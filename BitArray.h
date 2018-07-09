/*******************************************************************************
 * BitArray.h
 ******************************************************************************/

#ifndef BitArray_h
#define BitArray_h

//#define BitArray_DEBUG

class BitArray
{
    private: uint8_t _elementSize;
    private: unsigned long _bits;

    public: BitArray(uint8_t elementSize) : _elementSize(((elementSize-1) % 16) + 1)
    {
    }

    public: unsigned long operator [](const uint8_t index)
    {
        unsigned long _mask = 0x0000FFFF >> (16 - _elementSize);

        return ((_bits >> (index*_elementSize)) & _mask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        int shift = index * _elementSize;
        unsigned long _mask = 0x0000FFFF >> (16 - _elementSize);
        unsigned long newValue = (value & _mask) << shift;
        
        _bits = (_bits & ~(_mask << shift)) | newValue;
    }
}


class BitArray1
{
    public:  static const uint8_t bitsize = 1;
    public:  static const unsigned long maxElements = sizeof(unsigned long);
    private: static const unsigned long bitmask = 0x0001;

    private: unsigned long _bits;

    public: unsigned long operator [](const uint8_t index)
    {
        unit8_t shift = index % maxElements;
        
        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        unit8_t shift = index % maxElements;

        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray2
{
    public:  static const uint8_t bitsize = 2;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x0003;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray3
{
    public:  static const uint8_t bitsize = 3;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x0007;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray4
{
    public:  static const uint8_t bitsize = 4;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x000F;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray5
{
    public:  static const uint8_t bitsize = 5;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x001F;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray6
{
    public:  static const uint8_t bitsize = 6;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x003F;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray9
{
    public:  static const uint8_t bitsize = 9;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x01FF;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}


class BitArray10
{
    public:  static const uint8_t bitsize = 10;
    public:  static const uint8_t maxElements = sizeof(unsigned long) / bitsize;
    private: static const unsigned long bitmask = 0x03FF;

    private: unsigned long _bits;
    
    public: unsigned long operator [](const uint8_t index)
    {
        uint8_t shift = (index % maxElements) * bitsize;

        return ((_bits >> shift) & bitmask);  
    }
    
    public: void Set(const uint8_t index, unsigned long value)
    {
        uint8_t shift = (index % maxElements) * bitsize;
        
        _bits = (_bits & ~(bitmask << shift)) | ((value & bitmask) << shift);
    }
}

#endif 
