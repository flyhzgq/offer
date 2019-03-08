#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "array.h"

void array_ramdom(int *arr, int count)
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
}

void array_print(int *arr, int count)
{
	int i;
	for (i = 0; i<count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

