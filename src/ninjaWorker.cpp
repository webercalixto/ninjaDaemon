#include "global.hpp"


ninjaWorker::ninjaWorker(const int _workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                         std::shared_ptr<ninjaLogger> _logger)
{
    this->logger       = _logger;
    this->workerConfig = _workerConfig;
    this->workerNum    = _workerNum;
    std::string logMessage{ "ninjaWorker::ninjaWorker constructor workerNum = " + std::to_string(this->workerNum)
                            + " " };

    for (auto const &[key, val] : this->workerConfig)
    {
        logMessage += " " + key + "[type=" + std::to_string(val.type) + "]=>" + val.value;
    }
    this->logger->log(logMessage);
}

ninjaWorker::~ninjaWorker()
{
    this->logger->log("ninjaWorker::~ninjaWorker destructor  workerNum = " + std::to_string(this->workerNum));
}

bool ninjaWorker::setConfigs(const ninjaStructs::workerConfigMap &_workerConfig)
{
    this->workerConfig = _workerConfig;
    return true;
}
