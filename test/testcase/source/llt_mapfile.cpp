/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �Դ��տռ������޹�˾

 ******************************************************************************
  �� �� ��   : llt_mapfile.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��9��
  ����޸�   :
  ��������   : Mapfile��LLT����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��9��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/
#include <gtest/gtest.h>
#include <stdio.h>
#include "comm_macro.h"
#include "mapfile.h"

class CMapFileTestSuite : public testing::Test
{
protected:
    void SetUp() 
    {
        m_pMapfile = new CMapfile();
    }
    
    void TearDown() 
    {
        if (NULL != m_pMapfile)
        {
            delete m_pMapfile;
            m_pMapfile = NULL;
        }
    }
    
    CMapfile *m_pMapfile;    
};

TEST_F(CMapFileTestSuite, DoService)
{
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

    if (NULL != ppMap)
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                printf("%d ", ppMap[i][j]);
            }
            printf("\n");
        }
    }
}

