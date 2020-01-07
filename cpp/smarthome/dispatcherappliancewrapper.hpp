#ifndef ILRD_DISPATCHERAPPLIANCEWRAPPER_HPP
#define ILRD_DISPATCHERAPPLIANCEWRAPPER_HPP

#include <vector>
#include <boost/bind.hpp>
#include <bits/shared_ptr.h>

#include "dispatcher.hpp"

namespace ilrd
{

template <class Key, class Value, class Type>
class DispatcherApplianceWrapper
{
public:
    explicit DispatcherApplianceWrapper(Type *type);
    ~DispatcherApplianceWrapper();

    void Register(Dispatcher<Key, Value>& dispatcher);
    void Unregister(Type *type);

private:
    DispatcherApplianceWrapper(const DispatcherApplianceWrapper& other);
    DispatcherApplianceWrapper& operator=(const DispatcherApplianceWrapper& other);

    std::shared_ptr<Type> m_wrapper;
    std::vector<Dispatcher<Key, Value> > m_dispatchers;


};


template <class Key, class Value, class Type>
DispatcherApplianceWrapper<Key, Value, Type>::DispatcherApplianceWrapper(Type *type)
: m_wrapper(std::shared_ptr<Type>(type, boost::bind(&DispatcherApplianceWrapper::Unregister, this, _1)))
{}

template <class T>
DispatcherApplianceWrapper<T>::~DispatcherApplianceWrapper()
{
    Unregister();
}

template <class T>
void DispatcherApplianceWrapper<T>::Register(ilrd::Dispatcher<> &dispatcher)
{
    dispatcher.Register();
}

template <class T>
void DispatcherApplianceWrapper<T>::Unregister(T *type)
{

}




} // ilrd

#endif //ILRD_DISPATCHERAPPLIANCEWRAPPER_HPP
