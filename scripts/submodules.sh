#!/bin/bash
cd ..
git submodule init
git submodule update
cd third-party/rapidjson
git submodule init
git submodule update
if [ -f "../pistache/build/src/libpistache.a" ]
then
echo "Pistache already built"
else
echo "Building pistache"
cd ../pistache/
mkdir build
cd build
rm -rf *
cmake ..
make -j3
fi