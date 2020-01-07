//
// Created by student on 5/1/19.
//

#include "smokedetector.hpp"

namespace ilrd
{

SmokeDetector::SmokeDetector(ilrd::Dispatcher<bool> &dispatcher)
: m_dispatcher(dispatcher)
, m_isSmoke(false)
{}

SmokeDetector::~SmokeDetector()
{}

void SmokeDetector::Start()
{
    int runForever = 1;
    while(runForever)
    {
        bool isSmoke = CheckSmoke();

        if (isSmoke != m_isSmoke)
        {
            m_isSmoke = isSmoke;
            m_dispatcher.Dispatch(m_isSmoke);
        }
    }
}



bool SmokeDetector::CheckSmoke()
{
    srand(time(NULL));
    int randomInt = rand() % 9;

    if (randomInt < 5)
    {
        return true;
    }

    return false;
}







}