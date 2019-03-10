#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "array.h"

void array_ramdom(int *arr, int count)
{
	int i;
	if(arr == NULL)
		return;
	srand((unsigned int)time(NULL));
	for (i = 0; i<count; i++)
	{
		int num = rand() % (count);
		int temp = arr[i];
		arr[i] = arr[num];
		arr[num] = temp;
	}
}

void array_print(int *arr, int count)
{
	int i;
	if(arr == NULL)
		return;
	for (i = 0; i<count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//support memery overlap
void array_copy(int *from, int *to, int count)
{
	int i;
	if(from == NULL || to == NULL)
		return;
	if(from > to)
	{
		for (i = 0; i<count; i++)
		{
			to[i] = from[i];
		}
	}
	else
	{
		for (i = count-1; i>= 0; i--)
		{
			to[i] = from[i];
		}
	}

}


