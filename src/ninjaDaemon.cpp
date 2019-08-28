#include "global.hpp"

ninjaDaemon::ninjaDaemon()
{
    this->finishDaemon = false;
    this->logger       = std::make_shared<ninjaLogger>();
}

ninjaDaemon::~ninjaDaemon() {}
