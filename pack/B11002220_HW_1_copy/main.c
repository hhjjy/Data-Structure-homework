#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define a stack from BracketElement
#define MAX_SIZE 256
typedef struct {
    int pos;
    char word;
} BracketElement;
BracketElement stack[MAX_SIZE] = { 0 };
int stack_index = -1;

// Define a match arr to store the array 
typedef struct {
    int first;
    int last;
} MatchBracket;
MatchBracket match_arr[MAX_SIZE] = { 0 };
int store = 0;

// append to the stack 
void stack_append(BracketElement element) {
    stack[++stack_index] = element;
}
// get the element from the stack 
BracketElement stack_pop() {
    return stack[stack_index--];
}
// whether is empty 
int stack_is_empty() {
    return (stack_index < 0);
}
// whether the stack is full   
int stack_is_full() {
    return (stack_index == MAX_SIZE - 1);
}
// func:check_parentheses
// para:
//   - str: expression
// return:
//   - 1: if balanced 
//   - 0: else  
int check_parentheses(char* str) {
    //��l�Ƴ]�w!
    stack_index = -1;
    store = 0;
    MatchBracket match_temp;
    BracketElement temp;
    for (int i = 0; i < strlen(str); i++) {
        temp.pos = i;
        temp.word = str[i];
        // ���N��(�������|��
        if (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == ')' || str[i] == ']' || str[i] == '}') {
            stack_append(temp);
        }
        // lens of it more than 1 , and form a close  parathese 
        if (stack_index >= 1 && (
            (stack[stack_index].word == ')' && stack[stack_index - 1].word == '(') ||
            (stack[stack_index].word == ']' && stack[stack_index - 1].word == '[') ||
            (stack[stack_index].word == '}' && stack[stack_index - 1].word == '{')
            )) {
            // record and pop two of it from the stack 
            temp = stack_pop();
            match_temp.last = temp.pos;
            temp = stack_pop();
            match_temp.first = temp.pos;
            match_arr[store] = match_temp;
            store++;
        }
    }
    return stack_is_empty();
}

// at the end , to fit the result of it gives ,
// use qsort to order the matched arr .
int compare(const void* a, const void* b) {
    MatchBracket* bracket1 = (MatchBracket*)a;
    MatchBracket* bracket2 = (MatchBracket*)b;

    if (bracket1->first < bracket2->first) {
        return -1;
    }
    else if (bracket1->first > bracket2->first) {
        return 1;
    }
    else {
        return 0;
    }
}
int main() {
    FILE* file;
    FILE* OUTPUT_FILE;
    errno_t err1 = fopen_s(&file, "Input.txt", "r");
    errno_t err2 = fopen_s(&OUTPUT_FILE, "Output.txt", "w");

    if (err1 != 0 || err2!= 0 ) {
        printf("Cannot open the file\n");
        return 1;
    }

    char line[MAX_SIZE+2];// bounded condition 
    while (fgets(line, MAX_SIZE+2, file) != NULL) {
        if (check_parentheses(line)){
            fprintf_s(OUTPUT_FILE, "1\n");
            // quick sort in order to have correct result. 
            qsort(&match_arr, store, sizeof(match_arr[0]), compare); 
            //write to Output.txt
             for (int i = 0; i < store ; i++)
            {
                fprintf_s(OUTPUT_FILE, "%d,%d;",match_arr[i].first, match_arr[i].last);
            }
            fprintf_s(OUTPUT_FILE, "\n");
            printf("\n");
        }
        else{
            fprintf_s(OUTPUT_FILE, "-1\n");
            fprintf_s(OUTPUT_FILE, "%d\n",stack[0].pos);
        }
    }
    fclose(file);
    fclose(OUTPUT_FILE);
    return 0;
}
