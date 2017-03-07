#ifndef _Variant_h
#define _Variant_h

#include <inttypes.h>


typedef union
    {
        int32_t  Long;
        int16_t  Int;
        int8_t   SByte;
        uint32_t UnsignedLong;
        uint16_t UnsignedInt;
        uint8_t  Byte;
        bool     Bool;
        float    Float;
        void*    Pointer; 
    } 
    variant_union_t;

    
struct variant_t
{
    variant_t()                     { Data.Long = 0; };
    variant_t(const int32_t value)  { Data.Long = value; };
    variant_t(const int16_t value)  { Data.Int = value; };
    variant_t(const int8_t value)   { Data.SByte = value; };
    variant_t(const uint32_t value) { Data.UnsignedLong = value; };
    variant_t(const uint16_t value) { Data.UnsignedInt = value; };
    variant_t(const uint8_t value)  { Data.Byte = value; };
    variant_t(const bool value)     { Data.Bool = value; };
    variant_t(const float value)    { Data.Float = value; };
    variant_t(void* value)          { Data.Pointer = value; };
    variant_t(const variant_union_t value) { Data = value; };

    operator int32_t()  { return Data.Long; };
    operator int16_t()  { return Data.Int; };
    operator int8_t()   { return Data.SByte; };
    operator uint32_t() { return Data.UnsignedLong; };
    operator uint16_t() { return Data.UnsignedInt; };
    operator uint8_t()  { return Data.Byte; };
    operator bool()     { return Data.Bool; };
    operator float()    { return Data.Float; };
    operator void*()    { return Data.Pointer; };
    operator variant_union_t()  { return Data; };
    template <typename T> operator T*() { return dynamic_cast<T*>(Data.Pointer); };
    
    private: variant_union_t Data;
};

#endif
