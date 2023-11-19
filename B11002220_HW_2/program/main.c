#include "useful.h"
#include "string.h"
#define SENTENCE_SIZE 1000
#define MAX_WORD_SIZE 100
typedef struct node *listPointer;
typedef struct node
{
    char *word;
    listPointer next;
} node;


listPointer first = NULL;
listPointer last = NULL; // 最後一個
/**
 * @brief 將文字加到節點的最後面
 * 
 * @param first list的起頭
 * @param last  list的結尾
 * @param word  word是表示加入節點的文字
 */
void addnode(listPointer *first, listPointer *last,
             char *word)
{
    // 分配新的空間 
    node *new_node = malloc(sizeof(node));

    // 將分割好的字傳給WORD
    new_node->word = strdup(word);

    // 若是起始
    if (*first == NULL) { 
        *first = new_node;
        *last = new_node;
        new_node->next = new_node;
    } else { // 非空的list 
        (*last)->next = new_node;
        new_node->next = *first;
        *last = new_node;
    }

}
void print_node(listPointer *first, listPointer *last)
{
    listPointer temp = *first
    for (; temp != *last; temp = temp->next) {
        printf("%s ", temp->word);
    }
    printf("%s ", (*last)->word);
}
void exchange(listPointer *first, listPointer *last)
{
    if (*first == NULL || (*first)->next == NULL) {
        return; 
    }

    // 交換節點
    listPointer tmp = *first;
    *first = *last;
    *last = tmp;

    // 更新next 
    (*last)->next = (*first)->next;
    (*first)->next = tmp->next;
    tmp->next = *first;
}

/**
 * @brief 
 * 
 * @param first 
 * @param last 
 * @param begin 
 * @param end 
 */
// void reverse(listPointer *first, listPointer *last,int begin,int end)
// {


// }
int main()
{
    // read
    char sentence[SENTENCE_SIZE] = "I am a student";
    // fgets(sentence,SENTENCE_SIZE + 2, stdin );
    // 创建两个节点
    char *token = strtok(sentence, " ");
    while (token != NULL)
    {
        // printf("%s\n", token);
        addnode(&first, &last, token);
        token = strtok(NULL, " ");
    }
    exchange(&first,&last) ; 
    print_node(&first, &last);


    return 0;
}
