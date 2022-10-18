#include "al/malloc.h"
#include <stdlib.h>
#include <stdio.h>

void *al_malloc(size_t size)
{
	void *mem = calloc(size, 1);
#ifndef NMALLOC_ABORT
	if (!mem) {
		perror("malloc");
		abort();
	}
#endif
	return mem;
}
