#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//#define TREE_COMPARE_TEST

/* ****************************************** */

#define STACK_NUM 204800
struct tree * stack_array[STACK_NUM] = {0};
int stack_num = 0;

int stack_put(struct tree *t)
{
	if(stack_num == STACK_NUM)
		return -1;
	stack_array[stack_num++] = t;
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

/* ****************************************** */

/* ****************************************** */

#define QUEUE_NUM 204800
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

/* ****************************************** */


#ifdef TREE_COMPARE_TEST
#define TEST_MAX 128
int tree_test[TEST_MAX];
int tree_test_r[TEST_MAX];
int tree_index;
int tree_index_r;
#endif

struct tree
{
	int value;
	struct tree *left;
	struct tree *right;
};

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

int array_ramdom(int *arr, int count)
{
	int i;
	srand((unsigned int)time(NULL));
	for (i = 0; i<count - 1; i++)
	{
		int num = i + rand() % (count - 1 - i);
		int temp = arr[i];
		arr[i] = arr[num];
		arr[num] = temp;
	}
#ifndef TREE_COMPARE_TEST
	printf("array_ramdom:");
	for (i = 0; i<count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
#endif
}

int array_print(int *arr, int count)
{
	int i;
	for (i = 0; i<count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int main()
{

#ifdef STACK_TEST
	struct tree *p = (struct tree *)1;
	stack_put(p);
	p = (struct tree *)2;
	stack_put(p);
	p = (struct tree *)3;
	stack_put(p);

	printf("stack:");
	while(stack_size())
	{
		p = stack_get();
		printf("%p ", p);
	}
	printf("\n");
	return 0;
#endif

#ifdef QUEUE_TEST
	struct tree *p = (struct tree *)1;
	queue_put(p);
	p = (struct tree *)2;
	queue_put(p);
	p = (struct tree *)3;
	queue_put(p);

	printf("queue:");
	while(queue_size())
	{
		p = queue_get();
		printf("%p ", p);
	}
	printf("\n");
	return 0;
#endif

	int tree_value[] = {6, 7, 0, 8, 9, 4, 2, 3, 5, 1, 11,12,13,14,15,16,17,18,19,20};
	//int tree_value[] = {6, 7, 0, 8, 9, 4, 2, 3, 5, 1};

	struct tree *t;
	while(1)
	{
		array_ramdom(tree_value, sizeof(tree_value)/sizeof(int));

#ifdef TREE_COMPARE_TEST
		tree_index_r = 0;
		tree_index = 0;
#endif
		t = tree_init(tree_value, sizeof(tree_value)/sizeof(int));
		printf("tree_traveres:");
		tree_posttraveres_resursion(t);
#ifndef TREE_COMPARE_TEST
		printf("\n");
#endif

		printf("tree_traveres:");
		tree_posttraveres_loop(t);
#ifndef TREE_COMPARE_TEST
		printf("\n");
#endif

#ifndef TREE_COMPARE_TEST
		printf("tree_level_traveres:");
		tree_leveltraveres(t);
		printf("\n");
#endif

#ifdef TREE_COMPARE_TEST
		static int count = 0, count_err = 0;
		int i;
		for(i=0;i<sizeof(tree_value)/sizeof(int);i++)
		{
			if(tree_test[i] != tree_test_r[i])
			{
				count_err++;
				printf("=========================\n");
				array_print(tree_value, sizeof(tree_value)/sizeof(int));
				array_print(tree_test_r, sizeof(tree_value)/sizeof(int));
				array_print(tree_test, sizeof(tree_value)/sizeof(int));
				break;
			}
		}
		count++;
		if((count % 10) == 0)
			printf("result:%d/%d\n", count_err, count);
#endif
		tree_deinit(t);
		usleep(100*000);
	}

	return 0;
}

