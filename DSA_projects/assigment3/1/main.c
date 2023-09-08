#include<stdio.h>
#include<stdlib.h>
#include"hash.h"

int CharToInt(char ch);

int* Freqtable(char* str)
{
    int* freqtable = (int*) calloc(26, sizeof(int));
    while(*str!='\0')
    {
        ++freqtable[CharToInt(*str++)];
    }
    return freqtable;
}
int Hashcheck(char* str1, char* str2)
{
    int* freqtable1 = Freqtable(str1);
    int* freqtable2 = Freqtable(str2);
    for(int i = 0; i<26; ++i)
    {
        if(freqtable1[i] != freqtable2[i])
        {
            free(freqtable1);
            free(freqtable2);
            return 0;
        }
    }
    free(freqtable1);
    free(freqtable2);
    return 1;
}
void SelectedPrintList(ListSentinal* L , HashTableElementType Qkey)
{
    ListNode* CurNode = L->Head;
    int NumOfAnaC = 0;
    while(CurNode != NULL)
    {
        if(Hashcheck(CurNode->key,Qkey))
        {
            printf("%s ",CurNode->key);
            NumOfAnaC=1;
        }
        CurNode = CurNode->next;
    }
    if(!NumOfAnaC)printf("-1");
    printf("\n");
    return;
}
void PrintQuery(HashTable HT, HashTableElementType Qkey)//Function to print corrsponding anagrams
{
    SelectedPrintList(&HT[HashFunction(Qkey)],Qkey);
}

int main()
{
    int N,Q;
    scanf("%d %d",&N,&Q);
    HashTable HT = INITHshTble();

    for(int i=0; i<N; ++i){
        char key[11];
        scanf("%s",key);
        InsertInHashTable(HT,key);
        // PrintHashTable(HT);

    }
    for(int i=0; i<Q; ++i){
        char key[11];
        scanf("%s",key);
        PrintQuery(HT,key);
    }
    //DeleteHashTable(HT);

    return 0;
}
