#include "application.hpp"

#include <Windows.h>

void Application::InitInstance()
{
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