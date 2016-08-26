#pragma once

#include <map>
#include <vector>
#include <string>

#include "singleton.hpp"

/**
    \brief Game application layer.
*/
class Application : public Singleton<Application>
{
public:
    bool InitInstance();

    virtual WCHAR * GameTitle() const = 0;
    virtual HICON Icon() const = 0;

private:
    bool LoadStrings(std::string language);
    std::string GetString(std::string id);

private:
    std::map<std::string, std::string> _textResource;

    std::vector<WCHAR> _cmdLine;
    HINSTANCE _hInstance;


    // _screenSize
    // _renderer
    // _game
    // _resourceCache
    // _cmdLine?
};