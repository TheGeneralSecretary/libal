#include "al/string.h"
#include "al/malloc.h"
#include <string.h>

char *al_strdup(const char *s)
{
	size_t len = strlen(s) + 1;
	char *dup = al_malloc(len);

	if (dup)
		strncpy(dup, s, len);

	return dup;
}

char *al_strndup(const char *s, size_t n)
{
	char *dup = al_malloc(n + 1);
	if (dup)
		strncpy(dup, s, n);

	dup[n] = '\0';
	return dup;
}
