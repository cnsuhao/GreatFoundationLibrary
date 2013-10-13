/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

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
    string strFilePath = "..\\..\\..\\shortestpath\\project\\Resource\\"; //��ͼ�ļ�·��
    
    typedef struct _ST_MAPFILE
    {        
        bool bResult;   //��ͼ�ļ���ȡ���
        string filename; //��ͼ�ļ���
        char CanWalk[MAX_TOKEN_COUNT];          //ͨ·�ַ���
        char CannotWalk[MAX_TOKEN_COUNT];       //�ϰ��ַ���
        char DelimeterToken[MAX_TOKEN_COUNT];   //�ָ����ַ���
    }ST_MAPFILE;
    
    static const ST_MAPFILE s_StMapFile[] = 
    {
        {true, "map_normal.txt", "-", "~", " \r\n"},                    //normal
        {false, "map_abn_flat.txt", "-", "~", " \r\n"},                 //�쳣ƽ�ء���
        {false, "map_abn_uneven.txt", "-", "~", " \r\n"},               //�쳣�ϰ�  y
        {false, "map_abn_delimeter.txt", "-", "~", " \r\n"},            //�쳣�ָ��� /
        {true, "map_normal_multi_flat.txt", "-=", "~", " \r\n"},         //�����ƽ�ء���
        {true, "map_normal_multi_uneven.txt", "-", "~!", " \r\n"},       //������ϰ�����        
        {true, "map_normal_multi_delimeter.txt", "-", "~", " .\r\n"},    //����ŷָ�������
        
        {true, "map_normal_diff_row_len.txt", "-", "~", " \r\n"},       //ÿ�г��Ȳ�ͬ        
        {true, "map_normal_empty_row.txt", "-", "~", " \r\n"},          //����
        {true, "map_abn_row_upper_boundary.txt", "-", "~", " \r\n"},   //�г��߽�
        {true, "map_abn_col_upper_boundary.txt", "-", "~", " \r\n"},   //�г��߽�
        
        {false, "map_normal.txt", "-~", "~", " \r\n"},                    //normal ƽ�غ��ϰ��ַ����ظ� 
        {false, "map_normal.txt", "-", "~-", " \r\n"},                    //normal ƽ�غ��ϰ��ַ����ظ�
        {false, "map_normal.txt", "-", "~", " -\r\n"},                    //normal ƽ�غ��ϰ��ַ����ظ�                        
        
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

