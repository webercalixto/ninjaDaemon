#ifndef NINJADAEMON_HPP
#define NINJADAEMON_HPP

class ninjaDaemon
{
    private:
    std::string configFilename{ "" };
    int         numNinjaWorkers{ 0 };

    public:
    ninjaStructs::workerConfigMap workerConfigs;
    bool                          finishDaemon{ false };
    std::shared_ptr<ninjaLogger>  logger;
    ninjaDaemon();
    ~ninjaDaemon();
    bool loadConfigFile(std::string configFile);
};
#endif
