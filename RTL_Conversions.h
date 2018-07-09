#ifndef _RTL_Conversions_h_
#define _RTL_Conversions_h_

#include <stdlib.h>


template <typename T> bool AsciiToInt(char*& p, T& value)
{
    auto start = p;
    auto result = strtol(p, &p, 10);
    auto success = (p != start);

    if (success) value = (T)result;
     
    return success;
}


template <typename T> size_t AsciiToInt(const char* p, T& value)
{
    auto pEnd = p;
    auto result = strtol(p, &pEnd, 10);
    auto length = (pEnd  - p);

    if (length > 0) value = (T)result;
     
    return length;
}


template <typename T> bool AsciiHexToInt(char*& p, T& value)
{
    auto start = p;
    auto result = strtoul(p, &p, 16);
    auto success = (p != start);

    if (success) value = (T)result;
     
    return success;
}


template <typename T> size_t AsciiHexToInt(const char* p, T& value)
{
    auto pEnd = p;
    auto result = strtoul(p, &pEnd, 16);
    auto length = (pEnd - p);

    if (length > 0) value = (T)result;
     
    return length;
}


bool AsciiToFloat(char*& p, float& value)
{
    auto start = p;
    auto result = strtod(p, &p);
    auto success = (p != start);

    if (success) value = result;
     
    return success;
}

#endif
