/*
 *  C++ source file for module leadd.core
 */

#include <pybind11/pybind11.h>

// We are currently not interfacing with numpy
// #include <pybind11/numpy.h>

#include "LEADD/Reconstruction.cpp"
#include "LEADD/Graph.cpp"
#include "LEADD/PseudofragmentDB.cpp"
#include "LEADD/Connection.cpp"
#include "LEADD/ConnectionQueryResults.cpp"
#include "LEADD/ReconstructionSettings.cpp"
#include "LEADD/SAScore.cpp"
#include "LEADD/LEADD.cpp"

namespace py = pybind11;


PYBIND11_MODULE(core, m)
{// optional module doc-string
    m.doc() = "pybind11 core plugin"; // optional module docstring
    py::class_<LEADD>(m, "LEADD")
        .def(py::init< std::string const& // settings_file_path
                     , std::string const& // output_directory_path
                     >())
        .def("GrowIndividuals", &LEADD::GrowIndividuals)
        ;
}
