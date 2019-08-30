#include "global.hpp"
#include <csignal>
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
    ctx.workerConfigs["sleepDuration"] = { ninjaStructs::WTYPE_INT };
    ctx.workerConfigs["serverURL"]     = { ninjaStructs::WTYPE_STRING };
    ctx.funcPtr                        = callbackFunc;
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
    while (!ctx.finish)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
