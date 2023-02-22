# Xeus-qt

[![CI](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml/badge.svg)](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml)

ZeroMQ-based middleware for xeus integrated in the Qt event loop.

## Dependencies

| `xeus-qt` | `xeus` | `qt` |
|-----------|--------|------|
|  master   | ^3.0.0 | ^5.0 |
|  0.1.0    | ^3.0.0 | ^5.0 |

## Building and running the example kernel from source

```
mamba install compilers cmake pkg-config zeromq cppzmq xtl OpenSSL nlohmann_json qt xeus xeus-zmq  -c conda-forge
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

# License

We use a shared copyright model that enables all contributors to maintain the copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
