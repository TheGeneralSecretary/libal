#include "al/queue.h"
#include "al/malloc.h"
#include <string.h>
#include <malloc.h>

static struct al_qnode *al_create_node(void *data)
{
	struct al_qnode *node = al_malloc(sizeof(struct al_qnode));
	node->data = data;
	node->next = NULL;
	return node;
}

struct al_queue *al_queue_init(void)
{
	struct al_queue *q = al_malloc(sizeof(struct al_queue));
	q->front = q->rear = NULL;
	return q;
}

void al_queue_push(struct al_queue *q, const void *data, size_t len)
{
	void *tmp = al_malloc(len);
	memcpy(tmp, data, len);

	struct al_qnode *node = al_create_node(tmp);

	if (!q->rear) {
		q->front = q->rear = node;
		return;
	}

	q->rear->next = node;
	q->rear = node;
}

void *al_queue_pop(struct al_queue *q)
{
	if (!q->front)
		return NULL;

	struct al_qnode *node = q->front;
	q->front = q->front->next;

	if (!q->front)
		q->rear = NULL;

	void *data = node->data;
	free(node);
	return data;
}

void *al_queue_peek(struct al_queue *q)
{
	if (!q->front)
		return NULL;

	return q->front->data;
}

void al_queue_free(struct al_queue *q)
{
	if (q) {
		if (!q->front) {
			free(q);
			return;
		}

		void *data = al_queue_pop(q);
		while (data) {
			free(data);
			data = al_queue_pop(q);
		}

		free(q);
	}
}
