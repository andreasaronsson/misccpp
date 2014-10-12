// -*- c++ -*-

#include <Thread.h>
#include <sched.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>

unsigned int Thread::s_Instances = 0;
using namespace std;
/*****************************************************************************
 * Calls the run() method of a thread object.
 *
 * Arguments - arg: Pointer to the thread object to start.
 *    Return - Will always be NULL.
 **/
static void *threadFunction(void *arg)
{
    Thread *tp = (Thread *)arg;
    tp->Run();
    return NULL;
}

Thread::Thread()
{
    ++s_Instances;
}

Thread::~Thread()
{
    Stop();
    --s_Instances;
}

void Thread::Run()
{
    m_Running = true;
}

void Thread::Sleep(int ms)
{
    struct timespec ts;

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000 ) * 1000000;

    nanosleep(&ts, NULL);
}

void Thread::Start()
{
    if (pthread_create(&m_Handle, NULL, threadFunction, this))
        THROW_EXCEPTION("Thread could not be created");

    Thread::Yield();
}

void Thread::Stop()
{
    int timeout = 200;

    if (pthread_kill(m_Handle, SIGCONT) == 0)
    {
	cerr << "\n Killed me at once.";
    }
    Thread::Yield();
    do
    {
        Sleep(5);
        timeout--;
    } while (timeout != 0);

    if (pthread_kill(m_Handle, SIGKILL) == 0)
    {
	cerr << "\nI killed meself...";
    }
    else
    {
        pthread_join(m_Handle, NULL);
    }
}

void Thread::Yield()
{
    sched_yield();
}
