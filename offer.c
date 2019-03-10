#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sort.h"
#include "array.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "search.h"

void test_stack()
{
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
}

void test_queue()
{
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
}

void test_tree(int *tree_value, int count)
{
	struct tree *t;
	while(1)
	{
		array_ramdom(tree_value, count);

#ifdef TREE_COMPARE_TEST
		tree_index_r = 0;
		tree_index = 0;
#endif
		t = tree_init(tree_value, count);
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
		for(i=0;i<count;i++)
		{
			if(tree_test[i] != tree_test_r[i])
			{
				count_err++;
				printf("=========================\n");
				array_print(tree_value, count);
				array_print(tree_test_r, count);
				array_print(tree_test, count);
				break;
			}
		}
		count++;
		if((count % 10) == 0)
			printf("result:%d/%d\n", count_err, count);
#endif
		tree_deinit(t);
		usleep(500*1000);
	}

}

void test_sort(int *tree_value, int count)
{
	while(1)
	{
		printf("test sort\n");
		array_ramdom(tree_value, count);
		array_print(tree_value, count);
		//sort_quick(tree_value, count);
		//sort_merge(tree_value, count);
		sort_merge_loop(tree_value, count);
		array_print(tree_value, count);
		usleep(500*1000);
	}

}

void test_search(int *tree_value, int count)
{
	int index;
	int key= 0;
	sort_quick(tree_value, count);
	array_print(tree_value, count);
	while(1)
	{
		printf("test search %d\n", key);
		index = search_binary(tree_value, count, key++);
		printf("index:%d\n", index);
		usleep(500*1000);
	}

}


void useage()
{
	printf("choose num to test:\n");
	printf("1. test stack\n");
	printf("2. test queue\n");
	printf("3. test tree traveres\n");
	printf("4. test sort\n");
	printf("5. test search\n");
}
int main()
{

	int tree_value[] = {6, 7, 0, 8, 9, 4, 2, 3, 5, 1, 11,12,13,14,15,16,17,18,19,20};
	//int tree_value[] = {6, 7, 0, 8, 9, 4, 2, 3, 5, 1};
	int c;
	useage();
	c= getchar();
	switch (c)
	{
	case '1':
		test_stack();
		break;
	case '2':
		test_queue();
		break;
	case '3':
		test_tree(tree_value, sizeof(tree_value)/sizeof(int));
		break;
	case '4':
		test_sort(tree_value, sizeof(tree_value)/sizeof(int));
		break;
	case '5':
		test_search(tree_value, sizeof(tree_value)/sizeof(int));
		break;
	default:
		break;
	}

	return 0;
}

