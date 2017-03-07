// Some debugging assistance

#ifndef __RTL_Debug_H__
#define __RTL_Debug_H__

#include <inttypes.h>
#include "RTL_Stdlib.h"


extern void _DebugLog(const char* format, ...);
extern void _DebugPrint(const char* format, ...);
extern void _DebugPrintLine(const char* format, ...);


#define PTR(x) reinterpret_cast<unsigned long>( x )

class _DebugHelper
{
    public: _DebugHelper() : _className("") {};
    public: _DebugHelper(const char* className) : _className(className) {};
    
    public: void Log(const char* format, ...);
    public: void Print(const char* format, ...);
    public: void PrintLine(const char* format, ...);
    public: void PrintLogHeader();
    
    private: const char* _className;
};


class _NullDebugHelper
{
    public: _NullDebugHelper() {};
    public: _NullDebugHelper(const char* className) {};
    
    public: void Log(const char* format, ...) { };
    public: void Print(const char* format, ...) { };
    public: void PrintLine(const char* format, ...) { };
    public: void PrintLogHeader() { };
};


#if DEBUG
#   define DebugHelper _DebugHelper
#   define DebugLog _DebugLog
#   define DebugPrint _DebugPrint
#   define DebugPrintLine _DebugPrintLine
#else
#   define DebugHelper _NullDebugHelper
#   define DebugLog(...)
#   define DebugPrint(...)
#   define DebugPrintLine(...)
#endif

#endif

