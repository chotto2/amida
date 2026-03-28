/*
 * amida - Divisor finder using 45-degree Mirror Conjecture
 *
 * This program finds divisors of integers using a unique geometric approach
 * inspired by the Japanese "Amida-kuji" (ladder lottery) pattern.
 *
 * Key Features:
 * - Finds all divisors without using division or modulo operations
 * - Based on the "45-degree Mirror Conjecture" (未証明予想)
 * - Propagates divisor information from origin (n=0) to all integers
 * - Uses bitwise operations and propagation rules only
 *
 * Algorithm:
 * 1. Initialize origin (n=0) with all values 1..M_MAX
 * 2. Propagate: if divs[n] has bit m set, then divs[n+m] also has bit m
 * 3. This creates a geometric pattern resembling 45-degree paths
 *
 * Copyright (c) 2026 chotto2
 * License: MIT (or your preferred license)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DSP_MAX (128)
//#define N_MAX (128)
#define N_MAX (1000000)
#define M_MAX (N_MAX)
#define D_MAX (256)	// d(720720)=240

typedef struct {
	uint32_t div[D_MAX];
	int cnt;
} DIVS, *pDIVS;
DIVS divs[N_MAX+1];

/**
 * @brief Main entry point
 */
int32_t main()
{
	uint64_t m;
	uint64_t n;
	uint64_t d;
	int32_t ret = 0;
	uint64_t ofs;
        uint32_t count;
        uint64_t pre;

	/*--- init ---*/
        for (n = 1; n <= N_MAX; n++) {
                divs[n].div[0] = n;
                divs[n].cnt = 1;
        }

	/*--- other ---*/
        for (n = 1; n <= N_MAX; n++) {
                for (ofs = 0; ofs < M_MAX; ofs++) {
                        m = divs[n].div[ofs];
                        if (m == 0) {
                                break;
                        }
                        else {
                                if ((n+m) > N_MAX) {
                                        ;
                                }
                                else {
                                        count = divs[n+m].cnt;
                                        divs[n+m].div[count] = m;
                                        divs[n+m].cnt++;
                                }
                        }
                }
        }

	/*--- for printing ---*/
	printf("      n:   d(n):divisors2(n, %d)\n", DSP_MAX);
	printf("%7lu:%7d:", 0, N_MAX);
	for (m = 1; m <= DSP_MAX; m++) printf("*");
	printf("...\n");
        for (n = 1; n <= N_MAX; n++) {
		printf("%7lu:%7d:", n, divs[n].cnt);
		pre = 0;
                for (int cnt = divs[n].cnt; cnt > 0; cnt--) {
			m = divs[n].div[cnt-1];
			if (m > DSP_MAX) break;
			if (pre) {
				int i;
				for (i = 0; i < (m - pre - 1); i++) {
					printf(" ");
				}
			}
			printf("*");
			pre = m;
		}
		printf("\n");
	}

	return ret;
}


