#ifndef NINJAUTILS_HPP
#define NINJAUTILS_HPP
//#include <iostream>
#include <typeinfo>
#include "ninjaTypes.hpp"

namespace ninjaUtils {
template <typename T>
bool validPtr(T ptn)
{
    return ptn == nullptr ? false : true;
}

/*typename T mycast()
{
    return decltype(int);
}*/
bool validFile(const char *filename);

template <typename T>
T getValfromVariant(ninjaTypes::workerConfigVariant var)
{
    T value = std::get<T>(var);
    return value;
}

template <typename T>
bool getFromChars(ninjaTypes::_string &_val, T &dest)
{
    T                   result  = 0;
    ninjaTypes::_string tempStr = _val;
    if (auto [p, ec] = std::from_chars(tempStr.data(), tempStr.data() + tempStr.size(), result); ec == std::errc())
    {
        dest = result;
        return true;
    }
    return false;
}

struct visitWorkerConfigVariant
{
    public:
    ninjaTypes::_string &            _val;
    ninjaTypes::workerConfigVariant &_vari;
    visitWorkerConfigVariant(ninjaTypes::_string &val, ninjaTypes::workerConfigVariant &vari)
        : _val(val)
        , _vari(vari)
    {
    }
    bool operator()(ninjaTypes::_bool &)
    {
        if (_val == std::string("true"))
            _vari = true;
        else
            _vari = false;
        return 1;
    }
    bool operator()(ninjaTypes::_int &)
    {
        ninjaTypes::_int result = 0;
        if (getFromChars<ninjaTypes::_int>(_val, result))
        {
            _vari = result;
            return true;
        }
        return false;
    }
    /*** unfortunately std::from_chars does not seems to work for doubles on my gcc 9.1. Will use stol and stold instead
     * **/
    bool operator()(ninjaTypes::_double &)
    {
        if (std::is_same<ninjaTypes::_double, float>::value)
        {
            ninjaTypes::_double result = std::stof(_val);
            _vari                      = result;
            return true;
        }
        else if (std::is_same<ninjaTypes::_double, double>::value)
        {
            ninjaTypes::_double result = std::stod(_val);
            _vari                      = result;
            return true;
        }
        else if (std::is_same<ninjaTypes::_double, long double>::value)
        {
            ninjaTypes::_double result = std::stold(_val);
            _vari                      = result;
            return true;
        }
        return false;
    }
    bool operator()(ninjaTypes::_string &)
    {
        _vari = _val;
        return 4;
    }
};

} // namespace ninjaUtils



#endif
