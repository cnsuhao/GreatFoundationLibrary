/******************************************************************************

                  版权所有 (C), 2010-2020, 脑袋空空技术有限公司

 ******************************************************************************
  文 件 名   : mapfile.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月6日
  最近修改   :
  功能描述   : 二维地图文件读取类
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月6日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#include <memory.h>
#include "mapfile.h"

//构造函数
CMapfile::CMapfile()
{
    memset(m_FileName, 0, sizeof(m_FileName));
    memset(m_CanWalk, 0, sizeof(m_CanWalk));
    memset(m_CannotWalk, 0, sizeof(m_CannotWalk));
    memset(m_DelimeterToken, 0, sizeof(m_DelimeterToken));
}

//获取地图数据        
int CMapfile::**GetMap()
{
    return NULL;
}

//设置文件名
void CMapfile::SetFileName(char filename[])
{
}

//设置可行走的标识符
void CMapfile::SetCanWalkToken(char token[])
{
}

//设置无法行走的标识符
void CMapfile::SetCannotWalkToken(char token[])
{
}

//设置字符集间隔符
void CMapfile::SetDelimeterToken(char token[])
{

}


