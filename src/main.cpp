#include "global.hpp"

ninjaDaemon ctx;

int main(int argc, char *argv[])
{
    ctx.logger->log("STARTING NINJADAEMON");
    if (argc < 2 || !std::filesystem::exists(argv[1]))
    {
        ctx.logger->log("No ini filename provided or ini file doest exists. exiting");
        return 0;
    }
    ctx.logger->log("STARTING NINJADAEMON");
    std::cout << "HELLO WORLD" << std::endl;
    ctx.loadConfigFile(std::string(argv[1]));
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
