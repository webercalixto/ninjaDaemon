#include "global.hpp"

#include "inipp/inipp.h"

ninjaDaemon::ninjaDaemon(const std::string &logName)
{
    this->logger = std::make_shared<ninjaLogger>(logName);
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
    for (int workerNum = 0; workerNum < this->numNinjaWorkers; workerNum++)
    {
        ninjaStructs::workerConfigMap workerConfig = this->workerConfigs;

        for (auto &[key, val] : workerConfig)
        {
            // inipp::extract(ini.sections[std::to_string(workerNum)][key], workerConfig[key].value);
            std::string value      = "";
            std::string logMessage = "worker " + std::to_string(workerNum) + " " + key + "=>";
            inipp::extract(ini.sections[std::to_string(workerNum)][key], value);
            if (std::holds_alternative<std::string>(val))
            {
                val = value;
                logMessage += std::get<std::string>(val);
            }
            else if (std::holds_alternative<int>(val))
            {
                val = std::stoi(value);
                logMessage += std::to_string(std::get<int>(val));
            }
            else if (std::holds_alternative<double>(val))
            {
                val = std::stod(value);
                logMessage += std::to_string(std::get<double>(val));
            }
            else if (std::holds_alternative<bool>(val))
            {
                val = ((value == std::string("true")) ? true : false);
                if (std::get<bool>(val))
                    logMessage += "true";
                else
                    logMessage += "false";
            }
            else
                logMessage += "HOLDTYPE NOT RECOGNIZED";
            this->logger->log(logMessage);
        }
        std::unique_ptr<ninjaWorker> ptr(new ninjaWorker(workerNum, workerConfig, this->logger, this->funcPtr));
        this->ninjaWorkers.push_back(std ::move(ptr));
    }
    return true;
}
