#-------------------------------------------------------------------------------
# Build C++ module leadd.core
#   > cd _cmake_build
# For a clean build:
#   > rm -rf *
# Configure:
#   > cmake ..
# build and install the .so file:
#   > make install
#-------------------------------------------------------------------------------
# This is all standard CMake

# There is a lot of boilerplate code, which normally needs not to be changed. It
# is always indented and surrounded by comment lines marking the begin and end of
# the boilerplate code, like this:
#<< begin boilerplate code
    # some code
#>> end boilerplate code

#<< begin boilerplate code
    cmake_minimum_required(VERSION 3.4)
  # Find pybind11_DIR, if python can be found...
  # (that is we assume that the virtual environment is activated)
    project(core CXX)
    find_program(
        PYTHON_EXECUTABLE
        NAMES python
    )
    if(PYTHON_EXECUTABLE)
      execute_process(
          COMMAND "${PYTHON_EXECUTABLE}" -c "import site; print(site.getsitepackages()[0])"
          OUTPUT_VARIABLE _site_packages
          OUTPUT_STRIP_TRAILING_WHITESPACE
          ERROR_QUIET
      )
    else()
      message(FATAL_ERROR "python executable not found.")
    endif()
    set(pybind11_DIR "${_site_packages}/pybind11/share/cmake/pybind11")
    message("pybind11_DIR : ${pybind11_DIR}")
  # now this will do fine:
    find_package(pybind11 CONFIG REQUIRED)
#>> end boilerplate code

####################################################################################################
######################################################################### Customization section ####
# set compiler:
# set(CMAKE_CXX_COMPILER path/to/executable)

# Set build type:
# set(CMAKE_BUILD_TYPE DEBUG | MINSIZEREL | RELEASE | RELWITHDEBINFO)

# Add compiler options:
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} <additional C++ compiler options>")

# Add preprocessor macro definitions:
# add_compile_definitions(
#     OPENFOAM=1912                     # set value
#     WM_LABEL_SIZE=$ENV{WM_LABEL_SIZE} # set value from environment variable
#     WM_DP                             # just define the macro
# )

# Add include directories
message($ENV{HOME})
if(DEFINED ENV{VSC_SCRATCH})
    message(scratch)
    # we are building on a VSC cluster
    # assuming modules intel/2020a, IntelPython3/2020a, IntelPython3-Packages,
    SET(boost_root $ENV{EBROOTBOOST})
    SET(rdkit_root " /data/antwerpen/205/vsc20574/RDKit")
    SET(hdf5_root  $ENV{EBROOTHDF5})
elseif( $ENV{HOME} STREQUAL "/Users/etijskens" )
    message(home)
    SET(boost_root "/usr/local/Cellar/boost/1.75.0_1")
    SET(rdkit_root "/usr/local/Cellar/rdkit/2020.09.1")
    SET(hdf5_root  "/usr/local/Cellar/hdf5/1.12.0_1")
else()
    message(oops)
endif()
message("boost_root = ${boost_root}")
message("rdkit_root = ${rdkit_root}")
message("hdf5_root  = ${hdf5_root}")
include_directories(
    ${boost_root}/include
    ${rdkit_root}/include/rdkit
    ${hdf5_root}/include
)

# Add link directories
link_directories(
    ${boost_root}/lib
    ${rdkit_root}/lib
    ${hdf5_root}/lib
)

# Add link libraries (lib1 -> liblib1.so)
link_libraries(
    RDKitChemTransforms
    RDKitDepictor
    RDKitDescriptors
    RDKitFileParsers
    RDKitFingerprints
    RDKitForceFieldHelpers
    RDKitGraphMol
    RDKitMolDraw2D
    RDKitRDGeneral
    RDKitSmilesParse
    RDKitSubgraphs
    boost_serialization
    boost_program_options
    sqlite3
    #c++experimental # instead of stdc++fs https://releases.llvm.org/7.0.0/projects/libcxx/docs/UsingLibcxx.html
)



####################################################################################################

#<< begin boilerplate code
  # Create the target:
    pybind11_add_module(core core.cpp)

    install(
        FILES       "_cmake_build/core${PYTHON_MODULE_EXTENSION}"
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
#>> end boilerplate code
