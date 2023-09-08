#ifndef functions 
#define functions 
 

typedef struct Node
{
    int Element;
    struct Node* nextNoode;
} Node;

typedef Node* PtrNode;


void Insert(PtrNode Head, int num);

PtrNode Find( PtrNode Head, int num );

void Print( PtrNode Head);

int STRCMP(char*str1, char*str2);


#endif