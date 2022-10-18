#ifndef _AL_MAP_H_
#define _AL_MAP_H_

#include <stddef.h>

struct al_map_entry {
	char *key;
	void *value;
};

struct al_map {
	struct al_map_entry *entry;
	struct al_map *left;
	struct al_map *right;
};

struct al_map *al_map_init(void);
void al_map_insert(struct al_map *map, const char *key, const void *value,
		   size_t vlen);
void *al_map_get(struct al_map *map, const char *key);
void al_map_free(struct al_map *map);

#endif
