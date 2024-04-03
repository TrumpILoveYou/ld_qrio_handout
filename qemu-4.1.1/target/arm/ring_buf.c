

#include <sys/shm.h>
#include <unistd.h>

#include "exec/shm_ctx.h"
#include "exec/ring_buf.h"

#define _QR_Q_RB_DEBUG_
uint32_t cacheline_size = 512;

shm_data_t *shm = NULL;

shmctx_t    mutex_w;
shmctx_t    mutex_r;
int gcount = 0;
int ringbuf_init(size_t size, size_t n, int key) {
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

    shm = (shm_data_t*)addr;
    shm->size = size;
    shm->max = n;
    shm->index_r = 0; 
    shm->index_w = 0;
    shm->app_status = -1;
    for ( int i = 0 ; i < 300 ; i++) {
	    shm->flags[i] = 0;
    }
    printf("shm->size = %lu\n",shm->size);
    // init mutex_w
    ch = shm->channel;
    shmtx_init(&mutex_w, (shmtx_sh_t*)ch, 0x800);
    shmtx_init(&mutex_r, (shmtx_sh_t*)(ch + 64), 0x800);

#ifdef RB_DEBUG
    printf("index_r: %u, index_w: %u\n", shm->index_r, shm->index_w);
#endif

    return 0;
}
int ringbuf_get_index(size_t len , int pid) {

    pid = pid + 1;

    shmtx_lock(&mutex_w, pid);

    uint32_t index_w = shm->index_w;


    uint32_t next = Next_Slot(index_w, shm->max);

    if (next == shm->index_r) {
	shmtx_unlock(&mutex_w, pid);
	return -1;
    }
    /*if ( shm->flags[next] == 1 ) {
        shmtx_unlock(&mutex_w, pid);
        return -1;
    }*/

    atomic_cmp_set(&shm->index_w, index_w, next);
    if (!shmtx_unlock(&mutex_w, pid)) {
    } 
    return index_w;
}
int ringbuf_push_new(uint32_t index_w) {

    if ( shm->flags[index_w] == 1 ) {
	return -1;
    }
    atomic_cmp_set(&shm->flags[index_w], 0, 1);

    //printf("shm->falgs[%d] = %d\n",index_w,shm->flags[index_w]);

    return 0;
}
void * shm_getaddr_from_idx(uint32_t index_w){
    void *p = (void *)(shm->datas + index_w * shm->size);
    return p;
}


