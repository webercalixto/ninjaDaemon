#ifndef NINJADAEMON_HPP
#define NINJADAEMON_HPP

class ninjaDaemon
{
    private:
    std::string                               configFilename{ "" };
    int                                       numNinjaWorkers{ 0 };
    std::vector<std::unique_ptr<ninjaWorker>> ninjaWorkers;

    public:
    // std::map<std::string, std::variant<int, std::string, bool, double>> workerConfigs;
    ninjaTypes::funcCallbackPtr *funcPtr        = nullptr;
    ninjaTypes::workerLogLevel   workerLogLevel = ninjaTypes::workerLogLevel::LOGLEVEL_INIT_AND_ERROR;
    bool                         finish;
    ninjaTypes::workerConfigMap  workerConfigs;
    bool                         finishDaemon{ false };
    std::shared_ptr<ninjaLogger> logger;
    ninjaDaemon(const std::string &logName);
    ~ninjaDaemon();
    bool loadConfigFile(std::string configFile);
};
#endif
