# Xeus-qt
[![CI](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml/badge.svg)](https://github.com/jupyter-xeus/xeus-qt/actions/workflows/main.yml)


ZeroMQ-based middleware for xeus integrated in the Qt event loop.

## Creating the environment

Qt is always refering to Qt5.

```
mamba install compilers cmake pkg-config zeromq cppzmq xtl OpenSSL nlohmann_json qt=5.12.9 xeus=3.0.3 xeus-zmq=1.0.2  -c conda-forge
```

To run the example:

```
mamba install xeus-sqlite xproperty cpp-tabulate jupyter_client=6.1.12 jupyter_console python=3.9 tornado=6.1
```

## Building from source

To build the main library:

```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON
make install
```

To build the example:

```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
make install
```

## Known issues

If you're having issues with missing packages related to LibGl, try to add the following packages with `mamba`:

    mesa-libgl-devel-cos6-x86_64 mesa-dri-drivers-cos6-x86_64 libselinux-cos6-x86_64 libxdamage-cos6-x86_64 libxxf86vm-cos6-x86_64 libxext-cos6-x86_64 xorg-libxfixes

# License

We use a shared copyright model that enables all contributors to maintain the copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the LICENSE file for details.
