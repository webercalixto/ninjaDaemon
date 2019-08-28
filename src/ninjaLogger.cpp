#include "global.hpp"
#include <syslog.h>

ninjaLogger::ninjaLogger()
    : NOTICE_LVL(LOG_NOTICE)
    , DEBUG_LVL(LOG_DEBUG)
    , INFO_LVL(LOG_INFO)
    , WARNING_LVL(LOG_WARNING)
    , ERR_LVL(LOG_ERR)
    , CRIT_LVL(LOG_CRIT)
    , ALERT_LVL(LOG_ALERT)
    , EMERG_LVL(LOG_EMERG)
{
    setLogLevel(this->DEBUG_LVL);
    openlog("|NINJADAEMON|", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    this->log("ninjaDaemon: Log started");
}

ninjaLogger::~ninjaLogger()
{
    this->log("ninjaDaemon: ninjaLogger: Closing");
    closelog();
}

void ninjaLogger::setLogLevel(const int &level)
{
    setlogmask(LOG_UPTO(level));
    this->logLevel = level;
}

void ninjaLogger::log(const int level, const std::string &message) const
{
    syslog(level, "%s", message.c_str());
    if (level <= this->CRIT_LVL) std::cout << message << std::endl;
}
void ninjaLogger::log(const std::string &message) const
{
    this->log(this->logLevel, message);
}
