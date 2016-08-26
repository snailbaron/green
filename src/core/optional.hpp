#pragma once

template <class T> class Optional
{
public:
    Optional() noexcept
        : _initialized(false)
    { }

    Optional(const T &value)
        : _initialized(false)
    {
        new (_data) T(value);
        _initialized = true;
    }

private:
    char _data[sizeof(T)];
    bool _initialized;
};

