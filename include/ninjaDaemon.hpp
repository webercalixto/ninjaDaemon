#ifndef NINJADAEMON_HPP
#define NINJADAEMON_HPP

class ninjaDaemon
{
    private:
    std::string configFile;

    public:
    bool                         finishDaemon;
    std::shared_ptr<ninjaLogger> logger;
    ninjaDaemon();
    ~ninjaDaemon();
    bool loadConfigFile(std::string configFilename);
};
#endif
