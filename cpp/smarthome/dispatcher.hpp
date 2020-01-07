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
    typedef std::vector<DispatcherFunction> FunctionContainer;
    typedef std::shared_ptr<DispatcherBoostFunction> SharedPtr;

    explicit Dispatcher() = default;
    ~Dispatcher() = default;
    Dispatcher(const Dispatcher& other) = delete;
    Dispatcher& operator=(const Dispatcher& other) = delete;

    std::shared_ptr<DispatcherBoostFunction>  Register(DispatcherBoostFunction function);
    void Unregister(SharedPtr& key);

    void Dispatch(Value value);

private:
    FunctionContainer m_container;
    boost::mutex m_lock;
};


template <class Value>
typename Dispatcher<Value>::SharedPtr Dispatcher<Value>::Register(DispatcherBoostFunction function)
{
    std::cout << "Dispatcher::Register" << std::endl;

    { // scope lock
        boost::mutex::scoped_lock lock(m_lock);

        std::shared_ptr<DispatcherBoostFunction> sharedPtr = std::make_shared<DispatcherBoostFunction>(function);

        m_container.emplace_back(sharedPtr);

        return sharedPtr;
    }
}

template <class Value>
void Dispatcher<Value>::Unregister(SharedPtr& key)
{
    std::cout << "Dispatcher::Unregister" << std::endl;
    { // scope lock
        boost::mutex::scoped_lock lock(m_lock);
        key = nullptr;
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
            std::shared_ptr<DispatcherBoostFunction> function = iter->lock();
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
    }
}
} // ilrd

#endif //ILRD_DISPATCHER_HPP
