//#include <stdarg.h>
#include <string.h>
#include <Arduino.h>

#include "Debug.h"


void Printv(const char* format, va_list args);
void PrintLinev(const char* format, va_list args);


void _DebugHelper::PrintLogHeader()
{
    Serial.print(millis());
    Serial.print(": ");
    
    if (strlen(_className) > 0) { Serial.print(_className); Serial.print("::"); }
}


void _DebugHelper::Log(const char* format, ...)
{
    PrintLogHeader();

    va_list args;
    va_start(args, format);
    PrintLinev(format, args);
    va_end(args);
}


void _DebugHelper::Print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    Printv(format, args);
    va_end(args);
}


void _DebugHelper::PrintLine(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    PrintLinev(format, args);
    va_end(args);
}


void _DebugLog(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    Print("%l: ", millis());
    PrintLinev(format, args);
    va_end(args);
}


void _DebugPrint(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    Printv(format, args);
    va_end(args);
}


void _DebugPrintLine(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    PrintLinev(format, args);
    va_end(args);
}


void Print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    Printv(format, args);
    va_end(args);
}


void PrintLine(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    PrintLinev(format, args);
    va_end(args);
}

void Printv(const char* format, va_list args)
{
    const char* pStart = format;
    const char* pEnd = format + strlen(format);
    const char* pChar = pStart;
   
    while (pStart < pEnd)
    {
        pChar = strchr(pStart, '%');
        
        if (pChar != NULL)
        {
            Serial.write(pStart, (pChar - pStart));
            
            char specifier = *(++pChar);
            
            switch(specifier)
            {
                case 0:
                    return;
                    
                case 'b':
                    Serial.print(va_arg(args, bool));
                    break;

                case 'c':
                    Serial.print(va_arg(args, char));
                    break;

                case 'f':
                    Serial.print(va_arg(args, double));
                    break;

                case 'i':
                    Serial.print(va_arg(args, int));
                    break;

                case 'l':
                    Serial.print(va_arg(args, long));
                    break;

                case 'p':
                    Serial.print(va_arg(args, unsigned long), HEX);
                    break;

                case 's':
                    Serial.print(va_arg(args, char*));
                    break;

                default:
                    Serial.print(specifier);
                    break;
            }
            
            pStart = ++pChar;
        }
        else
        {
            Serial.write(pStart);
            pStart = pEnd;
        }
    }
}


void PrintLinev(const char* format, va_list args)
{
    Printv(format, args);
    Serial.println("");
}

