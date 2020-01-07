#ifndef RD60_REVERSE_SEMAPHORE_HPP
#define RD60_REVERSE_SEMAPHORE_HPP

#include <boost/thread/mutex.hpp>	/*	boost::mutex		*/
#include <boost/thread.hpp>			/*	condition_variable	*/
#include <boost/atomic.hpp>			/*	boost::atomic		*/

#include "utils.hpp"	            /*	utils	*/

namespace ilrd
{

class ReverseSemaphore : private Uncopyable
{
public:
    explicit ReverseSemaphore(int count = 1);
	/*	~ReverseSemaphore() = default;	*/
    void Notify();
    void Wait();

private:
    boost::mutex m_mutex;
    boost::condition_variable m_cv;
    boost::atomic<int> m_counter;
};

}

#endif	/*	RD60_REVERSE_SEMAPHORE_HPP	*/