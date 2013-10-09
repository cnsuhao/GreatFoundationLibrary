/******************************************************************************

                  版权所有 (C), 2010-2020, 脑袋空空技术有限公司

 ******************************************************************************
  文 件 名   : mapfile.h
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月6日
  最近修改   :
  功能描述   : 地图读取文件类
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月6日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MAPFILE_H__
#define __MAPFILE_H__

#define MAX_PATH_LEN 200        //最大文件路径字符串长度
#define MAX_TOKEN_COUNT 20      //最大标示个数
#define MAX_LINE_CHAR 200       //一行最大字符数

enum E_WALK
{
    E_WALK_CAN = 0,  //通路
    E_WALK_CANNOT,   //障碍
};

class CMapfile
{
public:
    //构造函数
    CMapfile();

    //析构函数
    ~CMapfile();
    
    //获取地图数据        
    int **GetMap(int &x, int &y);

    //设置文件名
    void SetFileName(char filename[]);

    //设置可行走的标识符
    void SetCanWalkToken(char token[]);

    //设置无法行走的标识符
    void SetCannotWalkToken(char token[]);

    //设置字符集间隔符
    void SetDelimeterToken(char token[]);

private:
    DISALLOW_COPY_ASSIGN(CMapfile);

    //创建Map数据
    void InitMap();

    //释放Map数据
    void CleanMap();

    //地图上字符转化为数字 0:通路 1:障碍 -1:非法值
    E_WALK Char2Int(char ch);

    //地图字符是否合法
    bool IsValidOfMapChar(char ch);

    //是否是间隔符
    bool IsDelimeterToken(char ch);
    
private:
    char m_FileName[MAX_PATH_LEN];      //文件名长度
    char m_CanWalk[MAX_TOKEN_COUNT];    //可以通路标识字符集
    char m_CannotWalk[MAX_TOKEN_COUNT]; //不能通路标识字符集
    char m_DelimeterToken[MAX_TOKEN_COUNT];   //字符中间的间隔符
    int **m_ppMap;   //Map数据
};

#endif //__MAPFILE_H__

