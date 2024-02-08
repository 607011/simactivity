/*
  fake_win.c

  Windows implementations of `system_idle_secs()` and `fake_user_event()` defined in fake.h

  Copyright (c) 2024 Oliver Lau <oliver@ersatzworld.net>

*/

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Windows.h>

#include "fake.h"

#ifdef DEBUG
#include <stdio.h>
#endif

int system_idle_secs(void)
{
    LASTINPUTINFO lii = {
        // cbSize: size of struct
        sizeof(LASTINPUTINFO),
        // dwTime: tick count goes here
        0};
    if (GetLastInputInfo(&lii))
    {
        // GetTickCount() retrieves number of milliseconds that have elapsed since the system was started
        DWORD CurIdleTime = (GetTickCount() - lii.dwTime) / 1000ULL;
        return (int)CurIdleTime;
    }
    return -1;
}

void fake_user_event(void)
{
#ifdef DEBUG
    wprintf(L"fake_user_event()\n");
#endif
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 1;
    input.mi.dy = 0;
    input.mi.mouseData = 0;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;  
    UINT uSent = SendInput(1, &input, sizeof(INPUT));
    if (uSent != 1)
    {
        wprintf(L"SendInput() failed: 0x%lx\n", HRESULT_FROM_WIN32(GetLastError()));
    }
}
