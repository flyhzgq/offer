#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "tree.h"

#define QUEUE_NUM 204800

int queue_put(struct tree *t);
struct tree * queue_get();
int queue_size();


#endif

