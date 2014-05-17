#include "cpuminer-config.h"
#include "miner.h"
#include "ocean.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BEGIN(a)            ((char*)&(a))
int scanhash_tjcoin(int thr_id, uint32_t *pdata,
        const uint32_t *ptarget,
        uint32_t max_nonce, unsigned long *hashes_done)
{
        uint32_t data[20], hash[8], target_swap[8];
        volatile unsigned char *hashc = (unsigned char *) hash;
        volatile unsigned char *datac = (unsigned char *) data;
        volatile unsigned char *pdatac = (unsigned char *) pdata;
        uint32_t n = pdata[19] - 1;
        int i=0;

        /* byte swap it */
        for(int z=0;z<20;z++) {
            datac[(z*4)  ] = pdatac[(z*4)+3];
            datac[(z*4)+1] = pdatac[(z*4)+2];
            datac[(z*4)+2] = pdatac[(z*4)+1];
            datac[(z*4)+3] = pdatac[(z*4)  ];
        }

        do {

              data[19] = ++n;
                ocean((unsigned char *)data, (unsigned char *)hash);
				if(fulltest(hash, ptarget)) {
					*hashes_done = n - pdata[19] + 1;
					pdatac[76] = datac[79];
					pdatac[77] = datac[78];
					pdatac[78] = datac[77];
					pdatac[79] = datac[76];
					return 1;
            }
		} while (n < max_nonce && !work_restart[thr_id].restart);
        *hashes_done = n - pdata[19] + 1;
        pdata[19] = n;
        return 0;
}

