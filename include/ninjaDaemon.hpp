#ifndef NINJADAEMON_HPP
#define NINJADAEMON_HPP

class ninjaDaemon
{
    private:
    std::string configFilename{ "" };
    int         numNinjaWorkers{ 0 };
    std::vector<std::unique_ptr<ninjaWorker>> ninjaWorkers;

    public:
    bool                          finish;
    ninjaStructs::workerConfigMap workerConfigs;
    bool                          finishDaemon{ false };
    std::shared_ptr<ninjaLogger>  logger;
    ninjaDaemon();
    ~ninjaDaemon();
    bool loadConfigFile(std::string configFile);
};
#endif
