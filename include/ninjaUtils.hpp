#ifndef NINJAUTILS_HPP
#define NINJAUTILS_HPP
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

} // namespace ninjaUtils


#endif
