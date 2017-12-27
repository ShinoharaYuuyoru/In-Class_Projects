#pragma once

#include "Common.h"
#include <cstdio>
#include <cstdarg>
#include "Logger.h"
#include <sstream>
#include <stdarg.h>

#include <ctime>
#include <iomanip>

#define F92_BREAK

#define F92_ASSERT_ALL

#ifdef F92_ASSERT_ALL
    #define F92_ASSERT(cond, msg, ...) \
        do \
        { \
            if (!(cond)) \
            { \
                F92::Assert::ReportFailure(#cond, __FILE__, __LINE__, (msg), ##__VA_ARGS__); \
                F92_BREAK \
            } \
        } while(0)

    #define F92_ASSERT_WARNING(cond, msg, ...) \
        do \
        { \
            if (!(cond)) \
            { \
                F92::Assert::ReportFailure(#cond, __FILE__, __LINE__, (msg), ##__VA_ARGS__); \
            } \
        } while(0)
#else
    #define F92_ASSERT(cond, msg, ...) 
#endif

namespace F92
{
    namespace Assert
    {
        void ShutDown();

        extern std::string lastErrorMessage;

        const std::string currentDateTime();

        void ReportFailure(const char * condition, const char * file, int line, const char * msg, ...);
    }
}
