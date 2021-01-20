# Ranger-32Blit

# Building
If you want to build a version for the device then specify a toolchain, which in this case is **32blit.toolchain**, make sure you remove any cached build files first. See cleaning section.

```
> cmake . -D32BLIT_PATH="../../32blit-beta" -DCMAKE_TOOLCHAIN_FILE="../../32blit-beta/32blit.toolchain"
```

If you want to build a desktop version just leave off the toolchain. This will configure a **make** build system so you can compile the code.
```
> cmake . -D32BLIT_PATH="../../32blit-beta"
```
Now you can run make to compile.

```
> make
OR
> make -j8; spout
```

# Cleaning
From within your project directory, remove these directories and files **before** running *cmake*:

```

rm -rf 32blit
rm -rf CMakeFiles
rm cmake_install.cmake
rm CMakeCache.txt
rm metadata.cmake
rm spout
rm spout.blit
rm spout.elf
rm spout.hex
rm spout.bin
rm spout.map

```
OR
```
clean.sh
```

# Example CMakeLists.txt(s)
```
cmake_minimum_required(VERSION 3.8)
project (als)
set(32BLIT_PATH "../32blit-beta/" CACHE PATH "Path to 32blit.cmake")
include (${32BLIT_PATH}/32blit.cmake)
blit_executable (als als.cpp als.hpp)
blit_assets_yaml (als assets.yml)
blit_metadata (als metadata.yml)
```

This Doom CMakeLists.txt shows an advance usage:
https://github.com/Daft-Freak/32BlitDoom/blob/master/CMakeLists.txt


This CmakeList has interesting checks in it, include debug stuff, uses ${PROJECT_NAME}
https://github.com/Daft-Freak/32blit-mjpeg-player/blob/master/CMakeLists.txt
