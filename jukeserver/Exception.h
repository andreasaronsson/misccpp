// -*- c++ -*-

#ifndef INCLUDE_EXCEPTION_H
#define INCLUDE_EXCEPTION_H

#include <string>
#include <vector>

/**
 * \brief General error reporting class that can be thrown from high places.
 *
 * Exceptions are used to report errors. While ordinary C code uses different
 * return values for error reporting, exceptions in C++ (and other languages)
 * offer a more in-your-face approach. If you rely on return values, you must
 * remember that they can be ignored in an application because error checking
 * takes precious execution time and might make code much uglier. Setting up
 * the world for exception checking in C++ is free, and requests CPU time only
 * when an error occurs. If a method encounters errors 0.1% of the times it
 * will be executed, using exceptions is probably the best approach.
 *
 * Usage is easy. Surround the code that might throw an exception with a
 * <code>try</code> statement, execute the code and set a <code>catch</code>
 * at the end of the watched code. Example:
 *
 * \code
 * try {
 *     THROW_EXCEPTION("I made a boo-boo");
 * } catch (ecco::Exception &e) {
 *     std::cout << e.GetFilename();
 *     std::cout << ", line " << e.GetLine() << "\n";
 *     std::cout << e.GetMessage() << std::endl;
 * }
 * \endcode
 *
 * Remember to use the <code>THROW_EXCEPTION</code> macro, since it makes your
 * code somewhat cleaner. Of course, you can still use the long form any time
 * you feel like it. But it's ugly.
 *
 * \code
 * throw ecco::Exception("I made a boo-boo", __FILE__, __LINE__);
 * \endcode
 *
 * Backtraces are available now (currently only supported on Linux). To enable
 * this feature, you have to link with the '-rdynamic' flag.
 */
class Exception
{
public:
    //@{
    /**
     * \brief Create a new exception.
     *
     * Create a new exception.
     *
     * @param message  a short message to carry with the exception. You should
     *                 really try to use this message to state what happened,
     *                 why it happened and how many legs a spider might have.
     * @param filename  name of the file where the exception occurred. It's
     *                  probably most wise to use __FILE__ here.
     * @param line  line number for the exception. It's probably most wise to
     *              use __LINE__ here.
     */
    Exception(const std::string &message, const char *filename, int line);
    Exception(const char *message, const char *filename, int line);
    //@}

    /**
     * \brief Get the stack trace from where this exception was thrown.
     *
     * Get the stack trace from where this exception was thrown.
     *
     * @return  a stacktrace, if the host system supports this feature.
     */
    const std::vector<std::string> &GetBacktrace() const
    {
        return m_Backtrace;
    }

    /**
     * \brief Get the name of the file where the exception occurred.
     *
     * Get the name of the file where the exception occurred.
     *
     * @return  name of the file where the exception was created.
     */
    const std::string &GetFilename() const
    {
        return m_Filename;
    }

    /**
     * \brief Get the line number where the exception occurred.
     *
     * Get the line number where the exception occurred.
     *
     * @return  the line where the error occurred.
     */
    int GetLine() const
    {
        return m_Line;
    }

    /**
     * \brief Get the message of why the exception occurred.
     *
     * Get the message of why the exception occurred.
     *
     * @return  the message of what happened here.
     */
    const std::string &GetMessage() const
    {
        return m_Message;
    }

private:
    void BuildBacktrace();

    std::vector<std::string> m_Backtrace;
    std::string m_Filename;
    int m_Line;
    std::string m_Message;
};


#define THROW_EXCEPTION(msg) \
throw Exception((msg), __FILE__, __LINE__)

#endif // Header guard
