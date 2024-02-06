#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsLib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "fake.h"

int system_idle_secs(void)
{
    int idle_secs = -1;
    io_iterator_t it = 0;
    if (IOServiceGetMatchingServices(kIOMainPortDefault, IOServiceMatching("IOHIDSystem"), &it) == KERN_SUCCESS)
    {
        io_registry_entry_t entry = IOIteratorNext(it);
        if (entry)
        {
            CFMutableDictionaryRef dict = NULL;
            if (IORegistryEntryCreateCFProperties(entry, &dict, kCFAllocatorDefault, 0) == KERN_SUCCESS)
            {
                CFNumberRef obj = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("HIDIdleTime"));
                if (obj != NULL)
                {
                    int64_t ns = 0;
                    if (CFNumberGetValue(obj, kCFNumberSInt64Type, &ns))
                    {
                        idle_secs = (int)(ns / 1000000000LL);
                    }
                }
                CFRelease(dict);
            }
            IOObjectRelease(entry);
        }
        IOObjectRelease(it);
    }
    return idle_secs;
}

CGPoint get_mouse_pos(void)
{
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor_pos = CGEventGetLocation(event);
    CFRelease(event);
    return cursor_pos;
}

void move_mouse_to(CGPoint point)
{
    CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, point, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);
}

void fake_user_event(void)
{
    CGPoint currentPos = get_mouse_pos();
    move_mouse_to(CGPointMake(currentPos.x + 1, currentPos.y));
    move_mouse_to(currentPos);
#ifdef DEBUG
    printf("jiggle@%d,%d\n", (int)currentPos.x, (int)currentPos.y);
#endif
}
