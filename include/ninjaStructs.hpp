#ifndef NYNJASTRUCTS_HPP
#define NYNJASTRUCTS_HPP

#include "ninjaLogger.hpp"

namespace ninjaStructs {

template <typename T>
struct configVal
{
    typedef T                                    type;
    std::variant<int, std::string, bool, double> value;
};

struct configVal2
{
    std::any value;
};



typedef enum workerConfigValType
{
    WTYPE_INT    = 0,
    WTYPE_STRING = 1,
    WTYPE_BOOL   = 2,
    WTYPE_DOUBLE = 3
} workerConfigValType;

/** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
/** Of course there are libraries for this, but what I need here is quite simple **/
typedef struct workerConfigVal
{
    ninjaStructs::workerConfigValType type  = WTYPE_STRING;
    std::string                       value = "";
} workerConfigVal;

using workerConfigMap = std::map<std::string, std::variant<int, std::string, bool, double>>;
using funcCallbackPtr = void(const int workerNum, const ninjaStructs::workerConfigMap &_workerConfig,
                             const std::shared_ptr<ninjaLogger> &_logger);
} // namespace ninjaStructs


#endif
