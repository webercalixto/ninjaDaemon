#ifndef NINJAUTILS_HPP
#define NINJAUTILS_HPP
namespace ninjaUtils {
template <typename T>
bool validPtr(T ptn)
{
    return ptn == nullptr ? false : true;
}
} // namespace ninjaUtils

#endif
