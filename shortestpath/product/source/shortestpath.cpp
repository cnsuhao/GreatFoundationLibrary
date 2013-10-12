/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : shortestpath.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��3��
  ����޸�   :
  ��������   : ���·���㷨ʵ��

  �޸���ʷ   :
  1.��    ��   : 2013��10��3��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <set>
#include <list>
#include <assert.h>
using namespace std;

#include "shortestpath.h"

//���캯��
CShortestPath::CShortestPath()
{
    m_maxX = INVALID_VALID;
    m_maxY = INVALID_VALID;
    
    memset(g_map, 0, sizeof(g_map));
	bMapInit = false;
}

//��������
CShortestPath::~CShortestPath()
{
    InitGrayBlackList();
}

//�����ɫ�ͺ�ɫ�����ڴ�
void CShortestPath::InitGrayBlackList()
{
    //�ͷ��ڴ�
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

    //���Set����
    g_setBlack.clear();
}

//�������
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

//�����յ�
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

//���õ�ͼ
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

//������ת��Ϊintֵ����ΪSet���ϲ���ʱ����
int CShortestPath::ST2INT(ST_PT &obj)
{
    return (obj.x << 8) + obj.y;
}

//intֵת��Ϊ������
ST_PT CShortestPath::INT2ST(int i)
{
    ST_PT stObj;
    stObj.x = i >> 8;
    stObj.y = i - (stObj.x << 8);
    return stObj;
}

//�Ƿ�ŵ���ɫ������
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

//�Ƿ���Ŀ���
bool CShortestPath::IsDestPt(ST_PT &objP)
{
    if (g_ePt == objP)    
    {
        return true;
    }
    return false;
}

//�Ƿ��ҵ�Ŀ���
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

//��ӡ���
void CShortestPath::ShowResult()
{
    printf("===============\n");
    
    ST_PT *pDest = &g_bPt;
    
    //����ʼ�㿪ʼ��ӡ�����Ŀ��·��
    printf("(%d, %d)\n", pDest->x, pDest->y);
    while (NULL != pDest->nextPt)
    {
        pDest = pDest->nextPt;
        printf("(%d, %d)\n", pDest->x, pDest->y);        
    }
}

//�������·��
bool CShortestPath::DoService()
{    
    //��ʼ����ɫ��ɫ�б�
    InitGrayBlackList();
    
    //�Ƚ����ŵ���ɫ������
    g_lstGray.push_back(&g_bPt);
    
    bool bFind = false;   //�Ƿ���Ŀ���
    ST_PT *pDest = NULL;  //Ŀ���
	static const int TRY_MAX_COUNT = 1000;  //���г���������
	int iTryCnt = 0;   //���г��Դ���
    
	//������Ҳ���������̫��
    while (iTryCnt <= TRY_MAX_COUNT)
    {
		iTryCnt++;

        //������ɫ�б�
        list<ST_PT *>::iterator pos = g_lstGray.begin();
        for (; pos != g_lstGray.end(); ++pos)
        {
            //����ɫ�б��е�Ԫ�س�ȡ�����������ɫ�б���
            ST_PT *pPt = *pos;
            g_lstBlack.push_back(pPt);
        
            //Ϊ����߼�����Ч�ʣ��������Set��׼�⺯��
            int iBlack = ST2INT(*pPt);
            (void)g_setBlack.insert(iBlack);

            //����������Ѱ�ң��������Ŀ���ֱ���˳�
            if (Search(pPt, E_DIR_EAST)){bFind = true; break;}
            if (Search(pPt, E_DIR_SOUTH)) {bFind = true; break;}
            if (Search(pPt, E_DIR_NORTH)) {bFind = true; break;}
        }
        
        //���»�ɫ�б���Ϊ��Ѱ�ҹ����л����¼����ɫ�б�
        g_lstGray = g_lstObj;
        g_lstObj.clear();
        if (bFind)
        {
            break;
        }        
    }

	//δ�ҵ�·��
	if (!bFind)
	{
		printf("\nNot find that way!\n");
		return false;
	}

    //Ŀ�������ʱ�����У��ҳ�Ŀ���
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

    //��Ŀ������׷�ݵ���ʼ�㣬����������
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

//�Ƿ�����Ч��
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


