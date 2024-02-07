/*
  fake_linux.c

  Linux implementations of `system_idle_secs()` and `fake_user_event()` defined in fake.h

  Copyright (c) 2024 Oliver Lau <oliver@ersatzworld.net>

*/

#include <X11/extensions/scrnsaver.h> // for XScreenSaverQueryInfo()
#include <X11/extensions/XTest.h> // for XTestFakeRelativeMotionEvent()

#include "fake.h"

#ifdef DEBUG
#include <stdio.h>
#endif

int system_idle_secs()
{
  Display *disp = XOpenDisplay(NULL);
  if (disp == NULL)
    return -1;
  XScreenSaverInfo info;
  XScreenSaverQueryInfo(disp, DefaultRootWindow(disp), &info);
  return (int)(info.idle / 1000UL);
}

void fake_user_event()
{
  Display *disp = XOpenDisplay(NULL);
  if (disp == NULL)
    return;
  XWindowAttributes attr;
  Status ret = XGetWindowAttributes(disp, DefaultRootWindow(disp), &attr);
  if (ret == 0)
    return;
  int win_width = attr.width;
  int win_height = attr.height;
  Window root_returned, child_returned;
  int root_x, root_y, win_x, win_y;
  unsigned int mask_return;
  Bool result = XQueryPointer(disp,
			      DefaultRootWindow(disp),
			      &root_returned, &child_returned,
			      &root_x, &root_y,
			      &win_x, &win_y,
			      &mask_return);
  if (result == False)
    return;
  int dx = (win_x < win_width - 1) // ensure pointer doesn't stop at right border
    ? 1
    : -1;
  XTestFakeRelativeMotionEvent(disp, dx, 0, CurrentTime);
  XFlush(disp);
#ifdef DEBUG
  printf("- mouse now at %d,%d (%d,%d)\n", win_x, win_y, win_width, win_height);
#endif
}
