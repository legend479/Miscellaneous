#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

int IntArrLen;
int MxMnLen;

void MergeSort(int* arr, int n)
{
    if(n==1) return ;
    int mid=n/2,left[mid],right[n-mid];
    
    for(int i=0; i<mid; i++){
        left[i]=arr[i];
    }
    for(int j=mid; j<n; j++){
        right[j-mid]=arr[j];
    }

    MergeSort(left,mid);
    MergeSort(right,n-mid);

    int m1=0,m2=0,indx=0;
    while (1){
        if(m1==mid && m2!=n-mid){
            for(int k=indx; k<n; k++){
                arr[k]=right[m2++];
            }
        }
        else if (m1!=mid && m2==n-mid){
            for(int k=indx; k<n; k++){
                arr[k]=left[m1++];
            }
        }
        else if(m1==mid && m2==n-mid){
            break;
        }
        
        else if(left[m1]>right[m2]){
            arr[indx++]=right[m2++];
        }
        else if(left[m1]<right[m2]){
            arr[indx++]=left[m1++];
        }
        else{
            arr[indx++]=left[m1++];
            arr[indx++]=right[m2++];
        }
    }

}

int* IntersectionArray(int* Arr1 , int* Arr2, int lenArr1, int lenArr2){
    int tempLen,solLen=0;
    if(lenArr1>lenArr2) tempLen=lenArr2;
    else tempLen=lenArr1;

    int tempsol[tempLen];

    MergeSort(Arr1,lenArr1);
    MergeSort(Arr2,lenArr2);

    int x=0,y=0;
    while(x<lenArr1 && y<lenArr2){
        if(Arr1[x]>Arr2[y])y++;
        else if(Arr1[x]<Arr2[y])x++;
        else {
            tempsol[solLen++]=Arr1[x];
            x++;
            y++;
        }
    }
    if(solLen==0)printf("%d",-1);

    int* sol= (int*) malloc(sizeof(int)*solLen);

    for(int k=0; k<solLen; k++){
        sol[k]=tempsol[k];
    }
    IntArrLen=solLen;
    return sol;
}

int countCharOccurrences(const char* str, int length, char ch){
    int freq=0;

    for(int i=0; i<length; i++){
        if(str[i]==ch) freq++;
    }

    return freq;
}

char findFirstNonRepeatingChar(const char* str, int length){
    int freqArr[26];
    for(int i=0; i<26; i++){
        freqArr[i]=0;
    }

    int f;
    for(int j=0; j<length; j++){
        f=(int) (str[j]-'a');
        freqArr[f]+=1;
    }

    for(int k=0; k<length; k++){
        f=(int) (str[k]-'a');
        if(freqArr[f]==1) return str[k];
    }
    return '\0';
}

int STRCMP(char*str1, char*str2){
    int i=0,f=1;
    while (!(str1[i]=='\0' || str2[i]=='\0')){
        if(str1[i]!=str2[i]){
            f=0;
            break;
        } 
        i++;
    }
    return f;
}

int EleCmp(char**strs, int numStr, int indx){
    int f=1;
    char testchar=strs[0][indx];
    for(int i=1; i<numStr; i++){
        if(strs[i][indx]!=testchar){
            f=0;
            break;
        }
    }
    return f;
}

char* findLongestCommonPrefix(char** strs, int numStr, int maxLen){
    char tempsol[maxLen];

    int solLen=0;
    while(EleCmp(strs,numStr,solLen) && strs[0][solLen]!='\0'){
        tempsol[solLen++]=strs[0][solLen];
    }

    char *sol=(char*) malloc((solLen+1)*sizeof(char));

    for(int j=0; j<solLen; j++){
        sol[j]=tempsol[j];
    }
    sol[solLen]='\0';
    return sol;
}

int* MaxMin(int* Arr, int lenArr){

    int solLen=0, tempSol[lenArr], left[lenArr], right[lenArr],curlmax=Arr[0],currmin=Arr[lenArr-1];
    
    for(int i=0; i<lenArr; i++){
        if(curlmax<Arr[i]){
            curlmax=Arr[i];
        }
        if(currmin>Arr[lenArr-1-i]){
            currmin=Arr[lenArr-1-i];
        }
        left[i]=curlmax;
        right[lenArr-1-i]=currmin;

    }


    for (int k = 0; k < lenArr; k++)
    {
        if(Arr[k]==left[k] && Arr[k]==right[k]){
            tempSol[solLen++]=k;
        }
    }
    

    int* sol= (int*) malloc(sizeof(int)*solLen);

    for(int j=0; j<solLen; ++j){
        sol[j]=tempSol[j];
    }

    MxMnLen=solLen;
    if(solLen==0) printf("%d",-1);
    return sol;
}

char* removeSubstring(char* str, int strLength, const char* substr, int substrLength){
    char tempSol[strLength];
    int f,solLen=0;
    for(int i=0; i<strLength; i++){
        f=1;
        for(int j=i; j<i+substrLength; j++){
            if(str[j]!=substr[j-i]){
                f=0;
                break;
            }
        }
        if(f){
            i+=substrLength-1;
        }
        else{
            tempSol[solLen++]=str[i];
        }
        
    }

    char* sol= (char*) malloc(solLen*sizeof(char));

    for(int k=0; k<solLen; k++){
        sol[k]=tempSol[k];
    }
    sol[solLen]='\0';

    return sol;
}
