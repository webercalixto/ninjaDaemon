#ifndef NYNJASTRUCTS_HPP
#define NYNJASTRUCTS_HPP



namespace ninjaStructs {

typedef enum workerConfigValType
{
    WTYPE_BOOL   = 0,
    WTYPE_STRING = 1,
    WTYPE_INT    = 2,
    WTYPE_DOUBLE = 3
} workerConfigValType;

/** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
/** Of course there are libraries for this, but what I need here is quite simple **/
typedef struct workerConfigVal
{
    ninjaStructs::workerConfigValType type;
    std::string                       value;
} workerConfigVal;

using workerConfigMap = std::map<std::string, ninjaStructs::workerConfigVal>;

} // namespace ninjaStructs


#endif
