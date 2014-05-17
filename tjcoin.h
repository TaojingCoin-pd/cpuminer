#ifndef __TJCOIN_H__
#define __TJCOIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scanhash_tjcoin(int thr_id, uint32_t *pdata,
        const uint32_t *ptarget,
        uint32_t max_nonce, unsigned long *hashes_done);

#endif /* __TJCOIN_H__ */

