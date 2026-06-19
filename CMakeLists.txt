cmake_minimum_required(VERSION 3.15...4.1)
project(kr326lib LANGUAGES CXX)

# Pin the Python used for the extension module to 3.13 (must be found BEFORE
# pybind11 so pybind11 builds against this interpreter/headers, not whatever it
# auto-detects). EXACT means configure fails if 3.13 is unavailable.
find_package(Python 3.13 EXACT REQUIRED COMPONENTS Interpreter Development)

add_subdirectory(extern/pybind11)

# calclib: target's name (handle for within this file to refer to) STATIC: makes
# .a file (if SHARED then .so, if INTERFACE it produces nothing, as this
# indicates we have a header only library) src/calclib.cpp: the source file
# being compiled into the library include/calc/lib.hpp: only for IDE
# referencing, no code functionality NOTE: The file will appear as libcalclib.a
# inside /build, as prefix "lib" is added by CMake, as well as .a on linux
# systems

add_library(chemlib STATIC src/chem.cpp include/chem.hpp)

# include contains the .hpp headers needed to satisfy the compiler at
# compilation time. When calclibs source files (src/calclib.cpp) get compiled
# the headers are made available via -I include/ (this would also be the case
# with PRIVATE) Due to keyword PUBLIC, the headers in calclib are also made
# available with -I include/ to any *target* within this call of *cmake* that
# links against libcalclib.a
target_include_directories(chemlib PUBLIC include)

# chemlib is a STATIC lib but gets linked into the `chem` shared module, so its
# objects must be position-independent (-fPIC). Without this the shared module
# fails to link with "relocation R_X86_64_PC32 ... recompile with -fPIC".
set_target_properties(chemlib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# indicates that the source files that are part of *target* library calclib,
# later libcalclib.a need to be compiled according to C++11 standard. PUBLIC:
# means any target linking against libcalclib.a also needs to be compiled under
# C++11 standards or higher.
target_compile_features(chemlib PUBLIC cxx_std_11)

# Build the Python extension module from the binding glue only.
# pybind11_add_module creates a SHARED module with the correct name/suffix (e.g.
# chem.cpython-314-x86_64-linux-gnu.so) and pulls in the Python headers.
pybind11_add_module(kr326lib src/bindings.cpp)

# Link the extension against the pure-C++ static lib so the bindings can call
# get_P_ideal_gas. PRIVATE: nothing links against a Python module.
target_link_libraries(kr326lib PRIVATE chemlib)

# Install the extension module into the wheel root so `import kr326lib` works.
# scikit-build-core only packages files placed by install() rules; without this
# the wheel is empty. DESTINATION "." == top level of site-packages.
install(TARGETS kr326lib LIBRARY DESTINATION .)
