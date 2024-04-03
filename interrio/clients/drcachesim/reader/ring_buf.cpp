#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include "qr_head.h"
#include "shm_ctx.h"
#include "ring_buf.h"


/* func of shmctx*/
uint_t shmtx_force_unlock(shmctx_t *mtx);

void shmtx_init(shmctx_t *mtx, shmtx_sh_t *addr, unsigned int spin) {
    mtx->lock = &addr->lock;
    mtx->spin = spin;
}

uint_t shmctx_trylock(shmctx_t *mtx, uint_t id) {
    return (*mtx->lock == 0 && atomic_cmp_set(mtx->lock, 0, id));
}

void shmtx_lock(shmctx_t *mtx, uint_t id) {
    unsigned int i,n;
    static unsigned long long ticks_per_second = 0;
    unsigned long long ticks_nop = 0;

    if (unlikely(ticks_per_second == 0)) {
        ticks_per_second = GetCpuFreq();
    }

    for ( ;; ) {
        if (*mtx->lock == 0 && atomic_cmp_set(mtx->lock, 0, id)) {
            return;
        }

        for (n = 1; n < mtx->spin; n <<= 1) {
            for (i = 0; i < n; i++) {
                cpu_pause();
                ticks_nop++;
            }

            if (*mtx->lock == 0 && atomic_cmp_set(mtx->lock, 0, id)) {
                return;
            }
        }

        if (++ticks_nop > ticks_per_second/50) {
#ifdef RB_DEBUG
            printf("ticks_nop: %llu, %lu\n", ticks_nop, *mtx->lock);
#endif
            shmtx_force_unlock(mtx);
            ticks_nop = 0;
        }

        relinquish();
    }
}


uint_t shmtx_unlock(shmctx_t *mtx, uint_t id) {
    return atomic_cmp_set(mtx->lock, id, 0);
}

uint_t shmtx_force_unlock(shmctx_t *mtx) {
    return atomic_test_and_set(mtx->lock, 0);
}

/* ringbuf class */
ringbuf_t::ringbuf_t()
	:rb_channel_id(1)
{
	/* can merge with init */
	return;
}

int ringbuf_t::ringbuf_init(size_t size, size_t n, int key)
{
    size_t initsize = 0;
    void *addr = NULL;
    char *ch;
    int id;

#ifdef RB_CACHE_ALIGN
    size = size_align(size, cacheline_size);
#endif

    initsize = sizeof(shm_data_t) + size * n;

    id = shmget(key, initsize, SHM_R|SHM_W|IPC_CREAT);
    if (id == 0)
        return -1;

    addr = shmat(id, NULL, 0);
    if (addr == (void*)-1)
        return -2;

    rb_shm = (shm_data_t*)addr;
    rb_shm->size = size;
    rb_shm->max = n;
    //shm->index_r = 0;
    //shm->index_w = 0;


    // init mutex_w
    ch = rb_shm->channel;
    shmtx_init(&rb_mutex_w, (shmtx_sh_t*)ch, 0x800);
    shmtx_init(&rb_mutex_r, (shmtx_sh_t*)(ch + 64), 0x800);

#ifdef RB_DEBUG
    printf("index_r: %u, index_w: %u\n", shm->index_r, shm->index_w);
#endif

    return 0;
}


int ringbuf_t::ringbuf_pop_unlock()
{

    if (rb_shm->index_w == rb_shm->index_r ) {
	return No_Data;
    }
    if (rb_shm->flags[rb_shm->index_r] == 0) {
        return No_Data;
    }

    return 0;
}

int ringbuf_t::ringbuf_set_next()
{

    rb_shm->flags[rb_shm->index_r] = 0;
    rb_shm->index_r = Next_Slot(rb_shm->index_r, rb_shm->max);

    return 0;
}

void * ringbuf_t::shm_getaddr_from_idx()
{
    uint32_t index_r = rb_shm->index_r;
    void *p = (void *)(rb_shm->datas + index_r * rb_shm->size);
    return p;
}
