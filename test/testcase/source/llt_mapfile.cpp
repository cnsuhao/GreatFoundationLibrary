/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : llt_mapfile.cpp
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : Mapfile的LLT测试
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/
#include <gtest/gtest.h>
#include <stdio.h>
#include "comm_macro.h"
#include "mapfile.h"
#include <string>
using namespace std;


class CMapFileTestSuite : public testing::Test
{
protected:
    void SetUp() 
    {
    }    
    void TearDown() 
    {       
    }
};

TEST_F(CMapFileTestSuite, TestMap)
{
    string strFilePath = "..\\..\\..\\shortestpath\\project\\Resource\\"; //地图文件路径
    
    typedef struct _ST_MAPFILE
    {        
        bool bResult;   //地图文件读取结果
        string filename; //地图文件名
        char CanWalk[MAX_TOKEN_COUNT];          //通路字符集
        char CannotWalk[MAX_TOKEN_COUNT];       //障碍字符集
        char DelimeterToken[MAX_TOKEN_COUNT];   //分隔符字符集
    }ST_MAPFILE;
    
    static const ST_MAPFILE s_StMapFile[] = 
    {
        {true, "map_normal.txt", "-", "~", " \r\n"},                    //normal
        {false, "map_abn_flat.txt", "-", "~", " \r\n"},                 //异常平地　ｘ
        {false, "map_abn_uneven.txt", "-", "~", " \r\n"},               //异常障碍  y
        {false, "map_abn_delimeter.txt", "-", "~", " \r\n"},            //异常分隔副 /
        {true, "map_normal_multi_flat.txt", "-=", "~", " \r\n"},         //多符号平地　＝
        {true, "map_normal_multi_uneven.txt", "-", "~!", " \r\n"},       //多符号障碍　！        
        {true, "map_normal_multi_delimeter.txt", "-", "~", " .\r\n"},    //多符号分隔符　．
        
        {true, "map_normal_diff_row_len.txt", "-", "~", " \r\n"},       //每行长度不同        
        {true, "map_normal_empty_row.txt", "-", "~", " \r\n"},          //空行
        {true, "map_abn_row_upper_boundary.txt", "-", "~", " \r\n"},   //行出边界
        {true, "map_abn_col_upper_boundary.txt", "-", "~", " \r\n"},   //列出边界
        
        {false, "map_normal.txt", "-~", "~", " \r\n"},                    //normal 平地和障碍字符集重复 
        {false, "map_normal.txt", "-", "~-", " \r\n"},                    //normal 平地和障碍字符集重复
        {false, "map_normal.txt", "-", "~", " -\r\n"},                    //normal 平地和障碍字符集重复                        
        
    };
    
    for (WORD i = 0; i < COUNTOF(s_StMapFile); i++)
    {
        CMapfile Mapfile;
        string strTmp = strFilePath + s_StMapFile[i].filename;
        char FileName[MAX_PATH_LEN] = {0};
        memcpy(FileName, strTmp.c_str(), MAX_PATH_LEN);    
        Mapfile.SetFileName(FileName);
        Mapfile.SetCanWalkToken(const_cast<char *>(s_StMapFile[i].CanWalk));
        Mapfile.SetCannotWalkToken(const_cast<char *>(s_StMapFile[i].CannotWalk));
        Mapfile.SetDelimeterToken(const_cast<char *>(s_StMapFile[i].DelimeterToken));
        
        int x = 0;
        int y = 0;
        int **ppMap = Mapfile.GetMap(x, y);
        
        EXPECT_EQ(s_StMapFile[i].bResult, (NULL != ppMap));

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
        
        ppMap = NULL;
        
    }
    
    
}

