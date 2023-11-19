#include "useful.h"
#include "string.h"
#define WRITE 
#define SENTENCE_SIZE 1000
#define MAX_WORD_SIZE 100
typedef struct node* listPointer;
typedef struct node
{
    char* word;
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
void addnode(listPointer* first, listPointer* last,
    char* word)
{
    // 分配新的空間
    node* new_node = malloc(sizeof(node));
    // 將分割好的字傳給WORD
    new_node->word = _strdup(word);
    // 若是起始
    if (*first == NULL)
    {
        *first = new_node;
        *last = new_node;
        new_node->next = NULL;
    }
    else
    { // 非空的list
        (*last)->next = new_node;
        new_node->next = NULL;
        *last = new_node;
    }
}
void print_node(listPointer first, FILE* FP)
{
#ifdef WRITE
    listPointer temp = first;
    for (; temp; temp = temp->next)
    {
        fprintf(FP, "%s ", temp->word);
    }
    fprintf(FP, "\n");
#else
    listPointer temp = first;
    for (; temp; temp = temp->next)
    {

        printf("%s ", temp->word);
    }
    printf("\n");
#endif

}
void exchange(listPointer first)
{
    if (first == NULL || (first)->next == NULL)
    {
        return;
    }
    listPointer temp = first;
    for (; temp->next; temp = temp->next); // FIND THE LAST
    // 交換內部的值就好
    char* Ctemp = _strdup((first)->word);
    (first)->word = _strdup((temp)->word);
    (temp)->word = Ctemp;
}
int get_length(listPointer first)
{
    int count = 0;
    listPointer temp = first;
    if (first)
    {
        do {
            count++;
            temp = temp->next;
        } while (temp);
    }
    return count;
}
/**
 * @brief 把從begin 到end的lsit反轉
 * @note 限定範圍在 0-(length-1)區間內
 * @param first
 * @param last
 * @param begin
 * @param end
 * @return 1:反轉成功
 * @return 0:反轉失敗
 */
int reverse(listPointer* first, int begin, int end)
{
    int count = 0;
    listPointer node_before_start = NULL, node_after_end = NULL;
    listPointer start_node = NULL, end_node = NULL, temp = NULL;
    int length = get_length(*first);
    // lead = *first;
    // 排除
    if (begin > end || length <= end)
        return 0;
    if (begin == end) // 不用處理
        return 1;
    // 設定四個節點
    for (temp = *first, count = 0; temp; temp = temp->next)
    {
        if (count == begin - 1)
            node_before_start = temp;
        if (count == begin)
            start_node = temp;
        if (count == end)
            end_node = temp;
        if (count == end + 1)
            node_after_end = temp;
        count++;
    }
    listPointer current, prev;
    current = start_node->next;
    prev = start_node;
    temp = NULL;
    // 從start 開始做反轉直到遇到end
    while (current != node_after_end)
    {
        temp = current->next; // null
        current->next = prev; // student ->null
        prev = current;       //
        current = temp;
        // current = current->next ;
    }
    // 'student am a I'
    if (begin == 0 && length - 1 == end) // 針對begin 為0的情況處理
    {
        *first = end_node;
        start_node->next = NULL;
    }
    else if (begin == 0)
    { // 0 - 2 
            *first = end_node;
            start_node->next = node_after_end;
    }
    else
    {
        // 把start 前的個節點指向end節點
        node_before_start->next = end_node;
        // 把start 節點指向end後的節點
        start_node->next = node_after_end;
    }
    return 1;
    


}
int main()
{
    char sentence[SENTENCE_SIZE] = { 0 };
    int start = 2;
    int end = 3;
    int c; // 讀取字元
    char* nextToken; 
    // 讀取資料
    
    FILE* Input; 
    if (fopen_s(&Input, "Input.txt", "r") == 0) {
        fscanf_s(Input, "%d %d", &start, &end);
        while ((c = fgetc(Input)) != '\n' && c != EOF); // 跳過換行符號
        fgets(sentence, SENTENCE_SIZE - 2, Input); //讀取第二行
        fclose(Input);
    }
     

    // 處理文字並加入節點
    char* token = strtok_s(sentence, " ", &nextToken);
    while (token != NULL)
    {
        // printf("%s\n", token);
        addnode(&first, &last, token);
        token = strtok_s(NULL, " ", &nextToken);;
    }
    // 交換、反項實作
    FILE* Output; 
    fopen_s(&Output,"Output.txt", "w");
    exchange(first); 
    print_node(first, Output);
    if (reverse(&first, start, end) == 1) //是否可以反向?
        print_node(first, Output);
    else {
        fprintf(Output, "-1\n");
    }
    fclose(Output);

    return 0;
}
