/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : searchstrategy.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月16日
  最近修改   :
  功能描述   : 搜索策略集合
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月16日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#include "sortstrategy.h"

void ISortStrategy::Swap(int &i, int &j)
{
    int iTmp = i;
    i = j;
    j = iTmp;
}

//简单排序包括冒泡，选择，插入三种排序方法
//冒泡排序 像水泡一样一个接一个传递下去
void CSortStrategyBubble::Sort(int *Array, int len)
{
    for (int i = 0; i < len - 1; i++)      //冒泡循环次数
    {
        for (int j = 0; j < len - 1 - i; j++)  //一轮冒泡所需时间
        {   
            if (Array[j] < Array[j+1])
            {
                Swap(Array[j], Array[j+1]);
            }
        }  
    }
}

//插入排序：排序前队列已经排好了，先对头两个元素排序
//8 5 4 3
void CSortStrategyInsert::Sort(int *Array, int len)
{   
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (Array[j] < Array[i])
            {
                for (int k = i; k > j; k--) //比较后要往后移
                {
                    Swap(Array[k], Array[k-1]);
                }
            }
        }
    }
}

//选择排序：先选出最小的，然后选次小的。。。
void CSortStrategySelect::Sort(int *Array, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if (Array[i] < Array[j]) //一直对同一元素操作
            {
                Swap(Array[i], Array[j]);               
            }
        }
    } 
}

//快速排序 二分法 必须递归
//10 8 5 12 7
void CSortStrategyQuick::Sort(int *Array, int len)
{
     Sort(Array, 0, len-1);
}

void CSortStrategyQuick::Sort(int *Array, int iBegin, int iEnd)
{
    if (iBegin >= iEnd)
    {
        return;
    }
    int k = Array[iBegin];
    int i = iBegin;
    int j = iEnd + 1;
    while (true)
    {
        while ((i < iEnd) && (Array[++i] > k));
        while ((j > iBegin) && (Array[--j] < k));
        if (i < j)
        {
            Swap(Array[i], Array[j]);
        }
        else
        {
            break;
        }
    }
    
    Swap(Array[iBegin], Array[j]);
    Sort(Array, 0, j-1);
    Sort(Array, j+1, iEnd);
}
