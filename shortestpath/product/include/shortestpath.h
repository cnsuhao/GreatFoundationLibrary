/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �Դ��տռ������޹�˾

 ******************************************************************************
  �� �� ��   : shortestpath.h
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��3��
  ����޸�   :
  ��������   : ���·����ѯ�㷨ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��3��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __shortestpath_h__
#define __shortestpath_h__

#define INVALID_COORDINATE -1
#define MAX_X 100
#define MAX_Y 100

//���������
typedef struct _ST_PT
{	
	int x;
	int y;
	_ST_PT *prevPt;  //ע��: �����ڱ��ṹ���������ڴ棬����ֻ����Ϊ����
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

//�ж�����
enum E_DIR
{
	E_DIR_EAST,
	E_DIR_SOUTH,
	E_DIR_NORTH
};

class CShortestPath
{
public:
    //���캯��
    CShortestPath();
    
    //��������
    ~CShortestPath();

    //�������
    void SetBeginPoint(ST_PT &obj);

    //�����յ�
    void SetEndPoint(ST_PT &obj);

    //���õ�ͼ
    bool SetMap(int x, int y, int **pMap);
    
    //��ӡ���
    void ShowResult();

    //�������·��
    void DoService();

private:
    
    //������ת��Ϊintֵ����ΪSet���ϲ���ʱ����
    int ST2INT(ST_PT &obj);

    //intֵת��Ϊ������
    ST_PT INT2ST(int i);

    //�Ƿ�ŵ���ɫ������
    bool IsPushGray(ST_PT &objP);

    //�Ƿ���Ŀ���
    bool IsDestPt(ST_PT &objP);
    
    //�Ƿ�����Ч��
    bool IsPointValid(ST_PT &obj);	

    //�Ƿ��ҵ�Ŀ���
    bool Search(ST_PT *prevPt, E_DIR eDir);
    
    //�����ɫ�ͺ�ɫ�����ڴ�
    void InitGrayBlackList();

private:
    int g_map[MAX_X][MAX_Y];  //ͼ�������
    int m_maxX;   //���x����
    int m_maxY;   //���y����
    list<ST_PT *> g_lstGray; //��ɫ����
    list<ST_PT *> g_lstBlack; //��ɫ����
    list<ST_PT *> g_lstObj;  //������ʱʹ�ö���
    SET_INT g_setBlack;  //���ڲ��ҵĺ�ɫ����
    ST_PT g_bPt;    //��ʼ��
    ST_PT g_ePt;    //������
};

#endif //__shortestpath_h__
