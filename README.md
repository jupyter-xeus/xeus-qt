## Creating the environment

```
mamba install cmake pkg-config zeromq cppzmq xtl OpenSSL nlohmann_json qt5 xeus-sqlite -c conda-forge
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