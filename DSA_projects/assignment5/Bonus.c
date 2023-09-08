#include <stdio.h>
#include <stdlib.h>
typedef struct TrieNode
{
    struct TrieNode *children[26];
    int isEndOfWord;
    struct TrieNode *TargetWords; 
    char *prefix;
} TrieNode;

typedef TrieNode *Trie;

TrieNode *createNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }
    node->prefix = NULL;
    node->TargetWords = NULL;
    node->isEndOfWord = 0;
    return node;
}
Trie createTrie()
{
    Trie T = createNode();
    return T;
}
void InsertWord(Trie T, char *guess)
{
    TrieNode *temp = T;
    int i = 0;
    while (guess[i] != '\0')
    {
        int index = guess[i] - 'a';
        if (temp->children[index] == NULL)
        {
            temp->children[index] = createNode();
        }
        temp = temp->children[index];
        ++i;
    }
    if (!temp->prefix)
    {
        temp->prefix = (char *)malloc(sizeof(char) * (i + 1));
        for (int j = 0; j < i; j++)
        {
            temp->prefix[j] = guess[j];
        }
        temp->prefix[i] = '\0';
    }
    temp->isEndOfWord = 1;
    // printf("Guess inserted: %s\n",temp->prefix);
    // temp->ListTarget = (char**)malloc(sizeof(char*));
}
void InsertTargetWord(Trie T, char *guess, char *Target)
{
    TrieNode *temp = T;
    int i = 0;
    while (guess[i] != '\0')
    {
        int index = guess[i] - 'a';
        temp = temp->children[index];
        ++i;
    }

    if (!temp->TargetWords)
        temp->TargetWords = createTrie();
    InsertWord(temp->TargetWords, Target);
}
void GetAllWordsInTrie(Trie T, Trie Target)
{
    if (T->isEndOfWord)
    {
        InsertWord(Target, T->prefix);
    }
    for (int i = 0; i < 26; ++i)
    {
        if (T->children[i] != NULL)
        {
            GetAllWordsInTrie(T->children[i], Target);
        }
    }
}
void GetAllTargetsinTrie(Trie T, Trie Target)
{
    if (T->isEndOfWord)
    {
        GetAllWordsInTrie(T->TargetWords, Target);
    }
    for (int i = 0; i < 26; ++i)
    {
        if (T->children[i] != NULL)
        {
            GetAllTargetsinTrie(T->children[i], Target);
        }
    }
}
void CountWordsInTrie(Trie T, int *count)
{
    if (T->isEndOfWord)
    {
        (*count)++;
    }
    for (int i = 0; i < 26; ++i)
    {
        if (T->children[i] != NULL)
        {
            CountWordsInTrie(T->children[i], count);
        }
    }
}

void DeleteTrie(Trie T)
{
    for (int i = 0; i < 26; i++)
    {
        if (T->children[i])
        {
            DeleteTrie(T->children[i]);
        }
    }
    if(T->TargetWords)DeleteTrie(T->TargetWords);
    if(T->prefix)free(T->prefix);
    free(T);
}

void PrintAllWordsinTrie(Trie T)
{
    if (T->isEndOfWord)
    {
        printf("%s ", T->prefix);
    }
    for (int i = 0; i < 26; ++i)
    {
        if (T->children[i] != NULL)
        {
            PrintAllWordsinTrie(T->children[i]);
        }
    }
}

void PrintAllTargetWordsWithPrefix(Trie T, char *prefix)
{
    TrieNode *temp = T;
    int i = 0;
    while (prefix[i] != '\0')
    {
        int index = prefix[i] - 'a';
        if (temp->children[index] == NULL)
        {
            printf("0\n");
            return;
        }
        temp = temp->children[index];
        ++i;
    }

    Trie Targets = createTrie();
    GetAllTargetsinTrie(temp, Targets);
    int count = 0;
    CountWordsInTrie(Targets, &count);
    if(count==0)
    {
        printf("0\n");
        return;
    }
    printf("%d ", count);
    PrintAllWordsinTrie(Targets);
    DeleteTrie(Targets);
    printf("\n");
}

// driver to test trie
int main()
{
    int Session;
    scanf("%d", &Session);
    Trie T = createTrie();
    char guess[100];

    for (int i = 0; i < Session; ++i)
    {
        int n;
        char target[100];
        scanf("%d %s", &n, target);
        for (int i = 0; i < n; ++i)
        {
            scanf("%s", guess);
            InsertWord(T, guess);
            InsertTargetWord(T, guess, target);
        }
    }
    // PrintTrieStructure(T);
    int Queries;
    scanf("%d", &Queries);
    for (int i = 0; i < Queries; ++i)
    {
        // char query[100];
        scanf("%s", guess);
        PrintAllTargetWordsWithPrefix(T, guess);
    }
}