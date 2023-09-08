#ifndef sort
#define sort

typedef int* ElementType;

//comparator function
int cmp(ElementType a, ElementType b);
//helper functions
void swap(int* a, int* b);
int MedianOfThree(ElementType Arr[], int len, int Indexs[]);

void Partion(ElementType Arr[], int len, int* pivotIndex, int Indexs[]);
void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType), int Indexs[]);

//Insite Perm Sort
void SortInPlace(ElementType Arr[], int Sorted_indexs[], int len);

void FreeArr(ElementType Arr[], int len);

#endif