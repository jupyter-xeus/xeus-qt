## Creating the environment

Qt is always refering to Qt5.

```
mamba install compilers cmake pkg-config zeromq cppzmq xtl OpenSSL nlohmann_json qt=5.12.9 xeus=2.1.1 -c conda-forge
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

## Known issues

If you're having issues with missing packages related to LibGl, try to add the following packages with `mamba`:

    mesa-libgl-devel-cos6-x86_64
    mesa-dri-drivers-cos6-x86_64
    libselinux-cos6-x86_64
    libxdamage-cos6-x86_64
    libxxf86vm-cos6-x86_64
    libxext-cos6-x86_64
    xorg-libxfixes
