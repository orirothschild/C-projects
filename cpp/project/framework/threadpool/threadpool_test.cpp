#include <iostream>
#include <cstdio>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "threadpool.hpp"
#include "slogger_header.hpp"

using namespace ilrd;
using namespace std;

void printhello(char *str, size_t *len)
{
    pthread_t thread_id = pthread_self();
    *len = thread_id;
    //cout << str << "\t" << thread_id << endl;
    usleep(5);
}

void printhello1(char *str, size_t *len)
{
    pthread_t thread_id = pthread_self();
    *len = thread_id;
    // cout << "hello from the other thread"
    //      << "\t" << thread_id << endl;
    usleep(5);
}

void printhello2(char *str, size_t *len)
{
    //sleep(2);
}

int main()
{
    Slogger::GetInstance().SetOstream(std::cout);
    Slogger::GetInstance().SetSeverity(Logger::DEBUG);
    ThreadPool thread_pool(1);
    char *str = new char[30];
     sprintf(str, "Hello from thread");
    size_t len = 0;
    boost::function<void()> func = boost::bind(&printhello, str, &len);
    boost::function<void()> func1 = boost::bind(&printhello1, str, &len);
    boost::function<void()> func2 = boost::bind(&printhello2, str, &len);

    //thread_pool.AddTask(func2, WaitableQueue<ThreadFunc>::HIGH);
    for (int i = 0; i < 300; ++i)
    {
        thread_pool.AddTask(func, WaitableQueue<ThreadFunc>::MED);
        thread_pool.AddTask(func1, WaitableQueue<ThreadFunc>::LOW);
        thread_pool.AddTask(func, WaitableQueue<ThreadFunc>::HIGH);
        //std::cout << "i is now -------------------------------------------------------: " << i << std::endl;
        
    }

    /* thread_pool.Pause();
    thread_pool.AddTask(func, WaitableQueue<ThreadFunc>::MED);
    thread_pool.AddTask(func1, WaitableQueue<ThreadFunc>::LOW);
    thread_pool.AddTask(func, WaitableQueue<ThreadFunc>::HIGH);
    sleep(2);
    thread_pool.Resume(); */

    bool flag = true;
    while (flag)
    {
        std::cout << "*************************************" << thread_pool.ThreadCount() << "******************************************" << std::endl;
        //thread_pool.IncPoolSize(10);
        bool retval = thread_pool.Shutdown(10);
        if (retval == false)
        {
            std::cout << "timeout" << std::endl;
        }
        else
        {
            std::cout << "shutdown worked" << std::endl;
        }

        flag = false;

        // for (int i = 0; i < 300; ++i)
        // {
        //     thread_pool.AddTask(func, MED);
        //     thread_pool.AddTask(func1, LOW);
        //     thread_pool.AddTask(func, HIGH);
        // }
        // sleep(3);
        // std::cout << "**************************************" << thread_pool.ThreadCount() << "******************************************" << std::endl;
    }
    std::cout << "*************************************" << thread_pool.ThreadCount() << "******************************************" << std::endl;

    //thread_pool.Shutdown(10);
    
    
    delete[] str;


    //thread_pool.TestKillThreads();


    
    return 0;
}