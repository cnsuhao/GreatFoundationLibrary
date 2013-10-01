/*-----------------------------------------------------------------------------
    File: shortestpath.h
    Function: 最短路径查询算法实现
    Author: 唐衡 sfido@sina.cn
    Date: 2013-9-30
    City: Chengdu
-----------------------------------------------------------------------------*/

#ifndef __shortestpath_h__
#define __shortestpath_h__

#define INVALID_COORDINATE -1
#define MAX_X 100
#define MAX_Y 100

//点坐标对象
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

private:
	void Clone(const _ST_PT &obj)
	{
		x = obj.x;
		y = obj.y;
		prevPt = obj.prevPt;
		nextPt = obj.nextPt;
	}

} ST_PT;

typedef set<int> SET_INT;

//行动方向
enum E_DIR
{
	E_DIR_EAST,
	E_DIR_SOUTH,
	E_DIR_NORTH
};

class CShortestPath
{
public:
    //构造函数
    CShortestPath();
    
    //析构函数
    ~CShortestPath();

    //设置起点
    void SetBeginPoint(ST_PT &obj);

    //设置终点
    void SetEndPoint(ST_PT &obj);

    //设置地图
    bool SetMap(int x, int y, int **pMap);
    
    //打印结果
    void ShowResult();

    //计算最短路径
    void DoService();

private:
    
    //点坐标转化为int值，作为Set集合查找时更快
    int ST2INT(ST_PT &obj);

    //int值转化为点坐标
    ST_PT INT2ST(int i);

    //是否放到灰色集合中
    bool IsPushGray(ST_PT &objP);

    //是否是目标点
    bool IsDestPt(ST_PT &objP);
    
    //是否是有效点
    bool IsPointValid(ST_PT &obj);	

    //是否找到目标点
    bool Search(ST_PT *prevPt, E_DIR eDir);
    
    //清除灰色和黑色集合内存
    void InitGrayBlackList();

private:
    int g_map[MAX_X][MAX_Y];  //图形坐标点
    int m_maxX;   //最大x坐标
    int m_maxY;   //最大y坐标
    list<ST_PT *> g_lstGray; //灰色集合
    list<ST_PT *> g_lstBlack; //黑色集合
    list<ST_PT *> g_lstObj;  //用于临时使用队列
    SET_INT g_setBlack;  //用于查找的黑色集合
    ST_PT g_bPt;    //起始点
    ST_PT g_ePt;    //结束点
};

#endif //__shortestpath_h__
