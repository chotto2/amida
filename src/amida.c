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
#include <gmp.h>

#define DSP_MAX (128)
#define N_MAX (128)
#define M_MAX (N_MAX)

typedef struct {
	mpz_t div;
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

	/*--- init ---*/
	for (n = 0; n <= N_MAX; n++)
		mpz_init(divs[n].div);

	/*--- base ---*/
	for (m = 1; m <= M_MAX; m++) {
		divs[0].cnt++;
		ofs = m - 1;
		mpz_setbit(divs[0].div, ofs);
	}

	/*--- other ---*/
	for (n = 0; n <= N_MAX; n++) {
		for (m = 1; m <= M_MAX; m++) {
			if ((n+m) > N_MAX) break;
			ofs = m - 1;
			if (mpz_tstbit(divs[n  ].div, ofs)) {
			    mpz_setbit(divs[n+m].div, ofs);
			    divs[n+m].cnt++;
			}
		}
	}

	/*--- for printing ---*/
	printf("      n:   d(n):divisors2(n, %d)\n", M_MAX);
	for (n = 0; n <= N_MAX; n++) {
		printf("%7llu:%7d:", n, divs[n].cnt);
		for (d = 1; d <= DSP_MAX; d++) {
			ofs = d - 1;
			printf("%s", (mpz_tstbit(divs[n].div, ofs) != 0)? "*": " ");
		}
		printf("%s", (divs[n].cnt >= DSP_MAX)? "...": "");
		printf("\n");
	}

	/*--- clear ---*/
	for (n = 0; n <= N_MAX; n++)
		mpz_clear(divs[n].div);

	return ret;
}


