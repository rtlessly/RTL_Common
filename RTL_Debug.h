// Some debugging assistance

#ifndef __RTL_Debug_H__
#define __RTL_Debug_H__

#include <pins_arduino.h>
#include <Streaming.h>
#include "RTL_Stdlib.h"


//******************************************************************************
/// This provides support for conditionally compiled debug logging. Debug logging
/// is enabled by adding the following macro definition at the beginning of the file
/// you wish to debug:
///
///      #define DEBUG 1 
///
/// Debug messages can then be displayed on the console by using the C++ streaming
/// notation as follows:
///
///     DebugPort << "This is a debug message. count=" << count << endl;
///
/// If the DEBUG  macro is 0 or not defined then the debug messages do nothing.
//******************************************************************************

// This determines which port to send the debug output to
#if defined(SERIAL_PORT_MONITOR)
   #define DEBUG_SERIAL_PORT   SERIAL_PORT_MONITOR
#elif defined(SERIAL_PORT_USBVIRTUAL)
   #define DEBUG_SERIAL_PORT   SERIAL_PORT_USBVIRTUAL
#else
   #define DEBUG_SERIAL_PORT   Serial
#endif

// This defines DebugPort as an actual serial port if DEBUG is enabled,
// otherwise, DebugPort is defined as a null (or dummy) print stream. 
// This allows the debug code to remain in the program but be effectively 
// disabled when DEBUG is disabled. 
#if DEBUG
    #define DebugPort   DEBUG_SERIAL_PORT
#else
    #define DebugPort   NullPrint
#endif

#define DebugStream ConsoleStream

#undef TRACE

#if DEBUG
#   define TRACE(x) x
#   define DEBUG_FUNCTION_INFO const char* __functionNmae__ = __func__
#   define DebugHelper _DebugHelper
#   define DebugLog (_DebugHelper().Log())
#else
#   define TRACE(x)
#   define DEBUG_FUNCTION_INFO
#   define DebugHelper _NullDebugHelper
#   define DebugLog (NullPrint)
#endif


inline ::Print& Logger()
{
    return ConsoleStream << millis() << F(": ");
}


inline ::Print& Logger(const char* const functionName)
{
    return Logger() << functionName << F(": ");
}


inline ::Print& Logger(const __FlashStringHelper* functionName)
{
    return Logger() << functionName << F(": ");
}


inline ::Print& Logger(const char* const className, const char* const functionName)
{
    return Logger() << className << F("::") << functionName << F(": ");
}


inline ::Print& Logger(const char* const className, const char* const functionName, void* obj)
{
    return Logger() << className << '[' << _HEX(PTR(obj)) << F("]::") << functionName << F(": ");
}


inline ::Print& Logger(const __FlashStringHelper* className, const char* const functionName)
{
    return Logger() << className << F("::") << functionName << F(": ");
}


inline ::Print& Logger(const __FlashStringHelper* className, const char* const functionName, void* obj)
{
    return Logger() << className << '[' << _HEX(PTR(obj)) << F("]::") << functionName << F(": ");
}


inline ::Print& Logger(const __FlashStringHelper* className, const __FlashStringHelper* functionName)
{
    return Logger() << className << F("::") << functionName << F(": ");
}


inline ::Print& Logger(const __FlashStringHelper* className, const __FlashStringHelper* functionName, void* obj)
{
    return Logger() << className << '[' << _HEX(PTR(obj)) << F("]::") << functionName << F(": ");
}


inline ::Print& Logger(const char* const className, void* obj)
{
    return Logger() << className << '[' << _HEX(PTR(obj)) << F("]: ");
}


inline ::Print& Logger(const __FlashStringHelper* className, void* obj)
{
    return Logger() << className << '[' << _HEX(PTR(obj)) << F("]: ");
}





class _DebugHelper
{
    public: _DebugHelper() : _className("") {};
    public: _DebugHelper(const char* className) : _className(className != NULL ? className : "") {};

    public: ::Print& Log();
    public: ::Print& Log(void* arg);

    private: const char* _className;
};


class _NullDebugHelper
{
    public: _NullDebugHelper() {};
    public: _NullDebugHelper(const char* className) {};

    public: ::Print& Log() { return NullPrint; };
    public: ::Print& Log(void* arg) { return NullPrint; };
};


template<typename T>
inline ::Print& operator <<(_DebugHelper& dbg, T arg) { DebugStream << arg; return DebugStream; };


template<typename T>
inline _NullPrint_& operator <<(_NullDebugHelper& dbg, T arg) { return NullPrint; };


#endif

