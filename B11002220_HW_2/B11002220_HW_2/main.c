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
listPointer last = NULL; // �̫�@��
/**
 * @brief �N��r�[��`�I���̫᭱
 *
 * @param first list���_�Y
 * @param last  list������
 * @param word  word�O��ܥ[�J�`�I����r
 */
void addnode(listPointer* first, listPointer* last,
    char* word)
{
    // ���t�s���Ŷ�
    node* new_node = malloc(sizeof(node));
    // �N���Φn���r�ǵ�WORD
    new_node->word = _strdup(word);
    // �Y�O�_�l
    if (*first == NULL)
    {
        *first = new_node;
        *last = new_node;
        new_node->next = NULL;
    }
    else
    { // �D�Ū�list
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
    // �洫�������ȴN�n
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
 * @brief ��qbegin ��end��lsit����
 * @note ���w�d��b 0-(length-1)�϶���
 * @param first
 * @param last
 * @param begin
 * @param end
 * @return 1:���ন�\
 * @return 0:���ॢ��
 */
int reverse(listPointer* first, int begin, int end)
{
    int count = 0;
    listPointer node_before_start = NULL, node_after_end = NULL;
    listPointer start_node = NULL, end_node = NULL, temp = NULL;
    int length = get_length(*first);
    // lead = *first;
    // �ư�
    if (begin > end || length <= end)
        return 0;
    if (begin == end) // ���γB�z
        return 1;
    // �]�w�|�Ӹ`�I
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
    // �qstart �}�l�����ઽ��J��end
    while (current != node_after_end)
    {
        temp = current->next; // null
        current->next = prev; // student ->null
        prev = current;       //
        current = temp;
        // current = current->next ;
    }
    // 'student am a I'
    if (begin == 0 && length - 1 == end) // �w��begin ��0�����p�B�z
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
        // ��start �e���Ӹ`�I���Vend�`�I
        node_before_start->next = end_node;
        // ��start �`�I���Vend�᪺�`�I
        start_node->next = node_after_end;
    }
    return 1;
    


}
int main()
{
    char sentence[SENTENCE_SIZE] = { 0 };
    int start = 2;
    int end = 3;
    int c; // Ū���r��
    char* nextToken; 
    // Ū�����
    
    FILE* Input; 
    if (fopen_s(&Input, "Input.txt", "r") == 0) {
        fscanf_s(Input, "%d %d", &start, &end);
        while ((c = fgetc(Input)) != '\n' && c != EOF); // ���L����Ÿ�
        fgets(sentence, SENTENCE_SIZE - 2, Input); //Ū���ĤG��
        fclose(Input);
    }
     

    // �B�z��r�å[�J�`�I
    char* token = strtok_s(sentence, " ", &nextToken);
    while (token != NULL)
    {
        // printf("%s\n", token);
        addnode(&first, &last, token);
        token = strtok_s(NULL, " ", &nextToken);;
    }
    // �洫�B�϶���@
    FILE* Output; 
    fopen_s(&Output,"Output.txt", "w");
    exchange(first); 
    print_node(first, Output);
    if (reverse(&first, start, end) == 1) //�O�_�i�H�ϦV?
        print_node(first, Output);
    else {
        fprintf(Output, "-1\n");
    }
    fclose(Output);

    return 0;
}
