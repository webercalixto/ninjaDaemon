#include "global.hpp"


ninjaWorker::ninjaWorker(const int _workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                         std::shared_ptr<ninjaLogger> _logger, ninjaStructs::funcCallbackPtr *_funcPtr)
{
    this->logger       = _logger;
    this->workerConfig = _workerConfig;
    this->workerNum    = _workerNum;
    this->funcPtr      = _funcPtr;
    std::string logMessage{ "ninjaWorker::ninjaWorker constructor workerNum = " + std::to_string(this->workerNum)
                            + " " };

    for (auto const &[key, val] : this->workerConfig)
    {
        logMessage += " [" + key + "]=>";
        if (auto pval = std::get_if<int>(&val)) logMessage += std::to_string(*pval);
        if (auto pval = std::get_if<std::string>(&val)) logMessage += *pval;
        if (auto pval = std::get_if<double>(&val)) logMessage += std::to_string(*pval);
        if (auto pval = std::get_if<bool>(&val))
        {
            if (*pval)
                logMessage += "TRUE";
            else
                logMessage += "FALSE";
        }
    }
    this->logger->log(logMessage);
    this->thread = std::thread([&] { this->threadFunction(std::move(this->exitSignal.get_future())); });
}

ninjaWorker::~ninjaWorker()
{
    this->logger->log("ninjaWorker::~ninjaWorker destructor  workerNum = " + std::to_string(this->workerNum)
                      + " starting");
    this->exitSignal.set_value();
    this->thread.join();
    this->logger->log("ninjaWorker::~ninjaWorker destructor  workerNum = " + std::to_string(this->workerNum)
                      + " finished");
}


void ninjaWorker::threadFunction(std::future<void> futureFinish)
{
    this->logger->log("ninjaWorker::threadFunction workerNum= " + std::to_string(this->workerNum) + " starting thread");
    while (futureFinish.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
    {
        this->funcPtr(this->workerNum, this->workerConfig, this->logger);
        this->logger->log("ninjaWorker::threadFunction workerNum= " + std::to_string(this->workerNum)
                          + " going to sleep for " + std::to_string(std::get<int>(this->workerConfig["sleepDuration"]))
                          + " ms");
        std::this_thread::sleep_for(std::chrono::milliseconds(std::get<int>(this->workerConfig["sleepDuration"])));
    }
    this->logger->log("ninjaWorker::threadFunction workerNum= " + std::to_string(this->workerNum)
                      + " finishing thread");
}
