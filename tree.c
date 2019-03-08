#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "stack.h"
#include "queue.h"
#include "tree.h"

#ifdef TREE_COMPARE_TEST
int tree_test[TEST_MAX];
int tree_test_r[TEST_MAX];
int tree_index;
int tree_index_r;
#endif

struct tree * tree_insert(struct tree *t, int value)
{
	if(t == NULL)
	{
		t = malloc(sizeof(struct tree));
		if(t == NULL)
		{
			printf("tree_insert malloc error\n");
			return NULL;
		}
		else
		{
			t->value = value;
			t->left = NULL;
			t->right = NULL;
		}
	}
	else
	{
		if(value > t->value)
			t->right = tree_insert(t->right, value);
		else
			t->left = tree_insert(t->left, value);
	}

	return t;
}

struct tree * tree_init(int *v, int size)
{
	struct tree *t = NULL;
	int i;
	for( i=0; i<size; i++ )
	{
		t = tree_insert(t, v[i]);
		if(t == NULL)
			break;
	}

	return t;
}

void tree_deinit(struct tree * t)
{
	if(t == NULL)
		return;
	tree_deinit(t->left);
	tree_deinit(t->right);
	free(t);
}


void tree_pretraveres_resursion(struct tree *t)
{
	if(t == NULL)
		return;
#ifdef TREE_COMPARE_TEST
	tree_test_r[tree_index_r++] = t->value;
#else
	printf("%d ", t->value);
#endif
	tree_pretraveres_resursion(t->left);
	tree_pretraveres_resursion(t->right);
}

void tree_intraveres_resursion(struct tree *t)
{
	if(t == NULL)
		return;
	tree_intraveres_resursion(t->left);
#ifdef TREE_COMPARE_TEST
	tree_test_r[tree_index_r++] = t->value;
#else
	printf("%d ", t->value);
#endif
	tree_intraveres_resursion(t->right);
}

void tree_posttraveres_resursion(struct tree *t)
{
	if(t == NULL)
		return;
	tree_posttraveres_resursion(t->left);
	tree_posttraveres_resursion(t->right);
#ifdef TREE_COMPARE_TEST
	tree_test_r[tree_index_r++] = t->value;
#else
	printf("%d ", t->value);
#endif

}

void tree_pretraveres_loop(struct tree *t)
{
	struct tree *p = t;
	while(p)
	{
#ifdef TREE_COMPARE_TEST
		tree_test[tree_index++] = p->value;
#else
		printf("%d ", p->value);
#endif
		if(p->right)
			stack_put(p->right);
		p = p->left;
		if(!p)
		{
			p = stack_get();
		}
	}
}

void tree_intraveres_loop(struct tree *t)
{
	struct tree *p = t;
	while(p)
	{
		if(p->left)
		{
			stack_put(p);
			p = p->left;
		}
		else
		{
#ifdef TREE_COMPARE_TEST
			tree_test[tree_index++] = p->value;
#else
			printf("%d ", p->value);
#endif
			if(p->right)
				p = p->right;
			else
			{	while(1)
				{
					p = stack_get();
					if(!p)
						break;
#ifdef TREE_COMPARE_TEST
					tree_test[tree_index++] = p->value;
#else
					printf("%d ", p->value);
#endif
					p = p->right;
					if(p)
						break;
				}
			}
		}
	}
}


void tree_posttraveres_loop(struct tree *t)
{
	struct tree *p = t;
	struct tree *last = NULL;
	while(p)
	{
		if(p->left)
		{
			stack_put(p);
			p = p->left;
		}
		else
		{
			if(p->right)
			{
				stack_put(p);
				p = p->right;
			}
			else
			{
#ifdef TREE_COMPARE_TEST
				tree_test[tree_index++] = p->value;
#else
				printf("%d ", p->value);
#endif
				while(1)
				{
					last = p;
					p = stack_get();
					if(!p)
						break;
					if(p->left && p->right)
					{
						if(last == p->left)
						{
							stack_put(p);
							p = p->right;
							break;
						}
						else
						{
#ifdef TREE_COMPARE_TEST
							tree_test[tree_index++] = p->value;
#else
							printf("%d ", p->value);
#endif
						}
					}
					else
					{
						if(!p->right || !p->left)
						{
#ifdef TREE_COMPARE_TEST
							tree_test[tree_index++] = p->value;
#else
							printf("%d ", p->value);
#endif
						}
					}
				}
			}
		}
	}
}

void tree_leveltraveres(struct tree *t)
{
	struct tree *p = t;
	if(!p)
		return;
	queue_put(p);
	while(1)
	{
		p = queue_get();
		if(!p)
			break;

		printf("%d ", p->value);
		
		if(p->left)
			queue_put(p->left);
		if(p->right)
			queue_put(p->right);

	}
		
}

