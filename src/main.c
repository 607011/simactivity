#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fake.h"

#define loop for (;;)

int main(int argc, char *argv[])
{
    static const int IDLE_TIMEOUT_SECS = 30;
#ifdef DEBUG
    const unsigned int CHECK_INTERVAL_SECS = 1;
#else
    const unsigned int CHECK_INTERVAL_SECS = 10;
#endif
    int idle_timeout_secs =
        (argc == 2)
            ? atoi(argv[1])
            : IDLE_TIMEOUT_SECS;
#ifdef DEBUG
    printf("I am here (%d)\n", CHECK_INTERVAL_SECS);
#endif
    loop
    {
        int dt = system_idle_secs();
        if (dt > idle_timeout_secs)
        {
            fake_user_event();
        }
        sleep(CHECK_INTERVAL_SECS);
    }
    return EXIT_SUCCESS;
}
