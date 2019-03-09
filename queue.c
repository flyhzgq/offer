#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "queue.h"

struct tree * queue_array[QUEUE_NUM] = {0};
int queue_num = 0;
int queue_in = 0;
int queue_out = 0;

int queue_put(struct tree *t)
{
	if(queue_num == QUEUE_NUM)
		return -1;
	queue_num++;
	queue_array[queue_in++] = t;
	if(queue_in == QUEUE_NUM)
		queue_in = 0;
	return 0;
}

struct tree * queue_get()
{
	struct tree *t;
	if(queue_num == 0)
		return NULL;
	queue_num--;
	t = queue_array[queue_out++];
	if(queue_out == QUEUE_NUM)
		queue_out = 0;
	return t;
}

int queue_size()
{
	return queue_num;
}



