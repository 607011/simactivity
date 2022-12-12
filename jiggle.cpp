#include <ApplicationServices/ApplicationServices.h>
#include <IOKit/IOKitLib.h>

int64_t systemIdleSecs(void)
{
  int64_t idlesecs = -1;
  io_iterator_t iter = 0;
  if (IOServiceGetMatchingServices(kIOMainPortDefault, IOServiceMatching("IOHIDSystem"), &iter) == KERN_SUCCESS)
  {
    io_registry_entry_t entry = IOIteratorNext(iter);
    if (entry)
    {
      CFMutableDictionaryRef dict = NULL;
      if (IORegistryEntryCreateCFProperties(entry, &dict, kCFAllocatorDefault, 0) == KERN_SUCCESS)
      {
        CFNumberRef obj = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("HIDIdleTime"));
        if (obj)
        {
          int64_t nanoseconds = 0;
          if (CFNumberGetValue(obj, kCFNumberSInt64Type, &nanoseconds))
          {
            idlesecs = nanoseconds / 1000000000LL;
          }
        }
        CFRelease(dict);
      }
      IOObjectRelease(entry);
    }
    IOObjectRelease(iter);
  }
  return idlesecs;
}

CGPoint getMousePos()
{
  CGEventRef event = CGEventCreate(NULL);
  CGPoint cursor = CGEventGetLocation(event);
  CFRelease(event);
  return cursor;
}

void moveMouseTo(const CGPoint point)
{
  CGEventRef event = CGEventCreateMouseEvent(
      NULL, kCGEventMouseMoved, point, kCGMouseButtonLeft);
  CGEventPost(kCGHIDEventTap, event);
  CFRelease(event);
}

int main()
{
  const int64_t IDLE_TIMEOUT_SECS = 60;
  while (true)
  {
    int64_t idleSecs = systemIdleSecs();
    CGPoint currentPos = getMousePos();
    if (idleSecs >= IDLE_TIMEOUT_SECS)
    {
      moveMouseTo(CGPointMake(currentPos.x + 1, currentPos.y));
      moveMouseTo(currentPos);
    }
    sleep(1);
  }
  return errSecSuccess;
}
