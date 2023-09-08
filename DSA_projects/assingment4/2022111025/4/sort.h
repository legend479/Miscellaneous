#ifndef sort
#define sort
//sorting algo
//shell sort
typedef int ElementType;
int cmp(ElementType a, ElementType b);

void Merge(ElementType Arr[], int left, int right, int mid, int (*cmp)(ElementType,ElementType));
void Sort(ElementType Arr[], int left, int right, int (*cmp)(ElementType, ElementType));

void MergeSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType));

//tester function to print array
void PRINTARR(int Arr[], int len);
#endif