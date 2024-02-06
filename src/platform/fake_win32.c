#include <Windows.h>

#include "fake.h"

int system_idle_secs()
{
    LASTINPUTINFO lii = {
        // cbSize: size of struct
        sizeof(LASTINPUTINFO), 
        // dwTime: tick count goes here
        0 
    };
    if (GetLastInputInfo(&lii))
    {
        // GetTickCount() retrieves number of milliseconds that have elapsed since the system was started
        DWORD CurIdleTime = (GetTickCount() - lii.dwTime) / 1000ULL;
        return (int)CurIdleTime;
    }
    return -1;
}


void fake_user_event()
{
    // TODO
}