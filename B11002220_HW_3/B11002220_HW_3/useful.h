#ifndef __userful__
#define __userful__

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/**
 * @brief �w�q��X��󪺤��W
 */
#define OUTPUT_FILE "Output.txt"

#ifdef __PRINTF_TO_FILE__BY_VISUAL_STUDIO
 /**
  * @brief �M�ſ�X��󪺤��e
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
   * @brief �N���e��X���X���
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
   * @brief �з�C fopen
   *
   */
#ifdef __PRINTF_TO_FILE__
   /**
    * @brief �M�ſ�X��󪺤��e
    */
#define clear_file() \
        do { \
            FILE *file = fopen(OUTPUT_FILE, "w"); \
            if (file != NULL) { \
                fclose(file); \
            } \
        } while (0)

    /**
     * @brief �N���e��X���X���
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
      * @brief �S���w�q__PRINTF_TO_FILE__ �ϥ�
      */
#define clear_file() \
        do { \
        } while (0)
#endif // ! __PRINTF_TO_FILE__BY_VISUAL_STUDIO || __PRINTF_TO_FILE__


    // ��ܾ��arr
#define PRINT_ARR(ARR, SIZE) \
    do \
    { \
        for (int i = 0; i < SIZE; i++) \
            printf("%d ", ARR[i]); \
        printf("\n"); \
    } while (0)

// �洫
#define SWAP(a, b, t) (t = a, a = b, b = t)

/**
 * @brief ����Ʀr a>b��X1,a=b ��X0 a<b ��X-1
 * @param a
 * @param b
 */
#define COMPARE(a, b) (a > b ? 1 : (a < b ? -1 : 0))

 // ���t�O����Ŷ�
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

// ��ܰ���ɶ��h�� ��J���Ovoid
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
