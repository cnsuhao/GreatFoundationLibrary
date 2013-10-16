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
    string strFilePath = "..\\..\\..\\shortestpath\\project\\Resource\\"; //��ͼ�ļ�·��
    
    typedef struct _ST_TESTCONDITION
    {
        bool bResult;   //ִ�н��      
        string filename; //��ͼ�ļ���  
        BYTE bX;    //���X����
        BYTE bY;    //���Y����
        BYTE eX;    //�յ�X����
        BYTE eY;    //�յ�Y����
    } ST_TESTCONDITION;
    
    static const ST_TESTCONDITION s_TestCond[] = 
    {
        //��ͨ��ͼ
        {true, "map_s_walk.txt", 0, 0, 2, 7},
        {true, "map_s_walk.txt", 2, 7, 0, 0},
        {true, "map_s_walk.txt", 3, 7, 0, 0},        
        {false, "map_s_walk.txt", 0, 0, 0, 0},        
        {false, "map_s_walk.txt", 0, 2, 0, 0},        
        {true, "map_s_walk.txt", 0, 3, 0, 0},        
        {false,"map_s_walk.txt",  0, 10, 0, 0},
        {false,"map_s_walk.txt",  0, 0, 0, 100},        
        {false,"map_s_walk.txt",  100, 0, 0, 0},
        {false, "map_s_walk.txt", 0, 0, 100, 0},
        {false,"map_s_walk.txt",  0, 0, 6, 3},        
        {false,"map_s_walk.txt",  0, 0, 4, 3},
        {true,"map_s_walk.txt",  0, 0, 4, 4},
        
        //��ͼ����ͨ
        {false,"map_s_not_walk.txt",  0, 0, 3, 6},  
        {false,"map_s_not_walk.txt",  0, 0, 3, 5},  
        {true,"map_s_not_walk.txt",  0, 0, 3, 4},      
    };
    
    for (int i = 0; i < COUNTOF(s_TestCond); i++)
    {
        CMapfile Mapfile;       
        string strTmp = strFilePath + s_TestCond[i].filename;
        char FileName[MAX_PATH_LEN] = {0};
        memcpy(FileName, strTmp.c_str(), MAX_PATH_LEN);
        Mapfile.SetFileName(FileName);
        Mapfile.SetCanWalkToken("-");
        Mapfile.SetCannotWalkToken("~");
        Mapfile.SetDelimeterToken(" \r\n");    
        int x = 0;
        int y = 0;
        int **ppMap = Mapfile.GetMap(x, y);    
        m_pShortestPath->SetMap(x, y, ppMap);
    
        bool bRet = false;
        
        //���������յ�
	    ST_PT bPt(s_TestCond[i].bX, s_TestCond[i].bY);
        ST_PT ePt(s_TestCond[i].eX, s_TestCond[i].eY);
        
        bRet = m_pShortestPath->SetBeginPoint(bPt);        
        if (!bRet)
        {
            EXPECT_EQ(s_TestCond[i].bResult, bRet);
            continue;
        }
        
        bRet = m_pShortestPath->SetEndPoint(ePt);        
        if (!bRet)
        {
            EXPECT_EQ(s_TestCond[i].bResult, bRet);
            continue;
        }

	    //��������㷨
	    bRet = m_pShortestPath->DoService();
	    EXPECT_EQ(s_TestCond[i].bResult, bRet);
        if (bRet)
	    {
		    m_pShortestPath->ShowResult();		
	    }	    
    }
}