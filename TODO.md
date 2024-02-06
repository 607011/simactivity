# TO DO

- [ ] Use CMake as build tool
- [ ] Windows version
- [ ] Linux version


## Windows

Use `GetLastInputInfo()` to retrieve the time of the last input event:

```c
#include <Windows.h>

int64_t system_idle_secs()
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
        return (int64_t)CurIdleTime;
    }
    return -1;
}
```


## Linux 

```c
#include <X11/extensions/scrnsaver.h>

int64_t system_idle_secs()
{
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL)
        return -1;
    XScreenSaverInfo *info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);
    return (int64_t)(info->idle / 1000UL);
}
```

Compile with:

```
gcc -I/usr/X11R6/include \
  -L/usr/X11R6/lib \
  -L/usr/X11R6/lib/X11 \
  -lXss -lX11
  -o jiggle jiggle.c
```
