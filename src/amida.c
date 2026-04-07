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
 * @note v1.3.0 (2026-04-07): Up to 3,000,000
 *       1. Extended the upper limit of integers from 2,000,000 to 3,000,000
 *       2. Expanded the memory that holds divisors
 *          - Note: d(2882880)=336 is the maximum within the range 0–3,000,000, so the array size is set to 344. (approx. 4.2GB)
 *
 * @note v1.2.0 (2026-04-04): Up to 2,000,000
 *       1. Extended the upper limit of integers from 1,000,000 to 2,000,000
 *       2. Expanded the memory that holds divisors
 *          - Note: d(1441440)=288 is the maximum within the range 0–2,000,000, so the array size is set to 296. (approx. 2.4GB)
 *          - Note: Change to dynamic memory(calloc)
 *
 * @note v1.1.0 (2026-04-01): Up to 1,000,000
 *       1. Extended the upper limit of integers from 128 to 1,000,000
 *       2. Removed GMP bit operations
 *       3. Improved memory efficiency by storing divisor values in an array
 *          - Note: d(720720)=240 is the maximum within the range 0–1,000,000, so the array size is set to 256. (approx. 1GB)
 *          - Note: Stored in ascending order, with NULL(0) as the terminator
 *
 * @note v1.0.0 (2026-01-31): Add amida command
 *       1. Plots the divisors of integers from 0 to 128
 *       2. Data retention by GMP bit operation
 *       3. No divisors exist in the VOID region.
 *
 * Copyright (c) 2026 chotto2
 * License: MIT (or your preferred license)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define D_MAX (344)	// d(2882880)=336
#define DSP_MAX (128)
#define N_MAX (3000000)
#define M_MAX (N_MAX)

typedef struct {
	uint32_t div[D_MAX];
	int cnt;
} DIVS, *pDIVS;
pDIVS divs;

int benchmark_mode = 0;

/**
 * @brief Main entry point
 */
int32_t main(int argc, char *argv[])
{
	uint64_t m;
	uint64_t n;
	uint64_t d;
	int32_t ret = 0;
	uint64_t ofs;
        uint64_t pre;

	/*--- check argv ---*/
	for (int i = 1; i < argc; i++) {
    	if (strcmp(argv[i], "--benchmark") == 0) {
        	benchmark_mode = 1;
 	   }
	}

	/*--- divs[N_MAX+1] ---*/
	divs = calloc(N_MAX+1, sizeof(DIVS));
	if (divs == NULL) {
		printf("ERR: NULL = calloc(%d, %d)\n", N_MAX+1, sizeof(DIVS));
		return -1;
	}

	/*--- init ---*/
        for (n = 1; n <= N_MAX; n++) {
                divs[n].div[0] = n;
                divs[n].cnt = 1;
        }

	/*--- amida process ---*/
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
                                        if (divs[n+m].cnt < D_MAX) {
                                        	divs[n+m].div[divs[n+m].cnt] = m;
					}
                                        divs[n+m].cnt++;
                                }
                        }
                }
        }

	/*--- for printing ---*/
	if (!benchmark_mode) {
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
					for (int i = 0; i < (m - pre - 1); i++) {
						printf(" ");
					}
				}
				printf("*");
				pre = m;
			}
			printf("\n");
		}
	}

	free(divs);

	return ret;
}


