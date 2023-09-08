//sperate chaining//

//LinkedList
typedef char* ListElementType;
typedef struct ListNode{
    ListElementType key;
    struct ListNode* next;
}ListNode;

typedef struct ListSentinal{
    ListNode* Head;
    ListNode* Tail;
}ListSentinal;

//LinkedList Function
ListSentinal* INITList();
// ListNode* INITNode(ListElementType key); //Private function
void InsertInList(ListSentinal* L, ListElementType key);
void DeleteFromList(ListSentinal* L, ListElementType key);
void DeleteList(ListSentinal* L);
void PrintList(const ListSentinal* L);

//HashTable
typedef ListElementType HashTableElementType;
typedef ListSentinal* HashTable;

///HashTable Functions
HashTable INITHshTble();
void InsertInHashTable(HashTable HshTable, HashTableElementType key);
void DeleteFromHashTable(HashTable HshTble, HashTableElementType key);
void DeleteHashTable(HashTable HshTble);
void PrintHashTable(HashTable HshTble);

//HashFunction
long long unsigned int HashFunction(HashTableElementType key);

#include<stdio.h>
#include<stdlib.h>

#define Capacity 100003//Create a hash table with 10^5 entry size(question constraint)(prime)

//LinkedList Function
ListSentinal* INITList()
{
    ListSentinal* L = (ListSentinal*) malloc(sizeof(ListSentinal));
    L->Head = NULL;
    L->Tail = NULL;
    return L;
}
ListNode* INITNode(ListElementType key)//Private function
{
    ListNode* N = (ListNode*) malloc(sizeof(ListNode));
    N->key = malloc(10*sizeof(char));
    for(int i=0; key[i]!=0; ++i){
        N->key[i]=key[i];
    }
    N->next = NULL;
    return N;
}
void InsertInList(ListSentinal* L, ListElementType key)
{
    ListNode* N = INITNode(key);
    if(L->Head == NULL)//ListEmpty
    {
        L->Head = N;
        L->Tail = N;
        return;
    } 
    L->Tail->next = N;
    L->Tail = N;
    return;
}
void DeleteFromList(ListSentinal* L, ListElementType key)
{
    if(L->Head == NULL)//EmptyList
    {
        return;
    }
    else if(L->Head == L->Tail && L->Head->key == key)//OneElement
    {
        free(L->Head);
        L->Head = NULL;
        L->Tail = NULL;
        return;
    }
    ListNode* CurNode = L->Head;
    ListNode* CurNodePre = NULL;

    while(CurNode != NULL)
    {
        if(CurNode->key == key)
        {
            CurNodePre->next = CurNode->next;
            free(CurNode);
            return;
        }
        CurNodePre = CurNode;
        CurNode = CurNode->next;
    }
    return;
}
void DeleteList(ListSentinal* L)
{
    ListNode* CurNode = L->Head;
    while(CurNode != NULL)
    {
        ListNode* temp = CurNode->next;
        free(CurNode);
        CurNode = temp;
    }
    free(L);
    return;
}
void PrintList(const ListSentinal* L)
{
    if(L->Head == NULL)printf("-1\n");
    else
    {
        ListNode* CurNode = L->Head;
        while(CurNode != NULL)
        {
            printf("%s ",CurNode->key);
            CurNode = CurNode->next;
        }
        printf("\n");
    }
    return;
}

///HashTable Functions
HashTable INITHshTble()
{
    // HashTable HshTable = (HashTable) malloc(sizeof(ListSentinal)*Capacity);
    // for(int i=0; i<Capacity; ++i){
    //     HshTable[i].Head = NULL;
    //     HshTable[i].Tail = NULL;
    // }
    HashTable HshTable = (HashTable) calloc(Capacity,sizeof(ListSentinal));
    return HshTable;
}
void InsertInHashTable(HashTable HshTable, HashTableElementType key)
{
    InsertInList(&HshTable[HashFunction(key)], key);
    return;
}
void DeleteFromHashTable(HashTable HshTble, HashTableElementType key)
{
    DeleteFromList(&HshTble[HashFunction(key)],key);
    return;
}
void DeleteHashTable(HashTable HshTble)
{
    for(int i = 0; i<Capacity; ++i){
        DeleteList(&HshTble[i]);
    }
}
void PrintHashTable(HashTable HshTble)
{
    for(int i=0; i<Capacity; ++i){
        PrintList(&HshTble[i]);
    }
}
//helper function for hash function
//Private functions
int CharToInt(char ch)
{
    return (ch - 'a');
}
long long int Power(long long int base, int exponent)
{
    long long int result = 1;
    while(1)
    {
        if (exponent & 1)//if exponent is odd multiply the result by(will happen atleast once)
            result *= base;
        exponent >>= 1;//floor division with 2
        if (!exponent)//if exponent is zero break
            break;
        base *= base; //else square base
    }

    return result;
}
//HashFunction
long long unsigned int HashFunction(HashTableElementType key)
{
    long long unsigned int hashValue = 0;
    while(*key!='\0')
    {
        hashValue = (hashValue + Power(11,*key++)) % Capacity;
    }
    return hashValue;
}
