#ifndef sort
#define sort

typedef char* ElementType;

//comparator function
int Radcmp(ElementType str1, ElementType str2);

//helper functions
void swap(ElementType* a, ElementType* b);
int ModifiedBinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType), int Interval);

#define logbase3e 0.9102392266
#define logbase32 0.6309297536

float logApprox( float x, int terms);

float Log3(float num);

void ModifiedInsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType), int Interval, int start);

void ShellSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType));

void FREE(ElementType Arr[], int len);

#endif
