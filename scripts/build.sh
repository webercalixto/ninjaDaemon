#!/bin/bash
scriptsDir=$(pwd)
clangCMD=clang-format-6.0

cd $scriptsDir
cd ..
mkdir build
cd build
find ../include/ -iname *.h -o -iname *.hpp | xargs $clangCMD -i style=file -sort-includes=false
find ../src/ -iname *.c -o -iname *.cpp | xargs $clangCMD -i style=file -sort-includes=false
cmake ..
make -j1