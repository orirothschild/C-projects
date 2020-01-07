#ifndef ILRD_DISPATCHER_HPP
#define ILRD_DISPATCHER_HPP

#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
#include <map>
#include <string>

namespace ilrd
{

template <class Value>
class Dispatcher
{
public:
    typedef boost::function<void (Value)> DispatcherBoostFunction;
    typedef std::weak_ptr<DispatcherBoostFunction> DispatcherFunction;
    typedef std::map<int, DispatcherFunction> FunctionContainer;
    typedef std::pair<size_t, std::shared_ptr<DispatcherBoostFunction> > PairReturnType;

    explicit Dispatcher();
    ~Dispatcher() = default;
    Dispatcher(const Dispatcher& other) = delete;
    Dispatcher& operator=(const Dispatcher& other) = delete;

    PairReturnType Register(DispatcherBoostFunction function);
    void Unregister(size_t key);

    void Dispatch(Value t);

private:
    FunctionContainer m_container;
    boost::mutex m_lock;
    size_t m_uniqueKey;
};





template <class Value>
Dispatcher<Value>::Dispatcher()
: m_uniqueKey(0)
{
    std::cout << "Dispatcher::Ctor" << std::endl;
}

template <class Value>
typename Dispatcher<Value>::PairReturnType Dispatcher<Value>::Register(DispatcherBoostFunction function)
{
    std::cout << "Dispatcher::Register" << std::endl;
    { // scope lock
        boost::mutex::scoped_lock lock(m_lock);

        std::shared_ptr<DispatcherBoostFunction> sharedPtr = std::make_shared<DispatcherBoostFunction>(function);

        size_t uniqueKey = m_uniqueKey++;
        m_container.insert(std::pair<int, DispatcherFunction>(uniqueKey, sharedPtr));

        return std::make_pair(uniqueKey, sharedPtr);
    }
}

template <class Value>
void Dispatcher<Value>::Unregister(size_t key)
{
    std::cout << "Dispatcher::Unregister" << std::endl;
    { // scope lock
        boost::mutex::scoped_lock lock(m_lock);
        typename FunctionContainer::iterator iter = m_container.find(key);
        if (iter != m_container.end())
        {
            m_container.erase(iter);
        }
    }
}

template <class Value>
void Dispatcher<Value>::Dispatch(Value value)
{
    std::cout << "Dispatcher::Dispatch" << std::endl;
    { // scope lock
        boost::mutex::scoped_lock lock(m_lock);
        for (typename FunctionContainer::iterator iter = m_container.begin();
             iter != m_container.end();
        )
        {
            std::shared_ptr<DispatcherBoostFunction> function = iter->second.lock();
            if (function)
            {
                (*function)(value);
                ++iter;
            }
            else
            {
                iter = m_container.erase(iter);
            }
        }
//        for(iter = m_container.begin(); iter != m_container.end(); ++iter)
//        {
//            (iter->second)(t);
//        }
    }
}
} // ilrd

#endif //ILRD_DISPATCHER_HPP
