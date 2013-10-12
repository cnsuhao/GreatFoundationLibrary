/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : shortestpath.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月3日
  最近修改   :
  功能描述   : 最短路径算法实现

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

//构造函数
CShortestPath::CShortestPath()
{
    m_maxX = INVALID_VALID;
    m_maxY = INVALID_VALID;
    
    memset(g_map, 0, sizeof(g_map));
	bMapInit = false;
}

//析构函数
CShortestPath::~CShortestPath()
{
    InitGrayBlackList();
}

//清除灰色和黑色集合内存
void CShortestPath::InitGrayBlackList()
{
    //释放内存
    list<ST_PT *>::iterator posGray = g_lstGray.begin();
    for (; posGray != g_lstGray.end(); ++posGray)
    {
        if (g_ePt == *(*posGray))
        {
            //do nothing
        }
        else
        {
            delete *posGray;
        }
    }
    g_lstGray.clear();

    list<ST_PT *>::iterator posBlack = g_lstBlack.begin();
    for (; posBlack != g_lstBlack.end(); ++posBlack)
    {
        if (g_bPt == *(*posBlack))
        {
            //do nothing
        }
        else
        {
            delete *posBlack;
        }        
    }
    g_lstBlack.clear();

    //清除Set集合
    g_setBlack.clear();
}

//设置起点
bool CShortestPath::SetBeginPoint(ST_PT &obj)
{
	if (!bMapInit)
	{
		return false;
	}

	assert((obj.x >= 0) && (obj.x < MAX_X));
    assert((obj.y >= 0) && (obj.y < MAX_Y));

	if (g_map[obj.x][obj.y] != 0)
	{
		return false;
	}

    g_bPt = obj;

	return true;
}

//设置终点
bool CShortestPath::SetEndPoint(ST_PT &obj)
{
	if (!bMapInit)
	{
		return false;
	}

	assert((obj.x >= 0) && (obj.x < MAX_X));
    assert((obj.y >= 0) && (obj.y < MAX_Y));

	if (g_map[obj.x][obj.y] != 0)
	{
		return false;
	}

    g_ePt = obj;
}

//设置地图
bool CShortestPath::SetMap(int x, int y, int **pMap)
{
    assert((x > 0) && (x <= MAX_X));
    assert((y > 0) && (y <= MAX_Y));
    
    m_maxX = x;
    m_maxY = y;
    
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            g_map[i][j] = pMap[i][j];
        }
    }

	bMapInit = true;
    
    return true;
}

//点坐标转化为int值，作为Set集合查找时更快
int CShortestPath::ST2INT(ST_PT &obj)
{
    return (obj.x << 8) + obj.y;
}

//int值转化为点坐标
ST_PT CShortestPath::INT2ST(int i)
{
    ST_PT stObj;
    stObj.x = i >> 8;
    stObj.y = i - (stObj.x << 8);
    return stObj;
}

//是否放到灰色集合中
bool CShortestPath::IsPushGray(ST_PT &objP)
{
    if (!IsPointValid(objP))
    {
        return false;
    }

    if (0 != g_map[objP.x][objP.y])
    {
        return false;
    }
    
    int iTmp = ST2INT(objP);
    SET_INT::iterator pos = g_setBlack.find(iTmp);
    if (pos != g_setBlack.end())
    {
        return false;
    }
    
    return true; 
}

//是否是目标点
bool CShortestPath::IsDestPt(ST_PT &objP)
{
    if (g_ePt == objP)    
    {
        return true;
    }
    return false;
}

