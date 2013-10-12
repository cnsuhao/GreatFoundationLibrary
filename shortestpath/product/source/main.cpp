/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : main.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月3日
  最近修改   :
  功能描述   :  广度优先算法
                本例采用广度优先算法进行计算
                找到从(0,0)到(4,4)的最短路径
                灰集合 黑集合
                找到顶点 -> 相邻点 -> 再相邻点 -> 终点 -> 反向追溯
  函数列表   :
              main
  修改历史   :
  1.日    期   : 2013年10月3日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <set>
#include <list>
#include <assert.h>
using namespace std;

#include "shortestpath.h"
#include "mapfile.h"

int main()
{    
    CMapfile *m_pMapfile = new CMapfile();
	//设置Map
    char FileName[] = "D:\\05.GitHub\\GreatFoundationLibrary\\shortestpath\\project\\Resource\\map_test.txt";
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

    CShortestPath *m_pShortestPath = new CShortestPath();
    (void)m_pShortestPath->SetMap(x, y, ppMap);

	//设置起点和终点
	ST_PT bPt(0,0);
    ST_PT ePt(2,7);
    
    (void)m_pShortestPath->SetBeginPoint(bPt);
    (void)m_pShortestPath->SetEndPoint(ePt);

	//处理查找算法
    if (m_pShortestPath->DoService())
	{
		m_pShortestPath->ShowResult();		
	}	
    
    //释放内存
    delete m_pShortestPath;
    delete m_pMapfile;
    
    return 0;
}
