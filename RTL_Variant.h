
#ifndef _RTL_Variant_h_
#define _RTL_Variant_h_

#include <inttypes.h>


union variant_union_t
{
    int32_t  Long;
    uint32_t UnsignedLong;
    int16_t  Int;
    uint16_t UnsignedInt;
    int8_t   SByte;
    uint8_t  Byte;
    char     Char;
    bool     Bool;
    float    Float;
    void*    Pointer;
};

inline uint16_t LoWord(variant_union_t v) { return uint16_t(v.UnsignedLong & 0x0000FFFF); };
inline uint16_t HiWord(variant_union_t v) { return uint16_t(v.UnsignedLong >> 16); };

struct variant_t
{
    variant_t()                     { Data.Long = 0; };
    variant_t(const int32_t value)  { Data.Long = value; };
    variant_t(const uint32_t value) { Data.UnsignedLong = value; };
    variant_t(const int16_t value)  { Data.Int = value; };
    variant_t(const uint16_t value) { Data.UnsignedInt = value; };
    variant_t(const int8_t value)   { Data.SByte = value; };
    variant_t(const uint8_t value)  { Data.Byte = value; };
    variant_t(const bool value)     { Data.Bool = value; };
    variant_t(const float value)    { Data.Float = value; };
    variant_t(void* value)          { Data.Pointer = value; };
    variant_t(const variant_union_t value) { Data = value; };
    variant_t(uint16_t loWord, uint16_t hiWord) { Data.Long = (uint32_t)((((uint32_t)hiWord) << 16) | (uint32_t)loWord); };

    operator int32_t()  { return Data.Long; };
    operator uint32_t() { return Data.UnsignedLong; };
    operator int16_t()  { return Data.Int; };
    operator uint16_t() { return Data.UnsignedInt; };
    operator int8_t()   { return Data.SByte; };
    operator uint8_t()  { return Data.Byte; };
    operator bool()     { return Data.Bool; };
    operator float()    { return Data.Float; };
    operator void*()    { return Data.Pointer; };
    operator variant_union_t()  { return Data; };

    template <typename T> operator T*() { return dynamic_cast<T*>(Data.Pointer); };

    uint16_t LoWord() { return (uint16_t)(Data.Long & 0x0000FFFF); };

    uint16_t HiWord() { return (uint16_t)(Data.Long >> 16); };

    private: variant_union_t Data;
};

#endif
