This is a simple worker daemon with REST JSON support, written with C++17.  
Quasi type safe data retrieval from ini file, fully asynchronous and 'unlimited' number of workers, etc etc  

### * Keep in mind this is a work in progress  
**Todo list**: Doxygen comments, code optimization and improvements on callback function style.  

<span style="color:red"> **I am working on a C99 equivalent, will release soon** </span>  
# Table of contents
1. [About this project](#about)  
  1.1 [Git workflow ](#git_workflow)  
  1.1 [Dependencies ](#dependencies)  
2. [Build Instructions](#build_instructions)  
  2.1 [First Build](#first_build)  
  2.2 [Subsequent Builds](#subsequent_builds)  
  2.2 [Clean](#clean)  
2. [Example](#usage_example)  
  2.1 [Ini File](#example_ini_file)  
  2.2 [Code](#example_code)  
  2.2 [Syslog output](#example_syslog)  

# Aboute this project <a name="about"></a>

This is a simple worker daemon with REST JSON support, written with C++17 <span style="color:red">  

**I am working on a C99 equivalent, will release soon** </span>  

There is a simple datatype abstraction, given that C++ will not support reflections in the near future.

Author: weber calixto (webersouzacalixto at gmail)

## Exception handling

Some lines with potential exceptions are left un-try-catched intentionally so the ugly runtime error can be seen.

## Git workflow <a name="git_workflow"></a>

I've chosen to work with GitHubflow (i.e Only a master branch with feature branches, no master/develop branching scheme, versioning with git tags).

Convention: Every master commit must be stable.

## Dependencies <a name="dependencies"></a>

Compiler:

For best C++17 support, use gcc 8 or newer, clang 7 or newer.

Formatter:

You must install clang-formatter to edit code following this project's code style.

*It may necessary to edit script/build.sh to use the appropriate clang-formatter command line call.

## Build instructions <a name="build_instructions"></a>

### First Build <a name="first_build"></a>

cd scripts/

./submodules.sh

./build.sh

### Subsequent builds <a name="subsequent_builds"></a>

cd scripts/

./build.sh

### To clean <a name="clean"></a>

cd scripts/

./clean.sh
 
# Usage Example <a name="usage_example"></a>
Lets say you want 4 workers ("threads").
### Configuration file .ini <a name="example_ini_file"></a>

[DEFAULT]  
numNinjaWorkers=4  
[0]  
sleepDuration=1000  
serverURL=http://www.google.com  
doubleExample=15.0  
boolExample=false  
[1]  
sleepDuration=1001  
serverURL=http://www.bing.com  
doubleExample=15.1  
boolExample=true  
[2]  
sleepDuration=1002  
serverURL=http://www.duckduckgo.com  
doubleExample=15.2  
boolExample=false  
[3]  
sleepDuration=1003  
serverURL=http://www.dontknowanyothersearchsites.com  
doubleExample=15.3  
boolExample=true  


### Your code thus would have to look like this <a name="example_code"></a>

```C++
ninjaDaemon ctx;
void signalHandler(int signum)
{
    ctx.logger->log("signalHandler: Interrupt signal (" + std::to_string(signum) + ") received");
    ctx.finish = true;
}

void callbackFunc(const int workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                  const std::shared_ptr<ninjaLogger> &_logger)
{
    (void)_workerConfig;
    _logger->log("callbackFunc workerNum=" + std::to_string(workerNum) + " doing some work");
}

int main(int argc, char *argv[])
{
    /** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
    ctx.funcPtr                        = callbackFunc;
    ctx.workerConfigs["sleepDuration"] = {static_cast<ninjaTypes::_int>(1000)};  
    ctx.workerConfigs["serverURL"]  = {static_cast<ninjaTypes::_string>(std::string(""))};  
    ctx.workerConfigs["doubleExample"]  = {static_cast<ninjaTypes::_double>(13.3f)};  
    ctx.workerConfigs["boolExample"]  = {static_cast<ninjaTypes::_bool>(true)};  
    ctx.logger->log("STARTING NINJADAEMON");
    if (argc < 2 || !ninjaUtils::validFile(argv[1]))
    {
        ctx.logger->log("No ini filename provided or ini file doesnt exist. exiting");
        return 0;
    }
    ctx.logger->log("STARTING NINJADAEMON");
    std::cout << "HELLO WORLD" << std::endl;
    if (!ctx.loadConfigFile(std::string(argv[1]))) return 0;
    signal(SIGINT, signalHandler);
    ctx.logger->log("RUNNING");
    while (!ctx.finish)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
```
### The output on syslog would look something like this: <a name="example_syslog"></a>
* Bear in mind the workers are fully asynchronous, message order may differ
```
Aug 30 21:28:31 weber-VirtualBox NINJAEXAMPLE[22207]: ninjaDaemon: Log started  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: STARTING NINJADAEMON  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: STARTING NINJADAEMON  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaDaemon::loadConfigFile  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaDaemon::loadConfigFile numNinjaWorkers = 4  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 0 boolExample=>false  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 0 doubleExample=>15.000000  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 0 serverURL=>http://www.google.com  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 0 sleepDuration=>1000  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::ninjaWorker constructor workerNum = 0  [boolExample]=>FALSE [doubleExample]=>15.000000 [serverURL]=>http://www.google.com [sleepDuration]=>1000  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 1 boolExample=>true  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 1 doubleExample=>15.100000  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 1 serverURL=>http://www.bing.com  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 1 sleepDuration=>1001 
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::ninjaWorker constructor workerNum = 1  [boolExample]=>TRUE [doubleExample]=>15.100000 [serverURL]=>http://www.bing.com [sleepDuration]=>1001  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 2 boolExample=>false  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 2 doubleExample=>15.200000   
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 2 serverURL=>http://www.duckduckgo.com  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 2 sleepDuration=>1002  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::ninjaWorker constructor workerNum = 2  [boolExample]=>FALSE [doubleExample]=>15.200000 [serverURL]=>http://www.duckduckgo.com [sleepDuration]=>1002  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::threadFunction workerNum= 1 starting thread  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::threadFunction workerNum= 0 starting thread  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::threadFunction workerNum= 2 starting thread  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 3 boolExample=>true  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 3 doubleExample=>15.300000  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 3 serverURL=>http://www.dontknowanyothersearchsites.com  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: worker 3 sleepDuration=>1003  
Aug 30 21:28:31 weber-VirtualBox `\`ڔU[22207]: ninjaWorker::ninjaWorker constructor workerNum = 3  [boolExample]=>TRUE [doubleExample]=>15.300000 [serverURL]=>http://www.dontknowanyothersearchsites.com [sleepDuration]=>1003  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: RUNNING  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: ninjaWorker::threadFunction workerNum= 3 starting thread  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: callbackFunc workerNum=2 doing some work  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: ninjaWorker::threadFunction workerNum= 2 going to sleep for 1002 ms  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: callbackFunc workerNum=1 doing some work  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: ninjaWorker::threadFunction workerNum= 1 going to sleep for 1001 ms  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: callbackFunc workerNum=0 doing some work  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: ninjaWorker::threadFunction workerNum= 0 going to sleep for 1000 ms  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: callbackFunc workerNum=3 doing some work  
Aug 30 21:28:31 weber-VirtualBox  e�!�[22207]: ninjaWorker::threadFunction workerNum= 3 going to sleep for 1003 ms  
Aug 30 21:28:32 weber-VirtualBox  e�!�[22207]: signalHandler: Interrupt signal (2) received  
Aug 30 21:28:32 weber-VirtualBox `\`ڔU[22207]: FINISHING NINJADAEMON  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaDaemon ctx finishing  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 0 starting  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::threadFunction workerNum= 0 finishing thread  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 0 finished  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 1 starting  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::threadFunction workerNum= 1 finishing thread  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 1 finished  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 2 starting  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::threadFunction workerNum= 2 finishing thread  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 2 finished  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 3 starting  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::threadFunction workerNum= 3 finishing thread  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaWorker::~ninjaWorker destructor  workerNum = 3 finished  
Aug 30 21:28:32 weber-VirtualBox ��w5[22207]: 7]: ninjaDaemon: ninjaLogger: Closing  
```
