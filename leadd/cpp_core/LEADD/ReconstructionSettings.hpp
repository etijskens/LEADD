#pragma once
#ifndef _RECONSTRUCTION_SETTINGS_HPP_
#define _RECONSTRUCTION_SETTINGS_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <unordered_map>
#include <experimental/filesystem>
#include <assert.h>

class ReconstructionSettings {
  std::string fragment_database_file;
  std::string connection_query_results_file;

  std::unordered_map<std::string, float> gammas{
    {"acyclic_frequency", 1.0f}, {"acyclic_level", 0.0f},
    {"ring_frequency",  1.0f},   {"ring_level",    0.0f},
    {"score", 2.5f}
  };

  std::unordered_map<std::string, unsigned> probabilities{
    {"peripheral_expansion", 4u},     {"peripheral_deletion", 4u},
    {"peripheral_substitution", 28u}, {"peripheral_crossover", 10u},
    {"internal_expansion", 4u},       {"internal_deletion", 4u},
    {"internal_substitution", 28u},   {"internal_crossover", 10u},
    {"translation", 4u},              {"stereo_flip", 4u},
    {"cyclization", 0u},              {"ring_expansion", 0u},
    {"ring_deletion", 0u},            {"ring_substitution", 0u},
    {"ring_crossover", 0u},           {"ring_translation", 0u}
  };

  unsigned prng_seed = 0;
  bool seed_prng = false;

  float n_ring_atoms_mean = 12.0f;
  float n_ring_atoms_stdev = 6.0f;
  unsigned max_n_ring_atoms = 24u;
  float peak_n_ring_atoms_probability = 0.7f;

  float ring_size_mean = 6.0f;
  float ring_size_stdev = 3.0f;
  unsigned max_ring_size = 12u;
  float peak_ring_size_probability = 0.9f;

  unsigned min_seed_size = 10u;

  bool assign_unspecified_stereo = false;

  unsigned n_seeds = 100u;
  unsigned n_generations = 10000u;
  unsigned n_children_per_generation = n_seeds;
  unsigned n_survivors_per_generation = n_seeds;
  float max_child_similarity = 0.95f;
  bool similarity_filter = true;

  float termination_score = 1.0f;
  bool average_score_as_termination_criterion = false;
  unsigned max_generations_stuck = 1000u;
  unsigned max_attempts_per_generation = 10u;
  unsigned max_multiple_intersections = 100u;
  unsigned max_maximum_bipartite_matchings = 100u;

  std::string feature_library_file;
  double max_sascore = 6.5;
  bool sascore_filter = false;

  std::string similarity_matrix_file;
  float acyclic_learning_similarity_threshold = 0.0f;
  float ring_learning_similarity_threshold = 0.0f;
  float acyclic_positive_reinforcement = 0.0f;
  float acyclic_negative_reinforcement = 0.0f;
  float ring_positive_reinforcement = 0.0f;
  float ring_negative_reinforcement = 0.0f;
  bool guided_evolution = false;

  std::string restart_input_file;
  std::string restart_output_file;
  unsigned n_generations_per_save = 0u;
  bool restart = false;
  bool save_progress = false;
  bool reset_weights_on_restart = false;

  std::string scoring_function_input_file;
  std::string scoring_function_call;
  std::string scores_output_file;
  std::string template_mol_smiles;
  bool external_scoring_function = false;
  bool score_first_population = true;

  bool write_report = false;
  bool monitor_best_molecule = false;

  std::vector<std::string> operations;
  std::vector<unsigned> operation_weights;
  std::discrete_distribution<unsigned> operations_distribution;

public:
  ReconstructionSettings();
  ReconstructionSettings(const std::string& settings_file);

  void GenerateOperationDistributions();
  const std::string& ChooseOperation(std::mt19937& prng);

  void CheckRequiredInputFiles() const;
  void CheckScoringFunctionValidity() const;

  const std::string& GetFragmentDatabaseFile() const;
  const std::string& GetConnectionQueryResultsFile() const;

  float GetAcyclicFrequencyGamma() const;
  float GetAcyclicLevelGamma() const;
  float GetRingFrequencyGamma() const;
  float GetRingLevelGamma() const;
  float GetScoreGamma() const;

  unsigned GetOperationProbability(const std::string& operation) const;

  unsigned GetPRNGSeed() const;
  bool SeedPRNG() const;

  float GetNRingAtomsMean() const;
  float GetNRingAtomsSTDEV() const;
  unsigned GetMaxNRingAtoms() const;
  float GetPeakNRingAtomsProbability() const;

  float GetRingSizeMean() const;
  float GetRingSizeSTDEV() const;
  unsigned GetMaxRingSize() const;
  float GetPeakRingSizeProbability() const;

  unsigned GetMinSeedSize() const;

  bool AssignUnspecifiedStereo() const;

  unsigned GetNSeeds() const;
  unsigned GetNGenerations() const;
  unsigned GetNChildrenPerGeneration() const;
  unsigned GetNSurvivorsPerGeneration() const;
  float GetMaxChildSimilarity() const;
  bool UsingSimilarityFilter() const;

  float GetTerminationScore() const;
  bool AverageScoreAsTerminationCriterion() const;
  unsigned GetMaxGenerationsStuck() const;
  unsigned GetMaxAttemptsPerGeneration() const;
  unsigned GetMaxMultipleIntersections() const;
  unsigned GetMaxMaximumBipartiteMatchings() const;

  const std::string& GetFeatureLibraryFile() const;
  float GetMaxSAScore() const;
  bool UsingSAScoreFilter() const;

  const std::string& GetSimilarityMatrixFile() const;
  float GetAcyclicLearningSimilarityThreshold() const;
  float GetRingLearningSimilarityThreshold() const;
  float GetAcyclicPositiveReinforcement() const;
  float GetAcyclicNegativeReinforcement() const;
  float GetRingPositiveReinforcement() const;
  float GetRingNegativeReinforcement() const;
  bool UsingGuidedEvolution() const;

  const std::string& GetRestartInputFile() const;
  const std::string& GetRestartOutputFile() const;
  unsigned GetNGenerationsPerSave() const;
  bool SaveProgress() const;
  bool Restart() const;
  bool ResetWeightsOnRestart() const;

  const std::string& GetScoringFunctionInputFile() const;
  const std::string& GetScoringFunctionCall() const;
  const std::string& GetScoresOutputFile() const;
  const std::string& GetTemplateMolSMILES() const;
  bool UsingExternalScoringFunction() const;
  bool ScoreFirstPopulation() const;

  bool WriteReport() const;
  bool MonitorBestMolecule() const;

  void Print() const;
};

bool StringIsBlank(const std::string& str);
bool FileIsAccessible(const std::string& path_str);
bool FileRootDirectoryIsAccessible(const std::string& path_str);

#endif
