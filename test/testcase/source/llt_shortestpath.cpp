/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

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
#include "comm_macro.h"
#include "mapfile.h"

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
    #if 1
    CMapfile *m_pMapfile = new CMapfile();
    
	//设置Map
    char FileName[] = "..\\..\\..\\shortestpath\\project\\Resource\\map_normal.txt";
    m_pMapfile->SetFileName(FileName);

    char CanWalk[] = "-";
    m_pMapfile->SetCanWalkToken(CanWalk);

    char CannotWalk[] = "~";
    m_pMapfile->SetCannotWalkToken(CannotWalk);

    char DelimeterToken[] = " \r\n";
    m_pMapfile->SetDelimeterToken(DelimeterToken);

    int x = 0;
    int y = 0;
    int **ppMap = m_pMapfile->GetMap(x, y);

    m_pShortestPath->SetMap(x, y, ppMap);
    #endif
    
    typedef struct _ST_TESTCONDITION
    {
        bool bResult;   //执行结果
        BYTE bX;    //起点X坐标
        BYTE bY;    //起点Y坐标
        BYTE eX;    //终点X坐标
        BYTE eY;    //终点Y坐标
    } ST_TESTCONDITION;
    
    static const ST_TESTCONDITION s_TestCond[] = 
    {
        {true, 0, 0, 2, 7},
        {true, 2, 7, 0, 0},
    };
    
    for (int i = 0; i < COUNTOF(s_TestCond); i++)
    {
        //设置起点和终点
	    ST_PT bPt(s_TestCond[i].bX, s_TestCond[i].bY);
        ST_PT ePt(s_TestCond[i].eX, s_TestCond[i].eY);
        
        m_pShortestPath->SetBeginPoint(bPt);
        m_pShortestPath->SetEndPoint(ePt);

	    //处理查找算法
        if (m_pShortestPath->DoService())
	    {
		    m_pShortestPath->ShowResult();		
	    }

	    EXPECT_EQ(s_TestCond[i].bResult, m_pShortestPath->DoService());
    }	
    
    #if 1
    //释放内存
    delete m_pMapfile;
    m_pMapfile = NULL;
    #endif

}