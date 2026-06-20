# kr326lib

Numerical library by Kai Ruth (ETH Zurich, Imperial) — a C++ core with Python
bindings via [pybind11](https://pybind11.readthedocs.io/).

## Install

```bash
pip install kr326lib
```

## Usage

```python
import kr326lib

# Ideal gas law (SI units; temperature in kelvin).
P = kr326lib.get_P_ideal_gas(n=1.0, T=300.0, V=0.0224)   # pressure [Pa]
V = kr326lib.get_V_ideal_gas(n=1.0, T=300.0, P=101325)   # volume   [m^3]
```

Building from source or contributing? See [CONTRIBUTING.md](CONTRIBUTING.md).
