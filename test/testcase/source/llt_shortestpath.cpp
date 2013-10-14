/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : llt_shortestpath.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��3��
  ����޸�   :
  ��������   : ���·���㷨������
  �����б�   :
              TEST
  �޸���ʷ   :
  1.��    ��   : 2013��10��3��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

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
    
	//����Map
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
        bool bResult;   //ִ�н��
        BYTE bX;    //���X����
        BYTE bY;    //���Y����
        BYTE eX;    //�յ�X����
        BYTE eY;    //�յ�Y����
    } ST_TESTCONDITION;
    
    static const ST_TESTCONDITION s_TestCond[] = 
    {
        {true, 0, 0, 2, 7},
        {true, 2, 7, 0, 0},
    };
    
    for (int i = 0; i < COUNTOF(s_TestCond); i++)
    {
        //���������յ�
	    ST_PT bPt(s_TestCond[i].bX, s_TestCond[i].bY);
        ST_PT ePt(s_TestCond[i].eX, s_TestCond[i].eY);
        
        m_pShortestPath->SetBeginPoint(bPt);
        m_pShortestPath->SetEndPoint(ePt);

	    //��������㷨
        if (m_pShortestPath->DoService())
	    {
		    m_pShortestPath->ShowResult();		
	    }

	    EXPECT_EQ(s_TestCond[i].bResult, m_pShortestPath->DoService());
    }	
    
    #if 1
    //�ͷ��ڴ�
    delete m_pMapfile;
    m_pMapfile = NULL;
    #endif

}