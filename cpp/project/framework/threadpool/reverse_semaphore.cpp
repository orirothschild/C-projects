#include "reverse_semaphore.hpp"	/*	reverse semaphore API	*/

namespace ilrd
{


ReverseSemaphore::ReverseSemaphore(int count)
: m_counter(count) 
{}

void ReverseSemaphore::Notify()
{
	boost::mutex::scoped_lock lock(m_mutex);
	m_counter.fetch_add(-1, boost::memory_order_seq_cst);
	m_cv.notify_one();
}

void ReverseSemaphore::Wait()
{
	boost::mutex::scoped_lock lock(m_mutex);
	while (m_counter > 0)
	{
		m_cv.wait(lock);
	}
	m_counter.fetch_add(1, boost::memory_order_seq_cst);
}

}	/*	namespace ilrd	*/