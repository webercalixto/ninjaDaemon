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
        this->logger->log("ninjaDaemon::loadConfigFile file |" + configFilename + "| does not exist!");
        return false;
    }
    std::ifstream    is(this->configFilename.c_str());
    inipp::Ini<char> ini;
    ini.parse(is);
    inipp::extract(ini.sections["DEFAULT"]["numNinjaWorkers"], this->numNinjaWorkers);
    if (this->numNinjaWorkers < 1)
    {
        this->logger->log("ninjaDaemon::loadConfigFile file |" + configFilename + "| numNinjaWorkers("
                          + std::to_string(this->numNinjaWorkers) + ") < 1");
        return false;
    }
    this->logger->log("ninjaDaemon::loadConfigFile numNinjaWorkers = " + std::to_string(this->numNinjaWorkers));
    for (auto const &[key, val] : this->workerConfigs)
    {
        std::cout << key << ':' << val.value << std::endl;
    }
    return false;
}
