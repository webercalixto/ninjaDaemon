#include "global.hpp"

#include "inipp/inipp.h"

ninjaDaemon::ninjaDaemon()
{
    /*this->finishDaemon = false;
    this->numNinjaWorkers = 0;
    this->configFilename{ "" };*/
    this->logger = std::make_shared<ninjaLogger>();
}

ninjaDaemon::~ninjaDaemon()
{
    this->logger->log("ninjaDaemon ctx finishing");
}

bool ninjaDaemon::loadConfigFile(std::string configFile)
{
    this->logger->log("ninjaDaemon::loadConfigFile " + configFilename);
    this->configFilename = configFile;
    if (!std::filesystem::exists(this->configFilename))
    {
        this->logger->log("ninjaDaemon::loadConfigFile file does not exist!");
        return false;
    }

    std::ifstream    is(this->configFilename.c_str());
    inipp::Ini<char> ini;
    ini.parse(is);
    return false;
}
