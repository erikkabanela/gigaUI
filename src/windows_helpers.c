#ifdef _WIN32
#include "windows_helpers.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib") // Link DWM library

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

bool IsWindowsDarkMode() {
    DWORD value = 1;  // default light
    DWORD dataSize = sizeof(value);
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER,
                      "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                      0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExA(hKey, "AppsUseLightTheme", NULL, NULL, (LPBYTE)&value, &dataSize);
        RegCloseKey(hKey);
    }
    return (value == 0);
}

void EnableDarkTitleBar(HWND hwnd) {
    if (!hwnd) return;
    BOOL dark = IsWindowsDarkMode();
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
}

#endif
