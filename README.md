# Aboute this project

This is a simple worker daemon with REST JSON support, written with C++17

Author: weber calixto (webersouzacalixto at gmail)

## Git workflow

I've chosen to work with GitHubflow (i.e Only a master branch with feature branches, no master/develop scheme, versioning with git tags).

Convention: Every master commit must be stable.

## Build instructions

### First time:

cd scripts/

./submodules.sh

./build.sh

### Subsequent builds 

cd scripts/

./build.sh

### To clean

cd scripts/

./clean.sh