#pragma once

#ifdef _WIN32
#include <windows.h>  // Only here
#include <stdbool.h>
void EnableDarkTitleBar(HWND hwnd);
bool IsWindowsDarkMode();
#endif