//是否找到目标点
bool CShortestPath::Search(ST_PT *prevPt, E_DIR eDir)
{
    ST_PT *tmpPt = new ST_PT;
    tmpPt->prevPt = prevPt;
    if (E_DIR_EAST == eDir)
    {
        tmpPt->x = prevPt->x;
        tmpPt->y = prevPt->y + 1;
    }
    else if (E_DIR_SOUTH == eDir)
    {
        tmpPt->x = prevPt->x + 1;
        tmpPt->y = prevPt->y;
    }
    else
    {
        tmpPt->x = prevPt->x - 1;
        tmpPt->y = prevPt->y;
    }

    if (!IsPointValid(*tmpPt))
    {
        delete tmpPt;
        tmpPt = NULL;
        return false;
    }

    if (IsPushGray(*tmpPt))
    {
        g_lstObj.push_back(tmpPt);

        if (IsDestPt(*tmpPt))
        {            
            return true;
        }
    }
    else
    {
        if (IsDestPt(*tmpPt))
        {
            delete tmpPt;
            tmpPt = NULL;
            return true;
        }

        delete tmpPt;
        tmpPt = NULL;
    }

    return false;
}

//打印结果
void CShortestPath::ShowResult()
{
    printf("===============\n");
    
    ST_PT *pDest = &g_bPt;
    
    //从起始点开始打印查出的目标路径
    printf("(%d, %d)\n", pDest->x, pDest->y);
    while (NULL != pDest->nextPt)
    {
        pDest = pDest->nextPt;
        printf("(%d, %d)\n", pDest->x, pDest->y);        
    }
}

//计算最短路径
bool CShortestPath::DoService()
{    
    //初始化灰色黑色列表
    InitGrayBlackList();
    
    //先将起点放到灰色集合中
    g_lstGray.push_back(&g_bPt);
    
    bool bFind = false;   //是否发现目标点
    ST_PT *pDest = NULL;  //目标点
	static const int TRY_MAX_COUNT = 1000;  //运行尝试最大次数
	int iTryCnt = 0;   //运行尝试次数
    
	//避免查找不到，尝试太多
    while (iTryCnt <= TRY_MAX_COUNT)
    {
		iTryCnt++;

        //遍历灰色列表
        list<ST_PT *>::iterator pos = g_lstGray.begin();
        for (; pos != g_lstGray.end(); ++pos)
        {
            //将灰色列表中的元素抽取出来，放入黑色列表中
            ST_PT *pPt = *pos;
            g_lstBlack.push_back(pPt);
        
            //为了提高检索的效率，这里采用Set标准库函数
            int iBlack = ST2INT(*pPt);
            (void)g_setBlack.insert(iBlack);

            //向三个方向寻找，如果发现目标点直接退出
            if (Search(pPt, E_DIR_EAST)){bFind = true; break;}
            if (Search(pPt, E_DIR_SOUTH)) {bFind = true; break;}
            if (Search(pPt, E_DIR_NORTH)) {bFind = true; break;}
        }
        
        //更新灰色列表，因为在寻找过程中会重新计算灰色列表
        g_lstGray = g_lstObj;
        g_lstObj.clear();
        if (bFind)
        {
            break;
        }        
    }

	//未找到路径
	if (!bFind)
	{
		printf("\nNot find that way!\n");
		return false;
	}

    //目标点在临时集合中，找出目标点
    list<ST_PT *>::iterator pos = g_lstGray.begin();
    for (; pos != g_lstGray.end(); ++pos)
    {
        ST_PT *pTmp = *pos;
        if (g_ePt == *pTmp)
        {
            pDest = pTmp;
            break;
        }
    }

    //从目标点向回追溯到起始点，并构造链接
    if (NULL == pDest)
    {
        return false;
    }
    
    ST_PT *pSwap = NULL;
    while (NULL != pDest->prevPt)
    {
        pSwap = pDest;
        pDest = pDest->prevPt;
        pDest->nextPt = pSwap;
    }    

	return true;
}

//是否是有效点
bool CShortestPath::IsPointValid(ST_PT &obj)
{
    if ((obj.x >= m_maxX) || (obj.x < 0))
    {
        return false;
    }

    if ((obj.y >= m_maxY) || (obj.y < 0))
    {
        return false;
    }

    return true;
}


