#include <stdarg.h>
#include <string.h>
#include <Arduino.h>
#include "RTL_Debug.h"


::Print& _DebugHelper::Log()
{
    DebugStream << millis() << F(": ");

    if (_className != NULL && _className[0] != '\0') DebugStream << _className << F("::");

    return DebugStream;
}


::Print& _DebugHelper::Log(void* arg)
{
    DebugStream << millis() << F(": ");

    if (_className != NULL && _className[0] != '\0') DebugStream << _className;

    DebugStream << '[' << _HEX(PTR(arg)) << F("]::");

    return DebugStream;
}

