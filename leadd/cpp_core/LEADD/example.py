import sys
from pyLEADD import LEADD

def ScoringFunction(smiles):
    """ Do something here and return float """
    return 3.14

def Main():
    settings_file = sys.argv[1]
    output_directory = sys.argv[2]

    leadd = LEADD(settings_file, output_directory)

    # Main loop. Each iteration is a generation.
    while not leadd.TerminationCriteriaMet():
        # Expand the population with children.
        leadd.GenerateChildren()
        # Score the children.
        for molecule in leadd.GetPopulation():
            if molecule.IsChild():
                smiles = molecule.GetSanitizedSMILES() # SMILES are text representations of molecules
                score = ScoringFunction(smiles)
                molecule.SetScore(score)
        # Keep the best individuals and wrap up the generation.
        leadd.SelectivePressure()

    leadd.Cleanup()

    return 0

if __name__ == "__main__":
    Main()
