#pragma once

#include "singleton.hpp"

/**
    \brief Game application layer.
*/
class Application : public Singleton<Application>
{
public:
    void InitInstance();

private:

    // _screenSize
    // _renderer
    // _game
    // _resourceCache
};