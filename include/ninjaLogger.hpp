#ifndef NINJALOGGER_HPP
#define NINJALOGGER_HPP

class ninjaLogger
{
    private:
    int         logLevel;
    std::string logName;
    std::mutex  lock;

    public:
    const int NOTICE_LVL;
    const int DEBUG_LVL;
    const int INFO_LVL;
    const int WARNING_LVL;
    const int ERR_LVL;
    const int CRIT_LVL;
    const int ALERT_LVL;
    const int EMERG_LVL;
    ninjaLogger(const std::string &_logName);
    ~ninjaLogger();
    void setLogLevel(const int &level);
    void log(const std::string &message);
    void log(int level, const std::string &message);
};

#endif
