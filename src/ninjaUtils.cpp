#include "global.hpp"

bool ninjaUtils::validFile(const char *filename)
{
    if (ninjaUtils::validPtr(filename) && std::filesystem::exists(filename))
        return true;
    else
        return false;
}
