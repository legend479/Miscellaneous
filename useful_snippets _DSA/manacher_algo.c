#include<stdio.h>
#include<stdlib.h>

int* MakePalinLenArr(char* STR, int lenSTR)
{
    char* NewSTR = ModifySTR(STR, lenSTR);
    int* SubPalinLen = (int*) malloc(sizeof(int)*(2*lenSTR+1));

    //predefined Values for leftmost values of Palin length array
    SubPalinLen[0] = 0;
    SubPalinLen[1] = 1;

    int CurCenterElement = 1;//index of current center index for checking
    int CurRightBound = 2;//index of current right bound of palindrome
    //index of current left bound = 2*CurCenterElement - CurRightBound

    for(int curEle = 2; curEle<2*lenSTR+1; ++curEle)
    {
        int curEleMirror = 2*CurCenterElement - curEle;
        int diff = CurRightBound - curEle;
        SubPalinLen[curEle] = 0;
        if(diff>0)
        {
            SubPalinLen[curEle] = SubPalinLen[curEleMirror] < diff ? SubPalinLen[curEleMirror] : diff;//min of distance to border and mirror element's palindrome length
        }
        while(((curEle + SubPalinLen[curEle] + 1) < (2*lenSTR+1)) && (NewSTR[curEle+SubPalinLen[curEle]+1] == NewSTR[curEle-SubPalinLen[curEle]-1]) )
        {
            ++SubPalinLen[curEle];
        }   
        if(curEle + SubPalinLen[curEle] >= CurRightBound)
        {
            CurCenterElement = curEle;
            CurRightBound = curEle + SubPalinLen[curEle];
        }
    }
    free(NewSTR);
    return SubPalinLen;  
}