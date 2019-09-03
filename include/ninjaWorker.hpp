#ifndef NINJAWORKER_HPP
#define NINJAWORKER_HPP
class ninjaWorker
{
    private:
    std::promise<void>           exitSignal;
    int                          workerNum{ -1 };
    ninjaTypes::workerConfigMap  workerConfig;
    std::shared_ptr<ninjaLogger> logger;
    ninjaTypes::funcCallbackPtr *funcPtr = nullptr;
    std::thread                  thread;

    public:
    ninjaTypes::workerLogLevel workerLogLevel = ninjaTypes::workerLogLevel::LOGLEVEL_INIT_AND_ERROR;
    ninjaWorker(const int _workerNum, const ninjaTypes::workerConfigMap &_workerConfig,
                std::shared_ptr<ninjaLogger> _logger, ninjaTypes::funcCallbackPtr *_funcPtr,
                const ninjaTypes::workerLogLevel _workerLogLevel = ninjaTypes::workerLogLevel::LOGLEVEL_INIT_AND_ERROR);
    ~ninjaWorker();
    void threadFunction(std::future<void> futureFinish);
};
#endif
