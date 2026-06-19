#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <chem.hpp>

PYBIND11_MODULE(kr326lib, m){
  m.doc() = "pybind11 module for kr326lib by Kai Ruth (ETH Zurich, Imperial)";
  m.def("get_P_ideal_gas", &get_P_ideal_gas, "Compute P from ideal gas equation", 
        pybind11::arg("n"), pybind11::arg("T"), pybind11::arg("V"));
}
