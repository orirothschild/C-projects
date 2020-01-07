#include <iostream>
#include <cstdio>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "threadpool.hpp"
//#include "Logger.hpp"
#include "slogger_header.hpp"

using namespace ilrd;

void PrintString(const std::string& str);
void SleepAndPrintString(const std::string& str);

int main()
{
    Slogger::GetInstance().SetOstream(std::cout);
    Slogger::GetInstance().SetSeverity(Logger::INFO);
    ThreadPool threadPool(15);
    //threadPool.DecPoolSize(10);
    threadPool.AddTask(boost::bind(PrintString, "task 1 1"), WaitableQueue<ThreadFunc>::LOW);
    threadPool.AddTask(boost::bind(PrintString, "task 1 2"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool.AddTask(boost::bind(PrintString, "task 1 3"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool.AddTask(boost::bind(PrintString, "task 1 4"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(PrintString, "task 1 5"), WaitableQueue<ThreadFunc>::LOW);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 6"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 7"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 8"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 9"), WaitableQueue<ThreadFunc>::LOW);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 10"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 11"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 12"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 13"), WaitableQueue<ThreadFunc>::MED);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 14"), WaitableQueue<ThreadFunc>::LOW);
    threadPool.AddTask(boost::bind(SleepAndPrintString, "task 1 15"), WaitableQueue<ThreadFunc>::HIGH);
    bool retVal = threadPool.Shutdown(5);
    std::cout << "shutdown retVal: " << retVal << std::endl;
    sleep(2);

    ThreadPool threadPool2(10);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 1"), WaitableQueue<ThreadFunc>::MED);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 2"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 3"), WaitableQueue<ThreadFunc>::LOW);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 4"), WaitableQueue<ThreadFunc>::LOW);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 5"), WaitableQueue<ThreadFunc>::MED);
    
    threadPool2.Pause();
    
    threadPool2.AddTask(boost::bind(PrintString, "task 2 6"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 7"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 8"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 9"), WaitableQueue<ThreadFunc>::HIGH);
    threadPool2.AddTask(boost::bind(PrintString, "task 2 10"), WaitableQueue<ThreadFunc>::HIGH);
    sleep(2);
    threadPool2.Resume();
    sleep(2);
    std::cout << "here" << std::endl;
    retVal = threadPool2.Shutdown(5);
    std::cout << "shutdown retVal: " << retVal << std::endl;

    return 0;
}

void PrintString(const std::string& str)
{
    std::cout << str << std::endl;
}

void SleepAndPrintString(const std::string& str)
{
    //sleep(1);
    std::cout << str << std::endl;
}