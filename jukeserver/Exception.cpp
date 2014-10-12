// -*- c++ -*-

#include <Exception.h>

// Backtracing in Linux.
#if defined(XP_UNIX_LINUX) && !defined(__UCLIBC__)
    #include <execinfo.h>
#endif

Exception::Exception(const std::string &message, const char *filename, int line)
    : m_Backtrace(0)
{
    m_Filename = filename;
    m_Message = message;
    m_Line = line;
    BuildBacktrace();
}

Exception::Exception(const char *message, const char *filename, int line)
    : m_Backtrace(0)
{
    m_Filename = filename;
    m_Message = message;
    m_Line = line;
    BuildBacktrace();
}

void Exception::BuildBacktrace()
{
#if defined(XP_UNIX_LINUX) && !defined(__UCLIBC__)
    void *stackArray[100];

    // Skip the first name in the stacktrace - it will always be this method,
    size_t size = backtrace(stackArray, 100);
    char **stackStrings = backtrace_symbols(stackArray, size);
    size--;
    m_Backtrace.reserve(size);
    for (unsigned int i = 0; i < size; i++)
        m_Backtrace.push_back(stackStrings[i + 1]);
    free(stackStrings);
#endif
}
