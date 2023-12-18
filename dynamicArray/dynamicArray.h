#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

/*避免头文件重复包含*/
typedef int ELEMENTTYPE;

typedef struct dynamicArray
{
    ELEMENTTYPE *data;      /* 数组的空间 */
    ELEMENTTYPE len;        /* 数组的大小 */
    ELEMENTTYPE capacity;   /* 数组的容量 */
} dynamicArray;

#endif //__DYNAMIC_ARRAY_H__
