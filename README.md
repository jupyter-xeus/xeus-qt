## Creating the environment

Qt is always refering to Qt5.

```
mamba install cmake pkg-config zeromq cppzmq xtl OpenSSL nlohmann_json qt -c conda-forge
```

To run the example:

```
mamba install xeus-sqlite xproperty cpp-tabulate
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