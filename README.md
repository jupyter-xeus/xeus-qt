# Xeus-qt

[![CI](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml/badge.svg)](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml)

ZeroMQ-based middleware for xeus integrated in the Qt event loop.

## Building and running the example kernel from source

First, create the environment with all required dependencies:
```
mamba env create -f environment-dev.yml -n xeus-qt
mamba activate xeus-qt
```

To build the main library:

```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
make install
```

To build the example kernel:

```
cd examples
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
make install
```

On linux, the build may fail with the following error:
```
cannot find "GL/gl.h"
```

In that case, run `mamba install mesalib -c conda-forge` and build again.

# License

We use a shared copyright model that enables all contributors to maintain the copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
