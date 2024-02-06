#include <X11/extensions/scrnsaver.h>

#include "fake.h"

#ifdef DEBUG
#include <stdio.h>
#endif

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
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL)
        return;
    Window win = XRootWindow(dpy, 0);
    XWarpPointer(dpy, None, win, 0, 0, 0, 0, 1, 0);
    XFlush(dpy);
    XWarpPointer(dpy, None, win, 0, 0, 0, 0, -1, 0);
    XFlush(dpy);
    printf("fake\n");
}

