#pragma once

#include "exception.hpp"
#include "exception.hpp"

/**
    \brief Base singleton class

    You can declare a singleton class like this:
    \code
        #include "singleton.hpp"

        class Data : public Singleton
        {
        public:
            Data(int data) { ... }
        };
    \endcode

    You would then use it like this:
    \code
        Data::Initialize(11);

        Data::Instance().Get();

        Data::Destroy();
    \endcode
*/

template <class T>
class Singleton
{
public:
    Singleton(const Singleton &other) = delete;

    /**
        \brief Create the singleton object.

        Arguments are passed to object class's constructor. Memory is allocated,
        and target object is constructed.
    */
    template <class ...Args>
    static void Initialize(Args... args)
    {
        _instance = new T(args...);
    }

    /**
        \brief Destroy singleton object.

        After this, the singleton state is uninitialized.
    */
    static void Destroy()
    {
        delete _instance;
        _instance = nullptr;
    }

    operator bool() const
    {
        return _instance;
    }

    static T & Instance()
    {
        if (!_instance) {
            THROW(Exception, "Singleton instance is requested, but singleton is not initialized");
        }
        return *_instance;
    }

protected:
    Singleton() {}

private:
    static T *_instance;
};

template <class T>
T * Singleton<T>::_instance = nullptr;
