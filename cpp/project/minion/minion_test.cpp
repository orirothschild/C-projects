

#include "minion.hpp"   /* minion */

using namespace ilrd;

int main()
{
    Slogger::GetInstance().SetOstream(std::cout);
    Slogger::GetInstance().SetSeverity(Logger::DEBUG);
    Minion minion("8080");
    
    minion.Start();

    return 0;
}