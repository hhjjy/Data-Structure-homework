#ifndef __userful__
#define __userful__

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/**
 * @brief 定義輸出文件的文件名
 */
#define OUTPUT_FILE "Output.txt"

#ifdef __PRINTF_TO_FILE__BY_VISUAL_STUDIO
 /**
  * @brief 清空輸出文件的內容
  */
#define clear_file() \
        do { \
            FILE *file; \
            if(fopen_s(&file, OUTPUT_FILE, "w") == 0) { \
                if (file != NULL) { \
                    fprintf(file,""); \
                    fclose(file); \
                 } \
            } \
        } while (0)

  /**
   * @brief 將內容輸出到輸出文件中
   */
#define printf(...) \
        do { \
            FILE *file; \
            if(fopen_s(&file, OUTPUT_FILE, "a") == 0) { \
                fprintf(file,__VA_ARGS__); \
                fclose(file); \
            } \
        } while (0)

#endif



  /**
   * @brief 標準C fopen
   *
   */
#ifdef __PRINTF_TO_FILE__
   /**
    * @brief 清空輸出文件的內容
    */
#define clear_file() \
        do { \
            FILE *file = fopen(OUTPUT_FILE, "w"); \
            if (file != NULL) { \
                fclose(file); \
            } \
        } while (0)

    /**
     * @brief 將內容輸出到輸出文件中
     */
#define printf(...) \
        do { \
            FILE *file = fopen(OUTPUT_FILE, "a"); \
            if (file != NULL) { \
                fprintf(file, __VA_ARGS__); \
                fclose(file); \
            } \
        } while (0)

#endif

#ifndef  __PRINTF_TO_FILE__BY_VISUAL_STUDIO && __PRINTF_TO_FILE__
     /**
      * @brief 沒有定義__PRINTF_TO_FILE__ 使用
      */
#define clear_file() \
        do { \
        } while (0)
#endif // ! __PRINTF_TO_FILE__BY_VISUAL_STUDIO || __PRINTF_TO_FILE__


    // 顯示整個arr
#define PRINT_ARR(ARR, SIZE) \
    do \
    { \
        for (int i = 0; i < SIZE; i++) \
            printf("%d ", ARR[i]); \
        printf("\n"); \
    } while (0)

// 交換
#define SWAP(a, b, t) (t = a, a = b, b = t)

/**
 * @brief 比較數字 a>b輸出1,a=b 輸出0 a<b 輸出-1
 * @param a
 * @param b
 */
#define COMPARE(a, b) (a > b ? 1 : (a < b ? -1 : 0))

 // 分配記憶體空間
#define MALLOC(arr, size) \
    do \
    { \
        if (!(arr = malloc(size))) \
        { \
            fprintf(stderr, "Malloc error\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define REMALLOC(arr, size) \
    do \
    { \
        if (!(arr = realloc(arr, size))) \
        { \
            fprintf(stderr, "Realloc error\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

// 顯示執行時間多少 輸入的是void
#define TIME_FUNCTION(func)                                                         \
    do                                                                              \
    {                                                                               \
        clock_t start = clock();                                                    \
        func();                                                                     \
        clock_t end = clock();                                                      \
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;            \
        printf("Function %s takes %f seconds to execute.\n", #func, cpu_time_used); \
    } while (0)


#endif
