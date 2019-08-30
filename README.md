### * Bear in mind this is a work in progress  
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
sleepDuration=3000  
serverURL=http://www.google.com  
[1]  
sleepDuration=3000  
serverURL=http://www.bing.com  
[2]  
sleepDuration=3000  
serverURL=http://www.duckduckgo.com  
[3]  
sleepDuration=3000  
serverURL=http://www.dontknowanyothersearchsites.com  

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

void main(){
  ctx.workerConfigs["sleepDuration"] = { ninjaStructs::WTYPE_INT };
  ctx.workerConfigs["serverURL"]     = { ninjaStructs::WTYPE_STRING };
  ctx.funcPtr                        = callbackFunc;
  if(!ctx.loadConfigFile(your_ini_filename_here))
    return 0;
  signal(SIGINT, signalHandler);
  while (!ctx.finish)
  {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
```
### The output on syslog would look something like this: <a name="example_syslog"></a>
* Bear in mind the workers are fully asynchronous, message order may differ
```
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaDaemon: Log started
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaDaemon::loadConfigFile
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaDaemon::loadConfigFile numNinjaWorkers = 4
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::ninjaWorker constructor workerNum = 0  serverURL[type=1]=>http://www.google.com sleepDuration[type=2]=>3000
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::ninjaWorker constructor workerNum = 1  serverURL[type=1]=>http://www.bing.com sleepDuration[type=2]=>3000
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::ninjaWorker constructor workerNum = 2  serverURL[type=1]=>http://www.duckduckgo.com sleepDuration[type=2]=>3000
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 0 starting thread
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::ninjaWorker constructor workerNum = 3  serverURL[type=1]=>http://www.dontknowanyothersearchsites.com sleepDuration[type=2]=>3000
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 1 starting thread
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 2 starting thread
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 3 starting thread
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=0 doing some work
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 0 going to sleep
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=1 doing some work
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 1 going to sleep
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=3 doing some work
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 3 going to sleep
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=2 doing some work
Aug 29 22:29:47 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 2 going to sleep
Aug 29 22:29:49 weber-VirtualBox |NINJADAEMON|[4492]: signalHandler: Interrupt signal (2) received
Aug 29 22:29:49 weber-VirtualBox |NINJADAEMON|[4492]: ninjaDaemon ctx finishing
Aug 29 22:29:49 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 0 starting
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 0 finishing thread
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 0 finished
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 1 starting
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=3 doing some work
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 3 going to sleep
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=2 doing some work
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 2 going to sleep
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 1 finishing thread
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 1 finished
Aug 29 22:29:50 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 2 starting
Aug 29 22:29:53 weber-VirtualBox |NINJADAEMON|[4492]: callbackFunc workerNum=3 doing some work
Aug 29 22:29:53 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 3 going to sleep
Aug 29 22:29:53 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 2 finishing thread
Aug 29 22:29:53 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 2 finished
Aug 29 22:29:53 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 3 starting
Aug 29 22:29:56 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::threadFunction workerNum= 3 finishing thread
Aug 29 22:29:56 weber-VirtualBox |NINJADAEMON|[4492]: ninjaWorker::~ninjaWorker destructor  workerNum = 3 finished
Aug 29 22:29:56 weber-VirtualBox |NINJADAEMON|[4492]: ninjaDaemon: ninjaLogger: Closing

```
