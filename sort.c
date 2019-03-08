#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sort.h"

int partition(int *s, int start, int end)
{
	int i = start + 1,j = end;
	int tmp;
	while(1)
	{
		
		while(i <= end && i > start)
		{
			if(s[i] > s[start])
				break;
			i++;
		}
		while(j >start && j <= end)
		{
			if(s[j] < s[start])
				break;
			j--;
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

void sort_merge(int s[], int size)
{
	
}

