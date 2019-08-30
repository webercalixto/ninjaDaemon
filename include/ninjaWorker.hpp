#ifndef NINJAWORKER_HPP
#define NINJAWORKER_HPP
class ninjaWorker
{
    private:
    std::promise<void>             exitSignal;
    int                            workerNum{ -1 };
    ninjaStructs::workerConfigMap  workerConfig;
    std::shared_ptr<ninjaLogger>   logger;
    ninjaStructs::funcCallbackPtr *funcPtr = nullptr;
    std::thread                    thread;

    public:
    ninjaWorker(const int _workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                std::shared_ptr<ninjaLogger> _logger, ninjaStructs::funcCallbackPtr *_funcPtr);
    ~ninjaWorker();
    void threadFunction(std::future<void> futureFinish);
};
#endif
