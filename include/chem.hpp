#ifndef CHEM_HPP
#define CHEM_HPP

// Universal gas constant
extern double R_GAS; // (J / (mol*K)).

double get_P_ideal_gas(double n, double T, double V);

double get_V_ideal_gas(double n, double T, double P);

#endif // CHEM_HPP
