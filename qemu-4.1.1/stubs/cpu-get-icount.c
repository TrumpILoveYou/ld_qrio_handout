#include "qemu/osdep.h"
#include "qemu/timer.h"
#include "sysemu/cpus.h"
#include "qemu/main-loop.h"

int use_icount;
double rate = 1.0;
double clockrate = 1.0;
double tagrate = 1.0;
double sendrate = 1.0;

int64_t cpu_get_icount(void)
{
    abort();
}

int64_t cpu_get_icount_raw(void)
{
    abort();
}

void qemu_timer_notify_cb(void *opaque, QEMUClockType type)
{
    qemu_notify_event();
}
