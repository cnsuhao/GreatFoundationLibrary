/*--------------------------------------------------
��������㷨
�������ù�������㷨���м���
�ҵ���(0,0)��(4,4)�����·��
�Ҽ��� �ڼ���
�ҵ����� -> ���ڵ� -> �����ڵ� -> �յ� -> ����׷��
---------------------------------------------------*/

#include <stdio.h>
#include <memory.h>
#include <set>
#include <list>
#include <assert.h>
using namespace std;

#include "shortestpath.h"

static const int in_map[3][10] = 
{
	0,1,0,0,0,0,0,0,0,1,  
	0,1,0,1,0,1,1,1,0,1,
	0,0,0,0,1,1,1,1,0,0,	
};

int main()
{
	CShortestPath sPath;
	ST_PT bPt(0,0);
	ST_PT ePt(2,9);
	sPath.SetBeginPoint(bPt);
	sPath.SetEndPoint(ePt);		
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
	
	sPath.SetMap(MAX_X, MAX_Y, ppMap);
	sPath.DoService();
	sPath.ShowResult();
	
	//�ͷ��ڴ�
	for (int m = 0; m < MAX_X; m++)
	{
	    delete[] ppMap[m];
	}
	delete[] ppMap;
	
	return 0;
}