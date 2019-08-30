### * This is a work in progress
# Aboute this project

This is a simple worker daemon with REST JSON support, written with C++17

Author: weber calixto (webersouzacalixto at gmail)

## Git workflow

I've chosen to work with GitHubflow (i.e Only a master branch with feature branches, no master/develop scheme, versioning with git tags).

Convention: Every master commit must be stable.

## Dependencies

Compiler:

For best C++17 support, use gcc 8 or newer, clang 7 or newer.

Formatter:

You must install clang-formatter to edit code following this project's code style.

*It may necessary to edit script/build.sh to use the appropriate clang-formatter command line call.

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

# Ini file Example
Lets say you want 4 workers ("threads").
Configuration file .ini:

[DEFAULT]
numNinjaWorkers=4
[0]
sleepDuration=10
serverURL=http://www.google.com
[1]
sleepDuration=15
serverURL=http://www.bing.com
[2]
sleepDuration=20
serverURL=http://www.duckduckgo.com
[3]
sleepDuration=30
serverURL=http://www.dontknowanyothersearchsites.com
