#ifndef hash
#define hash

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

#endif