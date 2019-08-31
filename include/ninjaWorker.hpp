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
    ninjaWorker(const int _workerNum, const ninjaTypes::workerConfigMap &_workerConfig,
                std::shared_ptr<ninjaLogger> _logger, ninjaTypes::funcCallbackPtr *_funcPtr);
    ~ninjaWorker();
    void threadFunction(std::future<void> futureFinish);
};
#endif
