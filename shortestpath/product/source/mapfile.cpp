/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

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

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "comm_macro.h"
#include "mapfile.h"

//构造函数
CMapfile::CMapfile()
{    
    InitMap();
}

//析构函数
CMapfile::~CMapfile()
{
    CleanMap();
}

//获取地图数据        
int** CMapfile::GetMap(int &x, int &y)
{
    FILE* pHandle = NULL;
    if ((pHandle = fopen(m_FileName, "r" )) == NULL)
    {
        printf("The file '%s' was not opened\n", m_FileName);
        return NULL;
    }
    else
    {
        printf( "The file '%s' was opened\n", m_FileName);
    }

    char line[MAX_LINE_CHAR] = {0};
    int lineNo = 0;
    int m = 0;
    while( !feof( pHandle ) )
    {
        memset(line, 0, sizeof(line));
        char *pLine = fgets( line, MAX_LINE_CHAR, pHandle );

        if (NULL == pLine)
        {
            continue;
        }

        //解析每一行放入Map数据中
        m = 0;
        for (int i = 0; (i < MAX_LINE_CHAR) && (m < MAX_Y); i++)
        {
            //输入字符非法，直接返回NULL，表明地图不合法            
            if (!IsValidOfMapChar(line[i]))
            {
                printf("There are some special char [%c] which can not identify.",
                    line[i]);
                fclose(pHandle);
                return NULL;
            }

            //如果是间隔符，则继续寻找下一个字符
            if (IsDelimeterToken(line[i]))
            {
                continue;
            }

            E_WALK eWalk = Char2Int(line[i]);
            m_ppMap[lineNo][m] = static_cast<int>(eWalk);
            m++;
        }

        //累计行号，如果超过最大值，表明地图不合法
        lineNo++;
        if (lineNo >= MAX_X)
        {
            printf("Map is so larger, the line should be less than %d\n", MAX_X);
            fclose(pHandle);
            return NULL;
        }
    }

    x = lineNo;
    y = m;
    
    fclose(pHandle);
    
    return m_ppMap;
}

//设置文件名
void CMapfile::SetFileName(char filename[])
{
    memcpy(m_FileName, filename, sizeof(m_FileName));
}

//设置可行走的标识符
void CMapfile::SetCanWalkToken(char token[])
{
    memcpy(m_CanWalk, token, sizeof(m_CanWalk));
}

//设置无法行走的标识符
void CMapfile::SetCannotWalkToken(char token[])
{
    memcpy(m_CannotWalk, token, sizeof(m_CannotWalk));
}

//设置字符集间隔符
void CMapfile::SetDelimeterToken(char token[])
{
    memcpy(m_DelimeterToken, token, sizeof(m_DelimeterToken));
}

//创建Map数据
void CMapfile::InitMap()
{
    memset(m_FileName, 0, sizeof(m_FileName));
    memset(m_CanWalk, 0, sizeof(m_CanWalk));
    memset(m_CannotWalk, 0, sizeof(m_CannotWalk));
    memset(m_DelimeterToken, 0, sizeof(m_DelimeterToken));
    
    m_ppMap = new int*[MAX_X];
    memset(m_ppMap, 0, sizeof(int*)*MAX_X);
    for (int i = 0; i < MAX_X; i++)
    {        
        int *pMap = new int[MAX_Y];        
        memset(pMap, 0, sizeof(int)*MAX_Y);
        m_ppMap[i] = pMap;
    }
}

//释放Map数据
void CMapfile::CleanMap()
{
    if (NULL == m_ppMap)  
    {
        return;
    }

    for (int i = 0; i < MAX_X; i++)
    {
        if (NULL != m_ppMap[i])
        {
            delete[] m_ppMap[i];
            m_ppMap[i] = NULL;
        }        
    }

    delete[] m_ppMap;
    m_ppMap = NULL;    
}

//地图上字符转化为数字 0:通路 1:障碍 -1:非法值
E_WALK CMapfile::Char2Int(char ch)
{
    E_WALK eRet = E_WALK_CANNOT;
    char *pdest = NULL;

    pdest = strstr(static_cast<char *>(m_CanWalk), &ch);
    if (NULL != pdest)
    {
        eRet = E_WALK_CAN;
    }

    pdest = strstr(static_cast<char *>(m_CannotWalk), &ch);
    if (NULL != pdest)
    {
        eRet = E_WALK_CANNOT;
    }

    return eRet;
}

//地图字符是否合法
bool CMapfile::IsValidOfMapChar(char ch)
{
    char *pdestCan = strstr(static_cast<char *>(m_CanWalk), &ch);
    char *pdestCannot = strstr(static_cast<char *>(m_CannotWalk), &ch);
    char *pdestToken = strstr(static_cast<char *>(m_DelimeterToken), &ch);

    //如果该字符不属于任何一个集合，则不合法
    if ((NULL == pdestCan) && (NULL == pdestCannot) && (NULL == pdestToken))
    {
        return false;
    }
    return true;
}

//是否是间隔符
bool CMapfile::IsDelimeterToken(char ch)
{
    char *pdestToken = strstr(static_cast<char *>(m_DelimeterToken), &ch);
    if (NULL == pdestToken)
    {
        return false;
    }
    return true;
}

