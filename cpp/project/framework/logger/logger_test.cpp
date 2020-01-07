
#include <fstream>
#include <iostream>

#include "slogger.hpp"
#define endline (std::endl<char, std::char_traits<char> >)

using namespace ilrd;

int main()
{
    Slogger::GetInstance().SetOstream(std::cout);
    Slogger::GetInstance().SetSeverity(Logger::DEBUG);
    Slogger::GetInstance().Log(Logger::ERROR) << "Writer: Ctor " << std::endl;
    /* Logger logger(std::cout, Logger::DEBUG);

    logger.Log(Logger::DEBUG) << "Error in ...";
    std::cout << std::endl;
    logger.Log(Logger::ERROR) << "value of ...";
    std::cout << std::endl;



    std::ofstream fp;
    fp.open("log", std::ios::app);

    Logger fileLogger(fp, Logger::DEBUG);

    fileLogger.Log(Logger::DEBUG) << "test log to file" << std::endl << std::endl;
    fileLogger.Log(Logger::DEBUG) << "second test" << endline;

    fp.close(); */

    return 0;
}
