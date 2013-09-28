/******************************************************************************

                  版权所有 (C), 2010-2020, 脑袋空空技术有限公司

 ******************************************************************************
  文 件 名   : llt_shortestpath.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月3日
  最近修改   :
  功能描述   : 最短路径算法测试类
  函数列表   :
              TEST
  修改历史   :
  1.日    期   : 2013年10月3日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/


#include <gtest/gtest.h>
#include <stdio.h>
#include <memory.h>
#include <set>
#include <list>
#include <assert.h>
using namespace std;

#include "shortestpath.h"

class CShortestPathTestSuite : public testing::Test
{
protected:
    void SetUp() 
    {
        m_pShortestPath = new CShortestPath();
    }
    
    void TearDown() 
    {
        if (NULL != m_pShortestPath)
        {
            delete m_pShortestPath;
            m_pShortestPath = NULL;
        }
    }
    
    CShortestPath *m_pShortestPath;    
};

TEST_F(CShortestPathTestSuite, DoService)
{
	//设置Map
    static const int in_map[3][10] = 
    {
        0,1,0,0,0,0,0,0,0,1,  
        0,1,0,1,0,1,1,1,0,1,
        0,0,0,0,1,1,1,1,0,0,    
    };

    int **ppMap = new int*[MAX_X];
    for (int i = 0; i < MAX_X; i++)
    {        
        int *pMap = new int[MAX_Y];        
        for (int j = 0; j < MAX_Y; j++)
        {
            pMap[j] = in_map[i][j];            
        }
        ppMap[i] = pMap;
    }
    
    m_pShortestPath->SetMap(MAX_X, MAX_Y, ppMap);

	//设置起点和终点
	ST_PT bPt(0,0);
    ST_PT ePt(2,3);
    
    m_pShortestPath->SetBeginPoint(bPt);
    m_pShortestPath->SetEndPoint(ePt);

	//处理查找算法
    if (m_pShortestPath->DoService())
	{
		m_pShortestPath->ShowResult();		
	}

	EXPECT_EQ(true, m_pShortestPath->DoService());
    
    //释放内存
    for (int m = 0; m < MAX_X; m++)
    {
        delete[] ppMap[m];
    }
    delete[] ppMap;

    EXPECT_EQ(6, 6);

}