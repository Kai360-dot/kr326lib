# Contributing to kr326lib

`kr326lib` is a C++ library built with CMake and exposed to Python via
[pybind11](https://pybind11.readthedocs.io/). This guide takes you from a clone
to a fast edit→run loop and a release wheel.

## Project layout

| Path               | Role                        |
| ------------------ | --------------------------- |
| `include/chem.hpp` | C++ declarations (header)   |
| `src/chem.cpp`     | C++ implementation          |
| `src/bindings.cpp` | pybind11 bindings           |
| `CMakeLists.txt`   | Build definition            |
| `pyproject.toml`   | Packaging / build backend   |
| `extern/pybind11`  | Vendored pybind11 submodule |

`src/chem.cpp` builds into the `chemlib` static library; `src/bindings.cpp`
wraps it as the importable `kr326lib` module.

## Prerequisites

- **Python 3.13** — the build pins this exact version.
- **A C++ compiler** with C++11 support.
- **[uv](https://docs.astral.sh/uv/)** — installs CMake and Ninja for you.

## Setup (one time)

pybind11 is a submodule, so clone recursively (or run
`git submodule update --init --recursive` inside an existing clone):

```bash
git clone --recurse-submodules https://github.com/Kai360-dot/kr326lib.git
cd kr326lib
```

Create an editable, auto-rebuilding dev environment:

```bash
uv venv --python 3.13 .venv
uv pip install scikit-build-core pybind11 cmake ninja        # build tools, in the venv
uv pip install -e ".[dev]" \
    --no-build-isolation \
    --config-settings=editable.rebuild=true \
    --config-settings=build-dir=build/{wheel_tag}
```

`editable.rebuild=true` recompiles changed C++ on the next `import`;
`--no-build-isolation` lets it reuse the build tools installed above.

## Debug loop

```bash
source .venv/bin/activate          # once per terminal
# edit src/*.cpp or include/*.hpp, then:
python -c "import kr326lib; print(kr326lib.get_P_ideal_gas(1, 300, 0.0224))"
```

Importing recompiles automatically when a source file changed (build output
prints; a failed compile raises on import). That is the whole loop: **edit → run**.

**Gotchas**

- Run from outside the repo root (or run a real `.py` file): with `python -c`
  the cwd is on `sys.path` and can shadow the installed module.
- Changed `CMakeLists.txt` (new target / source / dependency)? Re-run the
  `uv pip install -e .` command once. Editing existing sources doesn't need it.
- Editor autocomplete comes from a type stub generated and installed on every
  build (a `pybind11-stubgen` step in `CMakeLists.txt`); it isn't tracked in git.
  If completion looks stale, restart your language server (interpreter: `.venv`).

## Release

```bash
uv build --wheel        # wheel lands in dist/
```

A correct wheel is platform-tagged (e.g. `…-cp313-cp313-linux_x86_64.whl`); a
`py3-none-any` tag means the C++ was not compiled in. Test it isolated from the
dev environment:

```bash
uv venv --python 3.13 /tmp/wheeltest
uv pip install --python /tmp/wheeltest --no-index dist/kr326lib-*.whl
cd /tmp && /tmp/wheeltest/bin/python -c "import kr326lib; print(kr326lib.get_P_ideal_gas(1, 300, 0.0224))"
```

Validate metadata with `twine check dist/*` before publishing.

> **PyPI note:** a `linux_x86_64` wheel is rejected by PyPI — Linux binary wheels
> must be `manylinux`-tagged (build via
> [`cibuildwheel`](https://cibuildwheel.readthedocs.io/) + `auditwheel`). The
> sdist (`uv build --sdist`) can always be published.
