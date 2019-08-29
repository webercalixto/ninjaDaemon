#include "global.hpp"

ninjaDaemon ctx;

int main(int argc, char *argv[])
{
    /** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
    ninjaStructs::workerConfigMap workerConfigs;
    workerConfigs["sleepDuration"] = { ninjaStructs::WTYPE_INT, "" };

    ctx.logger->log("STARTING NINJADAEMON");
    if (argc < 2 || argv[1] == nullptr || !std::filesystem::exists(argv[1]))
    {
        ctx.logger->log("No ini filename provided or ini file doesnt exist. exiting");
        return 0;
    }
    ctx.logger->log("STARTING NINJADAEMON");
    std::cout << "HELLO WORLD" << std::endl;
    ctx.loadConfigFile(std::string(argv[1]));
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
