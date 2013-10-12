/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : main.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��3��
  ����޸�   :
  ��������   :  ��������㷨
                �������ù�������㷨���м���
                �ҵ���(0,0)��(4,4)�����·��
                �Ҽ��� �ڼ���
                �ҵ����� -> ���ڵ� -> �����ڵ� -> �յ� -> ����׷��
  �����б�   :
              main
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
#include "mapfile.h"

int main()
{    
    CMapfile *m_pMapfile = new CMapfile();
	//����Map
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

	//���������յ�
	ST_PT bPt(0,0);
    ST_PT ePt(2,7);
    
    (void)m_pShortestPath->SetBeginPoint(bPt);
    (void)m_pShortestPath->SetEndPoint(ePt);

	//��������㷨
    if (m_pShortestPath->DoService())
	{
		m_pShortestPath->ShowResult();		
	}	
    
    //�ͷ��ڴ�
    delete m_pShortestPath;
    delete m_pMapfile;
    
    return 0;
}
