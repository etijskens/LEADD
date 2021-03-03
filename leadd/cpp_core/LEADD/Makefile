# To install LEADD redefine the RDKIT_DIRECTORY in this script and type "make"
# in the command line while within the directory containing the present Makefile
# and all source code. After installation you can remove intermediate object files
# with "make clean".

# If libboost or libsqlite3 were installed in unconventional directories
# and the compiler fails to find them you can add their header and binary library
# directories with the -I and -L flags respectively. Note that you may also have
# to either specify the binary library directory in the LD_LIBRARY_PATH environment
# variable (either globally with "export" or locally in a script) or specify the
# directories in the compilation command with the -rpath flag.

# Note that by default the code is optimized for the same CPU architecture as
# the CPU used to compile the code. If you want to compile for a different
# architecture (perhaps a generic x84-64) modify the ARCHITECTURE variable below.
# Performance conscious users may also consider adding the -ffast-math flag to
# the compilation commands below.

RDKIT_DIRECTORY = /home/alan/RDKit
RDKIT_INCLUDE_DIRECTORY = ${RDKIT_DIRECTORY}/Code
RDKIT_LIBRARY_DIRECTORY = ${RDKIT_DIRECTORY}/build/lib
ARCHITECTURE = native

all: EncodeConnection DecodeConnection MakeFeatureLibrary CalculateSAScore Fragment PrecalculateConnectionQueryResults CheckConnectionQueryResultsGammas MakeFragmentSimilarityMatrix ConvertToReconstruction StandaloneLEADD

EncodeConnection: Connection.o EncodeConnection.cpp
	g++ Connection.o EncodeConnection.cpp -o EncodeConnection -march=${ARCHITECTURE} -O3

DecodeConnection: Connection.o DecodeConnection.cpp
	g++ Connection.o DecodeConnection.cpp -o DecodeConnection -march=${ARCHITECTURE} -O3

MakeFeatureLibrary: SAScore.o MakeFeatureLibrary.cpp
	g++ SAScore.o MakeFeatureLibrary.cpp -o MakeFeatureLibrary -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitGraphMol -lRDKitFingerprints -lRDKitDescriptors -lRDKitFileParsers -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

CalculateSAScore: SAScore.o CalculateSAScore.cpp
	g++ SAScore.o CalculateSAScore.cpp -o CalculateSAScore -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitGraphMol -lRDKitFingerprints -lRDKitDescriptors -lRDKitSmilesParse -lRDKitFileParsers -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

Fragment: Connection.o Pseudofragment.o PseudofragmentDB.o Fragment.cpp
	g++ Connection.o Pseudofragment.o PseudofragmentDB.o Fragment.cpp -o Fragment -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitChemTransforms -lRDKitForceFieldHelpers -lRDKitSubgraphs -lRDKitFingerprints -lRDKitSmilesParse -lRDKitFileParsers -lsqlite3 -lboost_serialization -lboost_program_options -lstdc++fs -fopenmp -march=${ARCHITECTURE} -O3

PrecalculateConnectionQueryResults: Connection.o Pseudofragment.o ConnectionQueryResults.o ReconstructionSettings.o PrecalculateConnectionQueryResults.cpp
	g++ Connection.o Pseudofragment.o ConnectionQueryResults.o ReconstructionSettings.o PrecalculateConnectionQueryResults.cpp -o PrecalculateConnectionQueryResults -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitFingerprints -lsqlite3 -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

CheckConnectionQueryResultsGammas: Connection.o ConnectionQueryResults.o CheckConnectionQueryResultsGammas.cpp
	g++ Connection.o Pseudofragment.o ConnectionQueryResults.o CheckConnectionQueryResultsGammas.cpp -o CheckConnectionQueryResultsGammas -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitFingerprints -lsqlite3 -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

MakeFragmentSimilarityMatrix: Connection.o Pseudofragment.o PseudofragmentDB.o MakeFragmentSimilarityMatrix.cpp
	h5c++ Connection.o Pseudofragment.o PseudofragmentDB.o MakeFragmentSimilarityMatrix.cpp -o MakeFragmentSimilarityMatrix -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitFingerprints -lsqlite3 -lboost_serialization -lboost_program_options -fopenmp -march=${ARCHITECTURE} -O3

ConvertToReconstruction: Graph.o Connection.o Pseudofragment.o PseudofragmentDB.o Fragmentation.o ConnectionQueryResults.o ReconstructionSettings.o Reconstruction.o ConvertToReconstruction.cpp
	h5c++ Graph.o Connection.o Pseudofragment.o PseudofragmentDB.o Fragmentation.o ConnectionQueryResults.o ReconstructionSettings.o Reconstruction.o ConvertToReconstruction.cpp -o ConvertToReconstruction -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitChemTransforms -lRDKitForceFieldHelpers -lRDKitFingerprints -lRDKitSmilesParse -lRDKitFileParsers -lRDKitMolDraw2D -lRDKitDepictor -lsqlite3 -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

StandaloneLEADD: Graph.o Connection.o Pseudofragment.o PseudofragmentDB.o SAScore.o ConnectionQueryResults.o ReconstructionSettings.o Reconstruction.o LEADD.o StandaloneLEADD.cpp
	h5c++ Graph.o Connection.o Pseudofragment.o PseudofragmentDB.o SAScore.o ConnectionQueryResults.o ReconstructionSettings.o Reconstruction.o LEADD.o StandaloneLEADD.cpp -o StandaloneLEADD -I${RDKIT_INCLUDE_DIRECTORY} -L${RDKIT_LIBRARY_DIRECTORY} -Wl,-rpath=${RDKIT_LIBRARY_DIRECTORY} -lRDKitRDGeneral -lRDKitGraphMol -lRDKitFingerprints -lRDKitDescriptors -lRDKitSmilesParse -lRDKitMolDraw2D -lRDKitDepictor -lsqlite3 -lboost_serialization -lboost_program_options -lstdc++fs -march=${ARCHITECTURE} -O3

Graph.o: Graph.hpp Graph.cpp
	g++ -c Graph.cpp -march=${ARCHITECTURE} -O3

Connection.o: Connection.hpp Connection.cpp
	g++ -c Connection.cpp -march=${ARCHITECTURE} -O3

Pseudofragment.o: Pseudofragment.hpp Pseudofragment.cpp
	g++ -c Pseudofragment.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

PseudofragmentDB.o: PseudofragmentDB.hpp PseudofragmentDB.cpp
	g++ -c PseudofragmentDB.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

Fragmentation.o: Fragmentation.hpp Fragmentation.cpp
	g++ -c Fragmentation.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

SAScore.o: SAScore.hpp SAScore.cpp
	g++ -c SAScore.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

ReconstructionSettings.o: ReconstructionSettings.hpp ReconstructionSettings.cpp
	g++ -c ReconstructionSettings.cpp -march=${ARCHITECTURE} -O3

ConnectionQueryResults.o: ConnectionQueryResults.hpp ConnectionQueryResults.cpp
	g++ -c ConnectionQueryResults.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

Reconstruction.o: Reconstruction.hpp Reconstruction.cpp
	h5c++ -c Reconstruction.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

LEADD.o: LEADD.hpp LEADD.cpp
	h5c++ -c LEADD.cpp -I${RDKIT_INCLUDE_DIRECTORY} -march=${ARCHITECTURE} -O3

clean:
	rm $(wildcard *.o)
