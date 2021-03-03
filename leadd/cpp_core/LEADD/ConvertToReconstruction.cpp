#include <iostream>
#include <boost/serialization/list.hpp>
#include <boost/program_options.hpp>
#include <GraphMol/FileParsers/MolSupplier.h>
#include "Fragmentation.hpp"
#include "Reconstruction.hpp"

ReconstructedMol ConvertToReconstructedMol(const RDKit::ROMol& mol, bool fragment_rings, bool names_as_scores, boost::format& formatter) {
  // Initialize an empty ReconstructedMol.
  ReconstructedMol reconstruction;
  // Set its molecule objects to the input RDKit::ROMol.
  reconstruction.pseudomol = mol;
  FlagAtoms(reconstruction.pseudomol);
  reconstruction.sanitized_mol = reconstruction.pseudomol;
  // If the ring systems ought to be fragmented:
  if (fragment_rings) {
    // Loop over the atoms in the molecule, convert them into Pseudofragments
    // and add them to the ReconstructedMol as MolBricks.
    for (const RDKit::Atom* atom : reconstruction.pseudomol.atoms()) {
      Pseudofragment pseudofragment = AtomToPseudofragment(reconstruction.pseudomol, atom, formatter);
      reconstruction.AddLabelledPseudofragment(pseudofragment);
    };
  // If ring systems should be treated as separate Pseudofragments.
  } else {
    // Separate the molecule into acyclic and cyclic fragments.
    std::vector<RDKit::ROMOL_SPTR> acyclic_fragments, ring_fragments;
    std::tie(acyclic_fragments, ring_fragments) = SplitAtRings(reconstruction.pseudomol);
    // Convert the cyclic fragments into Pseudofragments and add them to the
    // ReconstructedMol as MolBricks.
    for (RDKit::ROMOL_SPTR ring_fragment : ring_fragments) {
      Pseudofragment pseudofragment = DummyMolToPseudofragment(*ring_fragment, formatter);
      reconstruction.AddLabelledPseudofragment(pseudofragment);
    };
    // Loop over the acyclic atoms in the molecule, convert them into Pseudofragments
    // and add them to the ReconstructedMol as MolBricks.
    for (const RDKit::Atom* atom : reconstruction.pseudomol.atoms()) {
      if (!atom->getProp<bool>("WasInRing")) {
        Pseudofragment pseudofragment = AtomToPseudofragment(reconstruction.pseudomol, atom, formatter);
        reconstruction.AddLabelledPseudofragment(pseudofragment);
      };
    };
  };
  // If required, use the molecule's original name as its score.
  if (names_as_scores) {
    float score = std::stof(mol.getProp<std::string>("_Name"));
    reconstruction.SetScore(score);
  };

  return reconstruction;
};

int main(int argc, const char* argv[]) {
  // Set up a command line argument parser and parse the command line arguments.
  std::string input, output;
  bool names_as_scores, fragment_rings;

  boost::program_options::options_description description("Options");
  description.add_options()
   ("help,h",
     "Display this help message.")
   ("input,i", boost::program_options::value<std::string>(&input)->required(),
     "Path to the input file containing molecules in SMILES or SDF format.")
   ("output,o", boost::program_options::value<std::string>(&output)->required(),
     "Path to the output file containing serialized reconstruction versions of the molecules.")
   ("ringfrag,r", boost::program_options::bool_switch(&fragment_rings)->default_value(false),
     "Flag to enable ring fragmentation. If not provided ring systems will be isolated and treated as a single fragment.")
   ("nascores,s", boost::program_options::bool_switch(&names_as_scores)->default_value(false),
     "Flag to use the molecules' names as their scores.");

  boost::program_options::positional_options_description positionals_description;
  positionals_description.add("input", 1);
  positionals_description.add("output", 1);
  boost::program_options::variables_map vm;
  boost::program_options::command_line_parser parser(argc, argv);
  parser.options(description);
  parser.positional(positionals_description);
  boost::program_options::parsed_options parsed_options = parser.run();
  boost::program_options::store(parsed_options, vm);
  if (vm.count("help")) {
   std::cout << description;
   return 1;
  };
  boost::program_options::notify(vm);

  // Initialize a Connection string formatter.
  boost::format formatter("(%d, %d, %d)");

  // Initialize the list to store the ReconstructedMols.
  std::list<ReconstructedMol> reconstructions;

  // Create a molecule input stream based on the extension of the input file.
  std::experimental::filesystem::path extension = std::experimental::filesystem::path(input).extension();

  // If the input file is a SMILES file:
  if (extension == ".smi" || extension == ".ism" || extension == ".smiles") {
    RDKit::SmilesMolSupplier supplier(input);
    while (!supplier.atEnd()) {
      RDKit::ROMOL_SPTR mol (supplier.next());
      reconstructions.push_back(ConvertToReconstructedMol(*mol, fragment_rings, names_as_scores, formatter));
    };
  // If the input file is a SDF file:
  } else if (extension == ".sdf") {
    RDKit::SDMolSupplier supplier(input);
    while (!supplier.atEnd()) {
      RDKit::ROMOL_SPTR mol (supplier.next());
      reconstructions.push_back(ConvertToReconstructedMol(*mol, fragment_rings, names_as_scores, formatter));
    };
  // If the input format is invalid throw an error.
  } else {
    throw std::runtime_error("Unrecognized input format. Input should be either SMILES or SDF.");
  };

  // Assign unique IDs to the ReconstructedMols.
  unsigned id = 1;
  for (ReconstructedMol& reconstruction : reconstructions) {
    reconstruction.SetID(id++);
  };

  // Store the serialized ReconstructedMols in the output file.
  std::ofstream output_stream(output, std::ofstream::binary);
  boost::archive::binary_oarchive archive(output_stream);
  archive << reconstructions;

  // Signal success.
  return 0;
};
