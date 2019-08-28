#include "global.hpp"

ninjaDaemon ctx;

int main(int argc, char *argv[])
{
    (void)argv;
    ctx.logger->log("STARTING NINJADAEMON");
    if (argc < 2)
    {
        ctx.logger->log("No ini filename provided. exiting");
        return 0;
    }
    ctx.logger->log("STARTING NINJADAEMON");
    std::cout << "HELLO WORLD" << std::endl;
    ctx.loadConfigFile("test.ini");
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
