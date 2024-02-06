#include <X11/extensions/scrnsaver.h>

#include "fake.h"

int system_idle_secs()
{
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL)
        return -1;
    XScreenSaverInfo *info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);
    return (int)(info->idle / 1000UL);
}

void fake_user_event()
{
    // TODO
}