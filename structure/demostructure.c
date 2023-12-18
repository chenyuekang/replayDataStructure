#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 16
#define DEFAULT_SIZE 2
/*结构体*/
/*1.什么叫结构体：将不同类型的属性封装成一个类型*/
/*2.怎么定义结构体？*/
typedef struct stuInfo
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;
#if 0
    char clothes;
    char shoes;
    char phones;
#endif
} stuInfo;

/*取别名 typedef*/
/*写法二：
typedef struct stuInfo stuInfo
{
    int age;
    int height;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
};
*/

/*结构体会默认进行字节对齐：读取速度快(但是浪费空间)*/
/*结构体的[位域]到网络编程的时候再深究*/
/*什么叫变长结构体？*/  

/*函数：结构体做函数*/
#if 0
/*值传递：不影响实参*/
int printStruct(stuInfo stu)
{
    /*栈空间小的很，不允许超过8M*/
    stu.age = 100;
    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
                stu.age, stu.height, stu.sex, stu.weight, stu.name);
    return 0;
}
#else
/*传入参数：不要改变值,用const*/
int printStruct(const stuInfo *stu)
{
    /*栈空间小的很，不允许超过8M*/
    /*结构体必须用指针，省内存空间，没有用值传递*/
    int ret = 0;
    int len = sizeof(stu);
    printf("len:%d\n", len);
}

/*结构体数组做函数参数*/
int printStructBuffer(stuInfo *stu, int stuSize)
{
    for(int idx = 0; idx < stuSize; idx++)
    {
        printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
                stu[idx].age, stu[idx].height, stu[idx].sex, stu[idx].weight, stu[idx].name);
    }
    return 0;
}

int main()
{
#if 1
    /*3.怎么使用结构体*/
    struct stuInfo stu;
    memset(&stu, 0, sizeof(stu));


#if 0
    stu.age = 10;
    stu.weight = 30;
    stu.sex = 'm';
    stu.height = 130;
    strcpy(stu.name, "zhangsan", sizeof(stu.name) - 1);

    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
                stu.age, stu.height, stu.sex, stu.weight, stu.name);
#endif  

#if 0
    /*4.结构体大小*/
    int len = sizeof(stu);
    printf("len:%d\n", len);

    /*5.结构体数组*/
    /*数组：1.一块连续的内存地址
            2.存放的是同一种数据类型
    */
    stuInfo buffer[DEFAULT_SIZE];
    
    buffer[0].age = 10;
    buffer[0].weight = 30;
    buffer[0].sex = 'm';
    buffer[0].height = 130;
    strcpy(buffer[0].name, "zhangsan", sizeof(buffer[0].name) - 1);

    buffer[1].age = 20;
    buffer[1].weight = 50;
    buffer[1].sex = 'f';
    buffer[1].height = 160;
    strcpy(buffer[1].name, "wangwu", sizeof(buffer[1].name) - 1);

    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
                buffer[0].age, buffer[0].height, buffer[0].sex, buffer[0].weight, buffer[0].name);

    printf("stu.age:%d\t, stu.height:%d\t, stu.sex:%c\t, stu.weight:%d\t, stu.name:%s\n",
                buffer[1].age, buffer[1].height, buffer[1].sex, buffer[1].weight, buffer[1].name);
#endif

#if 0
    /*结构体指针*/
    stu.age = 10;
    stu.weight = 30;
    stu.sex = 'm';
    stu.height = 130;
    strncpy(stu.name, "zhangsan", sizeof(stu.name) - 1);

    /*结构体里面指针 必要要分配空间*/
    stu.address = "china";     //该写法一可以，指针指向字符串空间"china"是在全局区 
    //strcpy(stu.address, "china")     //该写法错误，address是个指针，只保存是地址，没有空间，需要分配空间
    if (stu.address == NULL)   //需要判空
    {
        return -1；
    }
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);      //该写法二动态分配空间  
    strcpy(stu.address, "china")  

    /*回顾指针*/
    int a = 5;
    int *p = &a;

/*two*/ 
    /*结构体指针*/
    stuInfo * info = &stu;
    /*结构体指针 读数据或者写数据，都是用->*/
    info->age = 30;
#if 0
    printf("info->age:%d\n", info->age);
    printf("stu.age:%d\n", stu.age);
#endif
     
    printStruct(&stu);
    
#endif

#if 0
    stuInfo buffer[DEFAULT_SIZE];
    
    buffer[0].age = 10;
    buffer[0].weight = 30;
    buffer[0].sex = 'm';
    buffer[0].height = 130;
    strcpy(buffer[0].name, "zhangsan", sizeof(buffer[0].name) - 1);

    buffer[1].age = 20;
    buffer[1].weight = 50;
    buffer[1].sex = 'f';
    buffer[1].height = 160;
    strcpy(buffer[1].name, "wangwu", sizeof(buffer[1].name) - 1);

    printStructBuffer(buffer, sizeof(buffer) / sizeof(buffer[0]));

#endif

#endif
    return 0;
}