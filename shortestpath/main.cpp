/*
广度优先算法
本例采用广度优先算法进行计算
找到从(0,0)到(4,4)的最短路径
灰集合 黑集合
找到顶点 -> 相邻点 -> 再相邻点 -> 终点 -> 反向追溯
*/

#include <stdio.h>
#include <memory.h>
#include <set>
#include <list>
#include <assert.h>
using namespace std;

#define INVALID_COORDINATE -1
#define MAX_X 6
#define MAX_Y 10
static const int g_map[MAX_X][MAX_Y] = 
{
	0,1,0,0,0,1,1,1,1,1,  
	0,1,0,1,0,1,1,1,1,1,
	0,0,0,1,0,1,1,1,1,1,
	0,1,0,1,0,1,1,1,1,1,
	0,1,0,0,0,0,1,1,1,1,
	0,1,0,0,0,0,0,0,0,0,
};

typedef set<int> SET_INT;

typedef struct _ST_PT
{	
	int x;
	int y;
	_ST_PT *prevPt;  //注意: 不会在本结构体内申请内存，这里只是作为传参
	_ST_PT *nextPt;

	_ST_PT()
	{
		x = INVALID_COORDINATE;
		y = INVALID_COORDINATE;
		prevPt = NULL;
		nextPt = NULL;
	}
	
	_ST_PT(int i, int j)
	{
		x = i;
		y = j;
		prevPt = NULL;
		nextPt = NULL;
	}


	~_ST_PT()
	{
		prevPt = NULL;
		nextPt = NULL;
	}

	_ST_PT(const _ST_PT &obj)
	{
		if (this == &obj)
		{
			return;
		}
		Clone(obj);
	}

	_ST_PT& operator=(const _ST_PT &obj)
	{
		if (this != &obj)
		{
			Clone(obj);
		}
		return *this;
	}

	bool operator==(const _ST_PT &obj)
	{
		if ((x == obj.x)
			&& (y == obj.y))
		{
			return true;
		}
		return false;
	}


	bool IsValid()
	{
		if ((x >= MAX_X) || (x < 0))
		{
			return false;
		}

		if ((y >= MAX_Y) || (y < 0))
		{
			return false;
		}

		return true;
	}
private:
	void Clone(const _ST_PT &obj)
	{
		x = obj.x;
		y = obj.y;
		prevPt = obj.prevPt;
		nextPt = obj.nextPt;
	}

} ST_PT;

int ST2INT(ST_PT &obj)
{
	return (obj.x << 8) + obj.y;
}

ST_PT INT2ST(int i)
{
	ST_PT stObj;
	stObj.x = i >> 8;
	stObj.y = i - (stObj.x << 8);
	return stObj;
}


list<ST_PT *> g_lstGray; //灰色集合
list<ST_PT *> g_lstBlack; //黑色集合
list<ST_PT *> g_lstObj;  //用于临时使用队列
SET_INT g_setBlack;  //用于查找的黑色集合

ST_PT g_bPt(0,0);  //起始点
ST_PT g_ePt(MAX_X-1,MAX_Y-1);  //结束点

//bPt周围的点，即上/下/右等于0，且不在黑色集合中，不等于终点，则放入灰色集合中
bool IsPushGray(ST_PT &objP)
{
	if (!objP.IsValid())
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

bool IsDestPt(ST_PT &objP)
{
	if (g_ePt == objP)	
	{
		return true;
	}
	return false;
}

enum E_DIR
{
	E_DIR_EAST,
	E_DIR_SOUTH,
	E_DIR_NORTH
};

bool IsFind(ST_PT *prevPt, E_DIR eDir)
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

	if (!tmpPt->IsValid())
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


int main()
{
	ST_PT *pBegin = new ST_PT;
	memcpy(pBegin, &g_bPt, sizeof(ST_PT));
	g_lstGray.push_back(pBegin);
	bool bFind = false;
	ST_PT *pDest = NULL;
	
	while (1)
	{
		list<ST_PT *>::iterator pos = g_lstGray.begin();
		for (; pos != g_lstGray.end(); ++pos)
		{
			ST_PT *pPt = *pos;
			g_lstBlack.push_back(pPt);

			//printf("(%d, %d)\n", pPt->x, pPt->y);
		
			int iBlack = ST2INT(*pPt);
			g_setBlack.insert(iBlack);			

			if (IsFind(pPt, E_DIR_EAST)){bFind = true; break;}
			if (IsFind(pPt, E_DIR_SOUTH)) {bFind = true; break;}
			if (IsFind(pPt, E_DIR_NORTH)) {bFind = true; break;}
		}
		g_lstGray = g_lstObj;
		if (bFind)
		{
			break;
		}
		g_lstObj.clear();
	}

	//printf("===============\n");
	
	list<ST_PT *>::iterator pos = g_lstObj.begin();
	for (; pos != g_lstObj.end(); ++pos)
	{
		ST_PT *pTmp = *pos;
		if (g_ePt == *pTmp)
		{
			pDest = pTmp;
			break;
		}
	}

	ST_PT *pSwap = NULL;
	while (NULL != pDest->prevPt)
	{	
		//printf("(%d, %d)\n", pDest->x, pDest->y);
		pSwap = pDest;
		pDest = pDest->prevPt;
		pDest->nextPt = pSwap;
	}

	printf("===============\n");
	
	printf("(%d, %d)\n", pDest->x, pDest->y);
	while (NULL != pDest->nextPt)
	{
		pDest = pDest->nextPt;
		printf("(%d, %d)\n", pDest->x, pDest->y);		
	}

	//释放内存
	list<ST_PT *>::iterator posGray = g_lstGray.begin();
	for (; posGray != g_lstGray.end(); ++posGray)
	{
		delete *posGray;
	}
	g_lstGray.clear();

	list<ST_PT *>::iterator posBlack = g_lstBlack.begin();
	for (; posBlack != g_lstBlack.end(); ++posBlack)
	{
		delete *posBlack;
	}
	g_lstBlack.clear();
	
	printf("hello world");
	return 0;
}