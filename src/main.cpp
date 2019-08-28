#include "global.hpp"

ninjaDaemon ctx;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    ctx.logger->log("STARTING NINJADAEMON");
    std::cout << "HELLO WORLD" << std::endl;
    ctx.logger->log("FINISHING NINJADAEMON");
    return 0;
}
