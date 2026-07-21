# Contributing

C++ library (CMake) with Python bindings (pybind11).

## Layout

- `include/chem.hpp`, `src/chem.cpp` - C++ library
- `src/bindings.cpp` - pybind11 bindings (the `kr326lib` module)
- `extern/pybind11` - vendored submodule

## Setup (once)

Needs Python 3.13, a C++ compiler, and [uv](https://docs.astral.sh/uv/).

```bash
git clone --recurse-submodules https://github.com/Kai360-dot/kr326lib.git
cd kr326lib
uv venv --python 3.13 .venv
uv pip install scikit-build-core pybind11 cmake ninja
uv pip install -e ".[dev]" \
    --no-build-isolation \
    --config-settings=editable.rebuild=true \
    --config-settings=build-dir=build/{wheel_tag}
```

## Dev loop

```bash
source .venv/bin/activate
# edit C++, then just import: it recompiles automatically
python -c "import kr326lib; print(kr326lib.get_P_ideal_gas(1, 300, 0.0224))"
```

Gotchas:

- Run from outside the repo root, or the cwd can shadow the installed module.
- Changed `CMakeLists.txt`? Re-run the `uv pip install -e .` command once.
- Stale autocomplete? Restart your language server (stubs regenerate per build).

## Release

Handled by CI: `release.yml` builds Linux/macOS/Windows wheels via cibuildwheel
(config in `[tool.cibuildwheel]` in `pyproject.toml`). For a quick local sanity
check only: `uv build --wheel` (must produce a platform-tagged wheel, not
`py3-none-any`).
