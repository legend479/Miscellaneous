#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10000  // Maximum value of n to test
#define STEP_SIZE 100 // Step size for increasing n
#define REPETITIONS 5  // Number of times to repeat the test for each n value

//helper
int* generateRandomArray(int n) {
    int* arr = malloc(n * sizeof(int));  // Allocate memory for the array

    srand(time(NULL));  // Seed the random number generator

    for (int i = 0; i < n; i++) {
        arr[i] = rand();  // Generate a random number and assign it to array element
    }

    return arr;
}
typedef int ElementType;
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}
void swap(ElementType* a, ElementType* b)
{
    if(a==b)return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

//timing function for quick sort
#define threshold -1//threshold for insertion sort, -1 for no optimization
int MedianOfThree(ElementType Arr[], int len)
{
    int mid = len/2;
    if(cmp(Arr[0], Arr[mid]) > 0)
        swap(&Arr[0], &Arr[mid]);
    if(cmp(Arr[0], Arr[len-1]) > 0)
        swap(&Arr[0], &Arr[len-1]);
    if(cmp(Arr[mid], Arr[len-1]) > 0)
        swap(&Arr[mid], &Arr[len-1]);
    return mid;
}
void Partion(ElementType Arr[], int len, int* pivotIndex)
{
    swap(&Arr[*pivotIndex],&Arr[len -1]);
    int LeftItterator = 0;
    int RightItterator = len-2;

    while(1)
    {
        while(Arr[LeftItterator]<=Arr[len-1] && LeftItterator<len-1)++LeftItterator;
        while(Arr[RightItterator]>Arr[len-1] && RightItterator>-1)--RightItterator;
        if(LeftItterator < RightItterator)
            swap(&Arr[LeftItterator],&Arr[RightItterator]);
        else 
            break;
    }
    swap(&Arr[LeftItterator],&Arr[len-1]);
    *pivotIndex = LeftItterator;
}
int HelperBinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType))
{
    if(left > right)
        return left;
    int mid = (left + right) / 2;
    if(cmp(Arr[mid], key) > 0)
        return HelperBinarySearch(Arr, left, mid-1, key, cmp);
    else if(cmp(Arr[mid], key) < 0)
        return HelperBinarySearch(Arr, mid+1, right, key, cmp);
    else
        return mid;
}
void HelperInsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
   for(int i=1; i<len; ++i)
   {
    ElementType key = Arr[i];
    int InsertionIndex = HelperBinarySearch(Arr, 0, i-1, Arr[i], cmp);
    for(int j=i; j>InsertionIndex; --j)
        Arr[j] = Arr[j-1];
    
    Arr[InsertionIndex] = key;
   }
}

void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType))
{
    if(len < threshold)//optimization
    {
        HelperInsertionSort(Arr, len, cmp);
        return;
    }
    else if(len < 2)return;//base case 

    int pivotIndex = MedianOfThree(Arr, len);
    if(len < 4)return;//2nd base case 
    Partion(Arr, len, &pivotIndex);
    QuickSort(Arr, pivotIndex, cmp);
    QuickSort(Arr+pivotIndex+1, len-pivotIndex-1, cmp);
}

//timing function for bubble sort
void BubbleSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    for(int i=len-1; i>=0; --i)
    {
        int flag = 1;
        for(int j=0; j<i; ++j)
        {
            if(cmp(Arr[j], Arr[j+1]) > 0)
            {
                swap(&Arr[j], &Arr[j+1]);
                flag = 0;
            }
        }
        if(flag) break;
    }
}

//timing function for insertion sort
int BinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType))
{
    if(left > right)
        return left;
    int mid = (left + right) / 2;
    if(cmp(Arr[mid], key) > 0)
        return BinarySearch(Arr, left, mid-1, key, cmp);
    else if(cmp(Arr[mid], key) < 0)
        return BinarySearch(Arr, mid+1, right, key, cmp);
    else
        return mid;
}

void InsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
   for(int i=1; i<len; ++i)
   {
    ElementType key = Arr[i];
    int InsertionIndex = BinarySearch(Arr, 0, i-1, Arr[i], cmp);
    for(int j=i; j>InsertionIndex; --j)
        Arr[j] = Arr[j-1];
    
    Arr[InsertionIndex] = key;
   }
}

//timing function for merge sort
void Merge(ElementType Arr[], int left, int right, int mid, int (*cmp)(ElementType,ElementType))
{
    ElementType TempArr[right-left+1];
    int LeftIterrator = 0;
    int RightIterrator = 0;
    for(int i=0; i<right-left+1; ++i)
    {

        if(LeftIterrator > (mid - left))TempArr[i] = Arr[(mid+1) + RightIterrator++];
        else if(RightIterrator > (right - (mid+1)))TempArr[i] = Arr[left + LeftIterrator++];
        else if(Arr[left + LeftIterrator]>Arr[(mid+1) + RightIterrator])
        {
            TempArr[i] = Arr[(mid+1) + RightIterrator++];
        }
        else
        {
            TempArr[i] = Arr[left + LeftIterrator++];
        }
    }
    for(int i=0; i<right-left+1; ++i)
    {
        Arr[left + i] = TempArr[i];
    }
}
void sort(ElementType Arr[], int left, int right, int (*cmp)(ElementType, ElementType))
{
    if(left >= right)return;
    int mid=(left+right)/2;
    sort(Arr, left, mid, cmp);
    sort(Arr, mid+1, right, cmp);
    Merge(Arr, left, right, mid, cmp);
}

void MergeSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    sort(Arr, 0, len-1, cmp);
}

//timing function for shell sort
int ModifiedBinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType), int Interval)
{
    if(left > right)
        return left;
    int mid = (((left/Interval) + (right/Interval)) / 2);
    mid *= Interval;
    mid += left%Interval;
    if(cmp(Arr[mid], key) > 0)
        return ModifiedBinarySearch(Arr, left, mid-Interval, key, cmp, Interval);
    else if(cmp(Arr[mid], key) < 0)
        return ModifiedBinarySearch(Arr, mid+Interval, right, key, cmp, Interval);
    else
        return mid;
}
#define logbase3e 0.9102392266
#define logbase32 0.6309297536
float logApprox( float x, int terms){
    x = 1 - x;
    float log = 0;
    for(int i = terms; i > 0; --i){
        log = log*x + (x/i);
    }
    log=-1*log;
    return log;
}
float Log3(float num){
    int NUM;
    NUM=*(int*) &num;

    float mant=((float)(NUM&0x7FFFFF))/(1<<23)+1.0f;
    

    int exp=((NUM>>23)&0xFF)-127;

    float log = (logApprox(mant,100)*logbase3e +logbase32*((float) exp));

    return log;
}
void ModifiedInsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType), int Interval, int start)
{
    for(int i=start+Interval; i<len; i+=Interval)
    {
        ElementType key = Arr[i];
        int InsertionIndex = ModifiedBinarySearch(Arr, start, i-Interval, Arr[i], cmp, Interval);
        for(int j=i; j>InsertionIndex; j-=Interval)
            Arr[j] = Arr[j-Interval];
        
        Arr[InsertionIndex] = key;
    }
}

void ShellSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    //knuth interval array for given array length
    int IntervalLen = (int)Log3(2*len+1);
    int Intervals[IntervalLen];
    Intervals[0] = 1;
    for(int i=1; i<IntervalLen; ++i)
        Intervals[i] = (3*(2*Intervals[i-1] + 1)- 1)/2;
    
    for(int i=IntervalLen-1; i>=0; --i)//itterate over intervals from max to min(1)
        for(int j=0; j<Intervals[i]; ++j)//itterate over subarrays defined by starting index
            ModifiedInsertionSort(Arr, len, cmp, Intervals[i], j);
}

//timing function for Selection sort
void SelectionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    for(int i=0,j=len; i<j-1; ++i,--j)
    {
        int min = i;
        int max = i;
        for(int k=i; k<j; ++k)
        {
            if(cmp(Arr[k], Arr[min]) < 0)
                min = k;
            if(cmp(Arr[k], Arr[max]) > 0)
                max = k;
        }
        swap(&Arr[i], &Arr[min]);
        if(i == max)//check if max moved
            swap(&Arr[j-1], &Arr[min]);
        else
            swap(&Arr[j-1], &Arr[max]);
    }
}

//timing function for sys_quick sort
void SystemQuickSort(ElementType Arr[], int len, int (*cmp)(const void*,const void*))
{
    qsort(Arr, len, sizeof(ElementType), cmp);
}

int main() {
    int n, i, j;
    clock_t start_time, end_time;
    double time_elapsed;
    FILE *output_file;
    int sort_num = 7;
    void (*Sort[7])() = {QuickSort,BubbleSort,InsertionSort,MergeSort,ShellSort,SelectionSort,SystemQuickSort};
    // Open the output file for writing
    for(int j=0; j<sort_num; ++j)
    {
        char filename[100];
        sprintf(filename, "time_complexity_%d.dat", j);
        output_file = fopen(filename, "w");
        if (output_file == NULL) {
            printf("Error: Could not open output file\n");
            return 1;
        }
        
        // Test your_function for different values of n
        for (n = STEP_SIZE; n <= MAX_N; n += STEP_SIZE) {
            time_elapsed = 0.0;
            for (i = 0; i < REPETITIONS; i++) {
                int* randomArray = generateRandomArray(n);            
                start_time = clock();
                Sort[j](randomArray, n, cmp);
                end_time = clock();
                free(randomArray);
                time_elapsed += ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
            }
            time_elapsed /= REPETITIONS;
            fprintf(output_file, "%d %f\n", n, time_elapsed);
        }
        
        // Close the output file
        fclose(output_file);
    }        
    return 0;
}
