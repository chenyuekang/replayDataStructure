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

/* API: application program interface */

/* 动态数组的初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity);

/* 动态数组插入数据(默认插到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val);

/* 动态数组插入数据(在指定位置插入) */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组删除数据（默认情况下删除最后末尾的数据） */
int dynamicArrayDeleteData(dynamicArray *pArray);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos);

/* 动态数组删除指定的元素 */
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val);

/* 动态数组销毁 */
int dynamicArrayDestory(dynamicArray *pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity);

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal);

#endif //__DYNAMIC_ARRAY_H__
