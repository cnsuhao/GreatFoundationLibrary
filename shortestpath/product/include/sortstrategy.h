/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : searchstrategy.h
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月16日
  最近修改   :
  功能描述   : 搜索策略,汇集了所有的搜索算法
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月16日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SEARCHSTRATEGY_H__
#define __SEARCHSTRATEGY_H__

//排序基类
class ISortStrategy
{
public:
    virtual void Sort(int *Array, int len) = 0;
protected:
    virtual void Swap(int &i, int &j);
};

//冒泡排序
class CSortStrategyBubble : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
};

//插入排序
class CSortStrategyInsert : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
};

//选择排序
class CSortStrategySelect : public ISortStrategy
{
public:
    void Sort(int *Array, int len);    
};

//快速排序
class CSortStrategyQuick : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
private:
    void Sort(int *Array, int iBegin, int iEnd);    
};


#endif  //__SEARCHSTRATEGY_H__

