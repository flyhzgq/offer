#ifndef _STACK_H_
#define _STACK_H_

#include "tree.h"

#define STACK_NUM 204800

int stack_put(struct tree *t);
struct tree * stack_get();
int stack_size();


#endif

