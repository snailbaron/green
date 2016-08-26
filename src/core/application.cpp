#include "application.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <cassert>
#include <Windows.h>
#include <json.hpp>

#include <DXUT.h>

bool Application::InitInstance()
{
    int screenWidth = 800;
    int screenHeight = 600;

    // Create a DirectX window
    DXUTInit(true, true, &_cmdLine[0], true);
    DXUTCreateWindow(GameTitle(), _hInstance, Icon());
    if (!DXUTGetHWND()) {
        return false;
    }
    SetWindowText(DXUTGetHWND(), GameTitle());

    DXUTCreateDevice(D3D_FEATURE_LEVEL_10_1, true, screenWidth, screenHeight);


    // _screenSize = ... width, height
    // create DX device
    // _renderer = std::shared_ptr<IRenderer>(new D3DRenderer11());
    // _renderer->SetBackgroundColor(...)
    // _renderer->OnRestore()

    // _game = CreateGameAndView()
    // if (!_game) {
    //     return false;
    // }
    // _resourceCache->Preload("*.ogg", NULL)
    // ...

    return true;
}

/// Check if this game instance is the only one running in system
bool IsOnlyInstance(LPCWSTR gameTitle)
{
    // Make sure only 1 instance is performing the check
    HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

    if (handle != ERROR_SUCCESS) {
        HWND hwnd = FindWindow(gameTitle, NULL);
        if (hwnd) {
            ShowWindow(hwnd, SW_SHOWNORMAL);
            SetFocus(hwnd);
            SetForegroundWindow(hwnd);
            SetActiveWindow(hwnd);
            return false;
        }
    }

    return true;
}

bool Application::LoadStrings(std::string language)
{
    std::string languageFile = "strings/" + language + ".json";

    std::ifstream fs(languageFile);
    nlohmann::json j;
    fs >> j;

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
        _textResource[it.key()] = it.value();
    }

    return true;
}

std::string Application::GetString(std::string id)
{
    auto it = _textResource.find(id);
    assert(it != _textResource.end());
    return it->second;
}