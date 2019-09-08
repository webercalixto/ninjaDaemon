#include "global.hpp"
#include <csignal>
ninjaDaemon ctx("|NINJAEXAMPLE|");

void signalHandler(int signum)
{
    ctx.logger->log("signalHandler: Interrupt signal (" + std::to_string(signum) + ") received");
    ctx.finish = true;
}

void callbackFunc(const int workerNum, const ninjaTypes::workerConfigMap &_workerConfig,
                  const std::shared_ptr<ninjaLogger> &_logger)
{
    (void)_workerConfig;
    _logger->log("callbackFunc workerNum=" + std::to_string(workerNum) + " doing some work");
}

int main(int argc, char *argv[])
{
    /** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
    ctx.funcPtr                        = callbackFunc;
    ctx.workerConfigs["sleepDuration"] = { static_cast<ninjaTypes::_int>(1000) };
    ctx.workerConfigs["serverURL"]     = { static_cast<ninjaTypes::_string>(std::string("")) };
    ctx.workerConfigs["doubleExample"] = { static_cast<ninjaTypes::_double>(13.3f) };
    ctx.workerConfigs["boolExample"]   = { static_cast<ninjaTypes::_bool>(true) };
    ctx.workerLogLevel                 = ninjaTypes::workerLogLevel::LOGLEVEL_INIT_AND_ERROR;
    ctx.logger->log("STARTING NINJADAEMON");
    if (argc < 2 || !ninjaUtils::validFile(argv[1]))
    {
        ctx.logger->log("No ini filename provided or ini file doesnt exist. exiting");
        return 0;
    }
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
