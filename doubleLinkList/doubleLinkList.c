#include "doubleLinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*状态码*/
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/*静态函数只在本源文件(.c)使用*/
/*静态前置声明*/
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val, int *pPos, int (*compareFunc(ELEMENTTYPE, ELEMENTTYPE)));

/*链表初始化*/
int DoubleLinkListInit(DoubleLinkList **pList)
{
    int ret = 0;          //接口很适配系统调用，系统调用一般是成功返回0，失败返回错误码或者-1
    DoubleLinkList *list = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * 1);           //分配空间
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    /*清空脏数据*/
    memset(list, 0, sizeof(DoubleLinkList) * 1);

    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    /*清空脏数据*/
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);
    list->head->data = 0;
    list->head->next = NULL;

    /*初始化的时候， 尾指针=头指针*/
    list->tail = list->head;

    /*链表的长度为0*/
    list->len = 0;

    /*二级指针*/
    *pList = list;
    return ret;            //设置ret=0,如果中间有问题，卡壳了，则ret就不为0了
}

/*链表头插*/
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, 0, val);
}

/*链表尾插*/
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, pList->len, val);
}

/*链表指定位置插入*/
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;                  //返回空指针
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;           //返回位置非法
    }

    /*封装结点*/
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /*清除脏数据*/
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);

#if 1
    newNode->data = 0;
    newNode->next = NULL;
#endif

    /*赋值*/
    newNode->data = val;

#if 1
    /*从虚拟头结点开始遍历*/
    DoubleLinkNode * travelNode = pList->head;
#else
    /*travelNode指向链表第一个元素开始遍历*/
    DoubleLinkNode * travelNode = pList->head->next;
#endif

    int flag = 0;
    /*这种情况下需要更改尾指针*/
    if(pos == pList->len)
    {
        /*修改结点指向*/
        travelNode = pList->tail;
    
 #if 0
        //代码重复使用
        newNode->next = travelNode->next;     //1
        travelNode->next = newNode;           //2
        pList->tail = newNode;
#endif

        flag = 1;
    }
    else
    {
        while(pos)    //pos不为0时进入循环，pos为0不进入循环
        {
            travelNode = travelNode->next;     //travelNode从头结点往后移
            pos--;
        }
    }
    /*修改结点指向*/
    newNode->next = travelNode->next;         //1
    travelNode->next = newNode;               //2
    if(flag)
    {
        /*尾指针更新位置*/
        pList->tail = newNode;
    }

    /*更新链表的长度*/
    (pList->len)++;

    return ret;
  
}

/*链表头删*/
int DoubleLinkListHeadDel(DoubleLinkList * pList)
{
    return DoubleLinkListDelAppointPos(pList, 1);         //删除第一个pos=1
}

/*链表尾删*/
int DoubleLinkListTailDel(DoubleLinkList * pList)
{
    return DoubleLinkListDelAppointPos(pList, pList->len);
}

/*链表指定位置删*/
int DoubleLinkListDelAppointPos(DoubleLinkList * pList, int pos)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

#if 1
    DoubleLinkNode * travelNode = pList->head;
#else
    DoubleLinkNode * travelNode = pList->head->next;
#endif

    int flag = 0;
    /*需要修改尾指针*/
    if(pos == pList->len)
    {
        /*需要修改尾指针*/
        flag = 1;
    }
    DoubleLinkNode * needDelNode = NULL;
    while(--pos)        //先自减，然后再进行判断,到达要删除结点位置的前一个结点
    {
        /*向后移动位置*/
        travelNode = travelNode->next;    
    }
    /*跳出循环找到的是哪一个结点？*/
    needDelNode = travelNode->next;               //1
    travelNode->next = needDelNode->next;         //2

    if(flag)
    {
        /*调整尾指针*/
        pList->tail = travelNode;
    }

    /*释放内存*/
    if(needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }
     
    /*链表长度减一*/
    (pList->len)--;
    return ret;


}

/*根据指定的元素得到在链表中所在的位置*/
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val, int *pPos, int (*compareFunc(ELEMENTTYPE, ELEMENTTYPE)))
{
    /*静态函数只给本源文件的函数用，不需要判断合法性*/
    int ret;

#if 0
    int pos = 0;
    DoubleLinkNode *travelNode = pList->head;
#else
    int pos = 1;
    DoubleLinkNode *travelNode = pList->head->next;
#endif

    while(travelNode != NULL)
    {
        #if 0
        if(travelNode->data == val)
        {
            /*解引用*/
            *pPos = pos;
            return pos;
        }
        #else
        cmp = compareFunc(val, travelNode->data);
        if(cmp == 0)
        {
            /*解引用*/
            *pPos = pos;
            return pos;
        }
        #endif
        travelNode = travelNode->next;
        pos++;
    }
    /*解引用*/
    *pPos = NOT_FIND;

    return NOT_FIND;   //返回值是-1
}

/*链表删除指定数据*/
int DoubleLinkListDelAppointData(DoubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc(ELEMENTTYPE, ELEMENTTYPE)))
{
    int ret = 0;

    /*元素在链表中的位置*/
    int pos = 0;

    /*链表的长度*/
    int size = 0;
    while(DoubleLinkListGetLength(pList, &size) && pos != NOT_FIND)    //如果没有pos != NOT_FIND当找不到时候会一直陷入死循环
    {
        /*根据指定的元素得到在链表中所在的位置*/
        DoubleLinkListAccordAppointValGetPos(pList, val, &pos, compareFunc);
        DoubleLinkListDelAppointPos(pList, pos);
    }
    return ret;
}

/*获取链表的长度*/
int DoubleLinkListGetLength(DoubleLinkList * pList, int *pSize)
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }
    /*返回链表的长度*/
    return pList->len;
}

/*链表的销毁*/
int DoubleLinkListDestory(DoubleLinkList * pList)
{
    int ret = 0;
    /*我们使用头删释放链表*/
    int size = 0;
    while(DoubleLinkListGetLength(pList, &size))
    {
        DoubleLinkListHeadDel(pList);
    }

    if(pList->head != NULL)
    {
        free(pList->head);
        /*指针置为NULL*/
        pList->head = NULL;
        pList->tail = NULL;
    }
    return ret;
}

/*链表遍历接口*/
int DoubleLinkListForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

#if 0
    /*travelNode指向虚拟头结点*/
    DoubleLinkNode * travelNode = pList->head;
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data:%d\n", travelNode->data);
    }
#else
    /*travelNode指向链表第一个元素*/
    DoubleLinkNode * travelNode = pList->head->next;
    while(travelNode != NULL)
    {
        /*包装器. 钩子 .回调函数*/
        printFunc(travelNode->data);
        printf("travelNode->data:%d\n", travelNode->data);
        travelNode = travelNode->next;
    }
#endif
    return ret;  
}