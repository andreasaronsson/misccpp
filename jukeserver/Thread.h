// -*- c++ -*-

#ifndef INCLUDE_THREAD_H
#define INCLUDE_THREAD_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <netdb.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <list>
#include <ncurses.h>
#include <ctype.h>
#include <Exception.h>

/**
 * \brief Thread class that can start and execute Runnable classes.
 *
 * A thread is a thread of execution in a program. An application can have
 * multiple threads of execution running concurrently.
 *
 * Every thread has a priority. Threads with higher priority are executed in
 * preference to threads with lower priority. When code running in some thread
 * creates a new Thread object, the new thread has its priority initially set
 * equal to the priority of the creating thread.
 */
class Thread
{
public:
    /**
     * \brief Create a new thread.
     *
     * Create a new thread.
     */
    Thread();

    /**
     * \brief Destroy the thread.
     *
     * Destroy the thread.
     **/
    ~Thread();

    /**
     * \brief Perform thread work - NOT FOR PUBLIC CONSUMING!
     *
     * Perform thread work - NOT FOR PUBLIC CONSUMING!
     */
    void Run();

    /**
     * \brief Suspend program execution for a while.
     *
     * Suspend program execution for a number of milliseconds.
     *
     * @param ms  number of milliseconds to sleep.
     */
    static void Sleep(int ms);

    /**
     * \brief Start running this thread.
     *
     * Start this thread and perform som actual work.
     */
    void Start();

    /**
     * \brief Stop the thread if it's currently executing.
     *
     * Stop the thread if it's currently executing.
     */
    void Stop();

    /**
     * \brief Let other processes and threads work.
     *
     * Give up your quality time with the processor and let some other lucky
     * thread or process perform some actual duty around here.
     */
    #ifdef Yield
    #undef Yield
    #endif
    static void Yield();
    
    // Dbug purposes

    inline int GetInstances() {return s_Instances;};


private:

    static unsigned int s_Instances;
    pthread_t m_Handle;
    bool m_Running;
    bool m_Stopped;
};


#endif // Header guard
