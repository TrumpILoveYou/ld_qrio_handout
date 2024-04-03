#ifndef _RING_BUF_2_H_
#define _RING_BUF_2_H_

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include "shm_ctx.h"
#define Channel_Size 256

#define size_align(d, a)     (((d) + (a - 1)) & ~(a - 1))

#define Next_Slot(x, max) ((x) + 1) % (max)

typedef enum {
    Cache_Full = 1,
    No_Data = 2,
    Hook_Error = 3,
} Statue;

typedef struct {
    char channel[Channel_Size];
    size_t size;
    size_t max;

    volatile int flags[300];
    volatile uint32_t index_r;
    volatile uint32_t index_w;     // free node tail
    volatile int app_status;
    char pending[60];
    char datas[0];
} shm_data_t;

#define HEAD_SIZE sizeof(struct shm_data_t)


class ringbuf_t{

public:
    ringbuf_t();
    //virtual ~ringbuf_t();
    int ringbuf_init(size_t size, size_t n, int key);
    int ringbuf_pop_unlock(void);
    int ringbuf_set_next(void);
    void * shm_getaddr_from_idx(void);

    shm_data_t *rb_shm;
protected:
    int rb_channel_id;
    shmctx_t rb_mutex_r;
    shmctx_t rb_mutex_w;

private:

};

#endif /* _IPC_READER_H_ */
