#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sort.h"
#include "array.h"

#define SORT_MERGE_MAX 2048
int sort_merge_array[SORT_MERGE_MAX];

int partition(int *s, int start, int end)
{
	int i = start,j = end+1;
	int tmp;
	while(1)
	{
		
		while(s[++i] < s[start])
		{
			if(i == end)
				break;
		}
		while(s[--j] > s[start])
		{
			if(j == start) //can not start+1
				break;
		}
		if(i < j)
		{
			tmp = s[i];
			s[i] = s[j];
			s[j] = tmp;
		}
		else
			break;

	}
	tmp = s[start];
	s[start] = s[j];
	s[j] = tmp;
	return j;
}

void sort_quick_(int *s, int start, int end)
{
	int pos;
	if(start >= end)
		return;
	pos = partition(s, start, end);
	//printf("pos:%d\n", pos);
	sort_quick_(s, start, pos - 1);
	sort_quick_(s, pos + 1, end);
}

void sort_quick(int s[], int size)
{
	if(s == NULL)
		return;
	if(size <= 1)
		return;
	sort_quick_(s, 0, size - 1);
}

void merge(int *s, int start, int mid, int end)
{
	int i = start,j = mid+1;
	int index = start;
	for(i=start;i<=end;i++)
		sort_merge_array[i] = s[i];
	i = start;
	while( i <= mid && j <= end)
	{
		if(sort_merge_array[i] < sort_merge_array[j])
			s[index++] = sort_merge_array[i++];
		else
			s[index++] = sort_merge_array[j++];
	}
	while(i <= mid)
		s[index++] = sort_merge_array[i++];
	while(j <= end)
		s[index++] = sort_merge_array[j++];
}

void sort_merge_resursion(int *s, int start, int end)
{
	int mid;
	if(start >= end)
		return;
	mid = start + (end - start)/2;
	sort_merge_resursion(s, start, mid);
	sort_merge_resursion(s, mid+1, end);
	merge(s, start, mid, end);
}

void sort_merge_loop(int s[], int size)
{
	int loop = 1;
	int i, mid, end;
	
	if(s == NULL)
		return;
	if(size <= 1)
		return;
	if(size > SORT_MERGE_MAX)
	{
		printf("sort merge do not support number more than %d\n", SORT_MERGE_MAX);
		return;
	}

	while(loop < size)
	{
		i = 0;
		while(1)
		{
			if(loop*2*i > (size - 1))
				break;
			mid = loop*2*i+loop-1;
			if( mid > (size - 1))
				mid = size - 1;
			end = loop*2 - 1 + loop*2*i;
			if( end > (size - 1))
				end = size - 1;
			merge(s, loop*2*i, mid, end);
			//printf("====%d %d mid:%d end:%d\n", loop, i, mid, end);
			//array_print(s, size);
			i++;
		}
		loop *= 2;
	}
	
}


void sort_merge(int s[], int size)
{
	if(s == NULL)
		return;
	if(size <= 1)
		return;
	if(size > SORT_MERGE_MAX)
	{
		printf("sort merge do not support number more than %d\n", SORT_MERGE_MAX);
		return;
	}
	sort_merge_resursion(s, 0, size - 1);
}

