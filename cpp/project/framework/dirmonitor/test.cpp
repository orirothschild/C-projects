#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <string>

#include "dirmonitor.hpp"
#include "slogger_header.hpp"
using namespace ilrd;


typedef boost::function<void (std::string)> LoaderFunction;

void Test1(std::string s)
{
	std::cout << s << std::endl;
}

int main()
{
	Slogger::GetInstance().SetOstream(std::cout);
    	Slogger::GetInstance().SetSeverity(Logger::DEBUG);
	Slogger::GetInstance().Log(Logger::DEBUG) << "Test: main" << std::endl;
	Reactor react;
	LoaderFunction func = &Test1;
	std::string dirPath = "./";


	DirMonitor dm(react, dirPath, func);

	react.Start();

	return 0;
}
