#ifndef _AL_QUEUE_H_
#define _AL_QUEUE_H_

#include <stddef.h>

struct al_qnode {
	void *data;
	struct al_qnode *next;
};

struct al_queue {
	struct al_qnode *front;
	struct al_qnode *rear;
};

struct al_queue *al_queue_init(void);
void al_queue_push(struct al_queue *q, const void *data, size_t len);
void *al_queue_pop(struct al_queue *q);
void *al_queue_peek(struct al_queue *q);
void al_queue_free(struct al_queue *q);

#endif
