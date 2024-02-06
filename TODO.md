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
#include <stdio.h>
#include <X11/Xlib.h>
 
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>
#include <gdk/gdkx.h>

static XScreenSaverInfo *mit_info = NULL;
int event_base, error_base;
if (XScreenSaverQueryExtension(GDK_DISPLAY(), &event_base, &error_base))
{
    mit_info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(GDK_DISPLAY(), GDK_ROOT_WINDOW(), mit_info);
    printf("idle time: %i\n", mit_info->idle);
}
else {
    // no display available
}
```

Compile with:

```
gcc -I/usr/X11R6/include \
  -I${GTK-DIR}/1.2.10/include/gtk-1.2 \
  -I${GLIB-DIR}/1.2.10/include/glib-1.2 \
  -I${GLIB-DIR}/lib/glib/include \
  -L${GTK-DIR}/1.2.10/i686-pc-linux-gnuoldld/lib \
  -L/usr/X11R6/lib \
  -L/usr/X11R6/lib/X11 \
  -lXss -lX11 -lgdk \
  -o jiggle jiggle.c
```
