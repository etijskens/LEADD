#pragma once
#ifndef _LEADD_HPP_
#define _LEADD_HPP_

#include <boost/serialization/list.hpp>
#include "Reconstruction.hpp"
#include "SAScore.hpp"

class LEADD {
private:
  ReconstructionSettings settings;
  sqlite3* database;
  sqlite3_stmt* select_fragment_by_id;
  ConnectionQueryResults query_results;
  FeatureLibrary feature_library;
  EvolutionGuide guide;

  std::list<ReconstructedMol> population;
  ReconstructionsInventory inventory;
  EvolutionReport report;

  SizeController controller;
  std::mt19937 prng;

  unsigned generation_n = 0;
  float best_score = 0;
  unsigned n_generations_stuck = 0;
  unsigned max_individual_id = 0;

  std::vector<float> parent_weights;
  std::vector<unsigned> parent_indices;

  const RDKit::SparseIntVect<std::uint32_t>* reference = nullptr;

private:
  void MakePopulationTakeBrickOwnership();
  void AssignConnectorWeightsToPopulation();
  void SampleParents();
  void ScoreChildrenBySimilarity();
  unsigned ScoreChildrenExternally();
  void FinishGeneration();

public:
  LEADD(const std::string& settings_file_path, const std::string& output_directory_path);

  void SeedPopulation();
  void GrowIndividuals();
  void InitializeRandomPopulation();
  void LoadPopulation();
  void SavePopulation() const;
  void WritePopulationSMILES(const std::string& file_path);

  unsigned GenerateChildren();
  void ScoreChildren();
  unsigned SelectivePressure();
  bool TerminationCriteriaMet();

  void UpdateReport();
  void ReportOnBestMolecule();

  void Cleanup();

  unsigned GetGenerationNumber() const;
  float GetBestScore() const;
  ReconstructedMol& GetBestIndividual();
  std::list<ReconstructedMol>& GetPopulation();
  const ReconstructionSettings& GetSettings() const;
  EvolutionReport& GetReport();
};

#endif
