#include<stdio.h>
#include<stdlib.h>

char* ModifySTR(char* STR, int lenSTR)//Inserts a HASHTAG character at each place in a given string
{
    char* NewSTR = (char*) malloc(sizeof(char)*(lenSTR*2+1));
    for(int i = 0; i<(lenSTR*2+1); ++i)
    {
        if(i&1)NewSTR[i]=STR[i/2];
        else NewSTR[i]='#';
    }
    return NewSTR;
}
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
int Query(int LeftIndx, int RightIndx, int* SubPalinLen, int lenSTR)
{
    int Center = LeftIndx + RightIndx - 1;
    int PalinLen = RightIndx - LeftIndx + 1;

    if(SubPalinLen[Center]>=PalinLen)return 1;
    else return 0;
}



int main()
{
    int N,Q;
    scanf("%d %d",&N,&Q);
    char str[N+1];
    scanf("%s",str);
    char STR[N];
    for(int i = 0; i<N; ++i)
    {
        STR[i]=str[i];
    }

    int* SubPalinLen = MakePalinLenArr(STR, N);

    for(int i = 0; i<Q; ++i)
    {
        int L,R;
        scanf("%d %d",&L,&R);

        if(Query(L,R,SubPalinLen,N))printf("YES\n");
        else printf("NO\n");
    }
    free(SubPalinLen);
    return 0;

}