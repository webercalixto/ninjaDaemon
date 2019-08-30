#ifndef NINJAWORKER_HPP
#define NINJAWORKER_HPP
class ninjaWorker
{
    private:
    int                           workerNum{ -1 };
    ninjaStructs::workerConfigMap workerConfig;
    std::shared_ptr<ninjaLogger>  logger;

    public:
    ninjaWorker(const int _workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                std::shared_ptr<ninjaLogger> _logger);
    ~ninjaWorker();
    bool setConfigs(const ninjaStructs::workerConfigMap &_workerConfig);
};
#endif
