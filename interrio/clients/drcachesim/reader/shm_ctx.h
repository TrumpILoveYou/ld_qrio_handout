
#ifndef _SHM_CTX_H_
#define _SHM_CTX_H_

#include <stdint.h>

#include "gcc_atomic.h"
#include "cpu_timer.h"

typedef unsigned long atomic_uint_t;
typedef volatile atomic_uint_t atomic_t;

typedef uintptr_t       uint_t;

typedef struct {
   atomic_t lock;
} shmtx_sh_t;

typedef struct {
    atomic_t *lock;
    unsigned int spin;
} shmctx_t;
#endif

