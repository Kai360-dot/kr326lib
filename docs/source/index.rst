kr326lib documentation
======================

**kr326lib** is a numerical library for process-systems calculations,
implemented in C++ with Python bindings via pybind11.

Installation
------------

.. code-block:: bash

   pip install kr326lib

Quick start
-----------

.. code-block:: python

   import kr326lib

   # Pressure of 1 mol of ideal gas at 298.15 K in 0.0248 m^3
   P = kr326lib.get_P_ideal_gas(n=1.0, T=298.15, V=0.0248)

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   api
