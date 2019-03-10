#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "search.h"
#include "array.h"

int search_binary_resursion(int s[], int start, int end, int key)
{
	int mid, index;
	if(s == NULL)
		return -1;
	if(start > end)
		return -1;

	mid = start + (end - start)/2;
	if(s[mid] > key)
	{
		index= search_binary_resursion(s, start, mid-1, key);
	}
	else if(s[mid] < key)
	{
		index = search_binary_resursion(s, mid+1, end, key);
	}
	else
		index = mid;
	return index;
}

int search_binary_loop(int s[], int start, int end, int key)
{
	int index = -1;
	int mid;
	if(s == NULL)
		return -1;

	while(start <= end)
	{
		mid = start + (end - start)/2; //0k
		//mid = (start + end)/2; //0k
		if(s[mid] > key)
			end = mid-1;
		else if(s[mid] < key)
			start = mid+1;
		else
		{
			index = mid;
			break;
		}
	}
	return index;
}

int search_binary(int s[], int count, int key)
{
	int index;
	//index = search_binary_resursion(s, 0, count-1, key);
	index = search_binary_loop(s, 0, count-1, key);
	return index;
}

