#ifndef sort
#define sort

typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b);

//helper functions
void swap(ElementType* a, ElementType* b);

int MedianOfThree(ElementType Arr[], int len);

void Partion(ElementType Arr[], int len, int* pivotIndex);

void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType));

//Solution function
long long int WatchMovies(int Arr[], int N, int K);

#endif