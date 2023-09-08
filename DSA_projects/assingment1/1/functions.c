#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int NumUniEle;

int numDig(float num){
    int NUM;
    NUM=*(int*) &num;

    float mant=((float)(NUM&0x7FFFFF))/(1<<23)+1.0f;
    

    int exp=((NUM>>23)&0xFF)-127;

    int log = (((mant-1)-(mant-1)*(mant-1)/2)*0.434 +0.302*((float) exp));

    return log+1;

}


void reverseString(char* str, int length){
    for(int i=0; i< length/2; i++){
        // swap i and length-1-i indexs using XOR
       str[i]=str[i]^str[length-i-1];
       str[length-i-1]=str[i]^str[length-i-1];
       str[i]=str[i]^str[length-i-1];
    }
}

int* uniqueElements(int* arr , int length){
    int* HashMap= (int* )calloc(10000,sizeof(int));
    int* tempsol= (int *)malloc(length*sizeof(int));
    int solLen=0;

    for(int i=0; i<length; i++){
        if(HashMap[arr[i]-1]==0){
            HashMap[arr[i]-1]=1;
            tempsol[solLen++]=arr[i];
        }
    }

    int* sol= (int*) malloc(solLen*sizeof(int));
    for(int j=0; j<solLen; j++){
        sol[j]=tempsol[j];
    }
    free(HashMap);
    free(tempsol);
    NumUniEle=solLen;
    return sol;
}

char* compressString(char* str, int length){
    char tempsol1[length], currentEle=str[0];
    int currentFreq=1,solLen=0, tempsol2[length];

    for(int i=1; i<length; i++){
        if(str[i]!= currentEle){
            tempsol1[solLen]=currentEle;
            tempsol2[solLen++]=currentFreq;
            currentEle=str[i];
            currentFreq=1;
        }
        else{
            currentFreq++;
        }
    }
    
    tempsol1[solLen]=currentEle;
    tempsol2[solLen++]=currentFreq;

    char* sol = (char*) calloc(length*2,sizeof(char));
    int iterate=0;
    for (int k = 0; k < solLen; k++)
    {
        sol[iterate++]=tempsol1[k];
        int Digits=numDig(tempsol2[k]);
        for(int l=0; l< Digits; l++){
            sol[Digits+iterate-1 -l]=(char)((tempsol2[k]%10)+48);
            tempsol2[k]/=10;
        }
        iterate+=Digits;
    }
    

    return sol;
}

int** transpose(int** matrix , int NumRow , int NumCol){
   int **sol= (int **) malloc(sizeof(int*)*NumCol);
   for(int x=0; x<NumCol; x++){
    sol[x]=(int *) malloc(sizeof(int)*NumRow);
   }

   for(int i=0; i<NumRow; i++){
    for(int j=0; j<NumCol; j++){
        sol[j][i]=matrix[i][j];
    }
   }

   return sol;
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
