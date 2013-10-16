/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : llt_searchstrategy.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月16日
  最近修改   :
  功能描述   : 搜索排序策略
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月16日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/


#include <gtest/gtest.h>
#include <stdio.h>
#include "comm_macro.h"
#include "sortstrategy.h"


class CSortSSuite : public testing::Test
{
protected:
    void SetUp() 
    {        
    }
    
    void TearDown() 
    {        
    }    
};

TEST_F(CSortSSuite, DoService)
{  
    int iArray[][20] = 
    {
        {10,1,6,2,4,9,12,3},        
    };
    
    int iExpArray[][20] = 
    {
        {12,10,9,6,4,3,2,1},
    };
        
    CSortStrategyBubble m_bubbleS;
    CSortStrategyInsert m_insertS;
    CSortStrategySelect m_selectS;
    CSortStrategyQuick m_quickS;

    int len = COUNTOF(iArray[0]);
    int i = 0;
    m_bubbleS.Sort(iArray[0], len);
    for (i = 0; i < len; i++)
    {
        printf("%d ", iArray[0][i]);
        EXPECT_EQ(iArray[0][i], iExpArray[0][i]);
    }
    printf("\n");
}

