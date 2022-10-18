#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "al/string.h"
#include "al/queue.h"
#include "al/map.h"

int test_string(void)
{
	char* str1 = al_strdup("StrMan");
	assert(!strcmp(str1, "StrMan"));

	char* str2 = al_strndup("JACKY", 3);
	assert(!strcmp(str2, "JAC"));

	free(str1);
	free(str2);
	return 1;
}

int test_queue(void)
{
	struct al_queue* q = al_queue_init();
	al_queue_push(q, "MAX", 4);
	al_queue_push(q, "JACK", 5);
	al_queue_push(q, "MAXMAN", 7);

	char* p1 = al_queue_peek(q);
	if(p1)
		assert(!strcmp(p1, "MAX"));

	char* d1 = al_queue_pop(q);
	if(d1)
		assert(!strcmp(d1, "MAX"));

	free(d1);
	al_queue_free(q);
	return 1;
}

int test_map(void)
{
	struct al_map* map = al_map_init();
	al_map_insert(map, "Max", "Maxi", 5);
	al_map_insert(map, "Jack", "Jackson", 8);
	al_map_insert(map, "Anti", "Antiv", 6);

	char* g1 = al_map_get(map, "Max");
	if(g1)
		assert(!strcmp(g1, "Maxi"));

	char* g2 = al_map_get(map, "Jack");
	if(g2)
		assert(!strcmp(g2, "Jackson"));

	char* g3 = al_map_get(map, "Anti");
	if(g3)
		assert(!strcmp(g3, "Antiv"));

	al_map_free(map);
	return 1;
}

int main(void)
{
	assert(test_string() == 1);
	assert(test_queue() == 1);
	assert(test_map() == 1);
}
