#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "stack.h"

struct tree * stack_array[STACK_NUM] = {0};
int stack_num = 0;

int stack_put(struct tree *t)
{
	if(stack_num == STACK_NUM)
		return -1;
	stack_array[stack_num++] = t;
	return 0;
}

struct tree * stack_get()
{
	if(stack_num == 0)
		return NULL;
	return stack_array[--stack_num];
}

int stack_size()
{
	return stack_num;
}


