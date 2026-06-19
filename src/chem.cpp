double R_GAS = 8.314; // create constants file

double get_P_ideal_gas(double n, double T, double V)
{
  return n * R_GAS * T / V;
}
