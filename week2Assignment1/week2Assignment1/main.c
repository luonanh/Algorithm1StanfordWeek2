//
//  main.c
//  week2Assignment1
//
//  Created by Anh Luong on 7/28/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#define MAXARRAY        100000

typedef enum {FALSE, TRUE} BOOLEAN;

/*
#ifdef DEBUG
#undef DEBUG
#endif
 */

#ifdef DEBUG
#undef DEBUG
//#define DEBUG 0
#endif

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT
#endif

//#define ERROR_PRINT(args ...) if (DEBUG) fprintf(stderr, args)

//#define DEBUG 1
static int countCompare = 0;

int partition(int *A, int left, int right, int pivot);
void swap(int *A, int src, int dest);
void myqsort(int *A, int left, int right);
void printArray(int *A, int left, int right);
BOOLEAN isIntArraySortedAscending(int *A, int left, int right);

int main(int argc, const char * argv[]) {
    int i, num;
    FILE *fp;
    int inarray[MAXARRAY];
    
    if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("read failed\n");
        return 1;
    }
    
    for (i = 0; fscanf(fp, "%d", &inarray[i]) != EOF; i++) {
        DEBUG_PRINT("Number read: %d\n", inarray[i]);
    }
    
    num = i;
    printf("Total number of elements is %d\n", num);
    
    myqsort(inarray, 0, num-1);
    
    for (i = 0; i < num; i++) {
        //DEBUG_PRINT("Element %dth is: %d\n", i, inarray[i]);
    }

    assert(isIntArraySortedAscending(inarray, 0, num-1) == TRUE);
    printf("Total comparisons is %d\n", countCompare);
    fclose(fp);
    return 0;
}

int choosePivotFirst(int *A, int left, int right)
{
    return left;
}

int choosePivotLast(int *A, int left, int right)
{
    return right;
}

int choosePivotMedian(int *A, int left, int right)
{
    int median = (left + right) / 2;
    int m, l, r;
    
    m = *(A + median);
    l = *(A + left);
    r = *(A + right);
    
    if ((l <= m && m <= r) || (r <= m && m <= l))
        return median;
    else if ((m <= l && l <= r) || (r <= l && l <= m))
        return left;
    else    // if ((m <= r && r<= l) || (l <= r && r <= m))
        return right;
}

int partition(int *A, int left, int right, int pivot)
{
    int p, i, j;    // p is pivot element, i is position of the 1st element in the partitioned part that is not smaller than element at pivot, j is the start of the unpartitioned part
    
    p = *(A + pivot);
    swap(A, left, pivot);
    DEBUG_PRINT("=========\n");
    DEBUG_PRINT("Start partition function, pivot is %d, p is %d, left is %d, right is %d\n", pivot, p, left, right);
    printArray(A, left, right);
    for (i = j = left + 1; j <= right; j++) {
        if (*(A + j) < p) {
            DEBUG_PRINT("%dth %d is smaller than %d\n", j, *(A + j), p);
            swap(A, i++, j);
        }
    }
    printArray(A, left, right);
    DEBUG_PRINT("i is %d\n", i);
    swap(A, left, i - 1);
    printArray(A, left, right);
    DEBUG_PRINT("End partition function\n");
    DEBUG_PRINT("=========\n");
    return i - 1;   // return the position of the pivot after partitioning.
}

void swap(int *A, int src, int dest)
{
    int temp;
 
    DEBUG_PRINT("Swap %d with %d\n", src, dest);
    temp = *(A + src);
    *(A + src) = *(A + dest);
    *(A + dest) = temp;
}

void myqsort(int *A, int left, int right)
{
    int p;
    
    //if (left >= right || (right - left) == 1)
    if (left >= right)
        return;

    DEBUG_PRINT("-------> qsort with left %d right %d\n", left, right);
    printArray(A, left, right);
    p = choosePivotMedian(A, left, right);
    DEBUG_PRINT("choosePivotFirst() p = %d\n", p);
    p = partition(A, left, right, p);
    countCompare += right - left;
    DEBUG_PRINT("**************countCompare = %d with left = %d and right = %d\n", countCompare, left, right);
    DEBUG_PRINT("After partition() p = %d\n", p);
    printArray(A, left, right);
    //countCompare += (left < p - 1) ? p - 1 - left : 0;
    //DEBUG_PRINT("countCompare 1st half is %d, left is %d, right is %d\n", countCompare, left, p - 1);
    myqsort(A, left, p - 1);
    
    //countCompare += (p + 1 < right) ? right - p - 1 : 0;
    //DEBUG_PRINT("countCompare 2nd half is %d, left is %d, right is %d\n", countCompare, p + 1, right);
    myqsort(A, p + 1, right);
    
    DEBUG_PRINT("countCompare whole is %d\n", countCompare);
    printArray(A, left, right);
}

void printArray(int *A, int left, int right)
{
    /*
    int i;
    
    printf("Array ");
    for (i = left; i <= right; i++) {
        printf("%dth is %d | ", i, *(A + i));
    }
    printf("\n");
    */
}

BOOLEAN isIntArraySortedAscending(int *A, int left, int right)
{
    int i;
    for (i = left; i < right; i++)
        if (A[i] > A[i+1])
            return FALSE;
    
    return TRUE;
}