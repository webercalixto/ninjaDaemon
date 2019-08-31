#ifndef NYNJATYPES_HPP
#define NYNJATYPES_HPP

#include "ninjaLogger.hpp"

namespace ninjaTypes {

/*using ninjaBool = bool;
using ninjaInt  = int;
using ninjaStr  = std::string;
using ninjaDbl  = double;*/


typedef bool        _bool;
typedef long int    _int;
typedef std::string _string;
typedef long double _double;
using workerConfigVariant = std::variant<_int, _string, _bool, _double>;
template <typename T>
struct configVal
{
    typedef T           type;
    workerConfigVariant value;
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
    ninjaTypes::workerConfigValType type  = WTYPE_STRING;
    std::string                     value = "";
} workerConfigVal;


using workerConfigMap = std::map<std::string, workerConfigVariant>;
using funcCallbackPtr = void(const int workerNum, const ninjaTypes::workerConfigMap &_workerConfig,
                             const std::shared_ptr<ninjaLogger> &_logger);
} // namespace ninjaTypes


#endif
