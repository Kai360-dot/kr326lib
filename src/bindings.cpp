#include <pybind11/cast.h>
#include <pybind11/pybind11.h>

#include <chem.hpp>

PYBIND11_MODULE(kr326lib, m)
{
  m.doc() = "pybind11 module for kr326lib by Kai Ruth (ETH Zurich, Imperial)";

  m.def("get_P_ideal_gas", &get_P_ideal_gas,
        R"doc(Compute P from the ideal gas equation.

  Computes pressure ``P = n * R * T / V`` from the ideal gas law.

  Args:
      n (float): Amount of substance [moles]
      T (float): Temperature [K]
      V (float): Volume [m3]

  Returns:
      float: Pressure P [Pa].
  )doc",
        pybind11::arg("n"), pybind11::arg("T"), pybind11::arg("V"));

  m.def("get_V_ideal_gas", &get_V_ideal_gas,
        "Compute V from ideal gas equation, n : number of gas molecules "
        "[mole], T : Temperature [K], P : Pressure [Pa]",

        R"doc(Compute V from the ideal gas equation.

  Computes Volume ``V = n * R * T / P`` from the ideal gas law.

  Args:
      n (float): Amount of substance [moles]
      T (float): Temperature [K]
      P (float): Pressure [Pa]

  Returns:
      float: Volume V [m3].
  )doc",
        pybind11::arg("n"), pybind11::arg("T"), pybind11::arg("P"));
}
