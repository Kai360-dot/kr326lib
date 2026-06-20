"""
pybind11 module for kr326lib by Kai Ruth (ETH Zurich, Imperial)
"""
from __future__ import annotations
import typing
__all__: list[str] = ['get_P_ideal_gas', 'get_V_ideal_gas']
def get_P_ideal_gas(n: typing.SupportsFloat | typing.SupportsIndex, T: typing.SupportsFloat | typing.SupportsIndex, V: typing.SupportsFloat | typing.SupportsIndex) -> float:
    """
    Ideal gas pressure, P = n R T / V.
    
    Args:
        n: Amount of substance [mol].
        T: Absolute temperature [K] (Kelvin).
        V: Volume [m^3].
    
    Returns:
        Pressure [Pa].
    """
def get_V_ideal_gas(n: typing.SupportsFloat | typing.SupportsIndex, T: typing.SupportsFloat | typing.SupportsIndex, P: typing.SupportsFloat | typing.SupportsIndex) -> float:
    """
    Ideal gas volume, V = n R T / P.
    
    Args:
        n: Amount of substance [mol].
        T: Absolute temperature [K] (Kelvin).
        P: Pressure [Pa].
    
    Returns:
        Volume [m^3].
    """
