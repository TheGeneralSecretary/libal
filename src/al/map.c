#include "al/map.h"
#include "al/malloc.h"
#include "al/string.h"
#include <string.h>
#include <malloc.h>

static struct al_map_entry *al_create_entry(const char *key, const void *value,
					    size_t vlen)
{
	struct al_map_entry *entry = al_malloc(sizeof(struct al_map_entry));
	entry->key = al_strdup(key);
	entry->value = al_malloc(vlen);
	memcpy(entry->value, value, vlen);
	return entry;
}

static void al_insert_entry(struct al_map **map, struct al_map_entry *entry)
{
	/* if map is uninitalized or empty */
	if (!(*map) || !((*map)->entry)) {
		if (!(*map))
			*map = al_map_init();

		(*map)->entry = entry;
		(*map)->left = NULL;
		(*map)->right = NULL;
	} else {
		char *key = (*map)->entry->key;

		if (strcmp(entry->key, key) < 0)
			al_insert_entry(&((*map)->left), entry);
		else if (strcmp(entry->key, key) > 0)
			al_insert_entry(&((*map)->right), entry);
	}
}

static struct al_map_entry *al_get_entry(struct al_map *map, const char *key)
{
	if (!map || !map->entry)
		return NULL;

	if (!strcmp(key, map->entry->key))
		return map->entry;
	else if (strcmp(key, map->entry->key) < 0)
		return al_get_entry(map->left, key);
	else if (strcmp(key, map->entry->key) > 0)
		return al_get_entry(map->right, key);

	return NULL;
}

struct al_map *al_map_init(void)
{
	struct al_map *map = al_malloc(sizeof(struct al_map));
	map->entry = NULL;
	map->left = NULL;
	map->right = NULL;
	return map;
}

void al_map_insert(struct al_map *map, const char *key, const void *value,
		   size_t vlen)
{
	struct al_map_entry *entry = al_create_entry(key, value, vlen);
	al_insert_entry(&map, entry);
}

void *al_map_get(struct al_map *map, const char *key)
{
	struct al_map_entry *entry = al_get_entry(map, key);
	if (!entry)
		return NULL;

	return entry->value;
}

void al_map_free(struct al_map *map)
{
	if (!map)
		return;

	if (map->left)
		al_map_free(map->left);

	if (map->right)
		al_map_free(map->right);

	if (map->entry) {
		free(map->entry->key);
		free(map->entry->value);
		free(map->entry);
	}

	free(map);
}
