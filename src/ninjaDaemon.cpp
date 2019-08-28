#include "global.hpp"

ninjaDaemon::ninjaDaemon()
{
    this->finishDaemon = false;
    this->logger       = std::make_shared<ninjaLogger>();
}

ninjaDaemon::~ninjaDaemon()
{
    this->logger->log("ninjaDaemon ctx finishing");
}

bool ninjaDaemon::loadConfigFile(std::string configFilename)
{
    this->logger->log("ninjaDaemon::loadConfigFile " + configFilename);

    return false;
}
