/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �Դ��տռ������޹�˾

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
	//����Map
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

	//���������յ�
	ST_PT bPt(0,0);
    ST_PT ePt(2,3);
    
    m_pShortestPath->SetBeginPoint(bPt);
    m_pShortestPath->SetEndPoint(ePt);

	//��������㷨
    if (m_pShortestPath->DoService())
	{
		m_pShortestPath->ShowResult();		
	}

	EXPECT_EQ(true, m_pShortestPath->DoService());
    
    //�ͷ��ڴ�
    for (int m = 0; m < MAX_X; m++)
    {
        delete[] ppMap[m];
    }
    delete[] ppMap;

    EXPECT_EQ(6, 6);

}