/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : mapfile.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��6��
  ����޸�   :
  ��������   : ��ά��ͼ�ļ���ȡ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��6��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "comm_macro.h"
#include "mapfile.h"

//���캯��
CMapfile::CMapfile()
{    
    CreateMap();
}

//��������
CMapfile::~CMapfile()
{
    DestoryMap();
}

//��ȡ��ͼ����        
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

    //��ʼ����ֵ
    InitMap();

    char line[MAX_LINE_CHAR] = {0};
    int lineNo = 0;  //�����
    int colNo = 0;   //�����
    int m = 0;

    while( !feof( pHandle ) )
    {
        memset(line, 0, sizeof(line));
        char *pLine = fgets( line, MAX_LINE_CHAR, pHandle );

        if (NULL == pLine)
        {
            continue;
        }

        //����ÿһ�з���Map������
        m = 0;
        for (WORD i = 0; (i < strlen(line)) && (m < MAX_Y); i++)
        {
            //�����ַ��Ƿ���ֱ�ӷ���NULL��������ͼ���Ϸ�            
            if (!IsValidOfMapChar(line[i]))
            {
                printf("There are some special char [%c] which can not identify.\n",
                    line[i]);
                fclose(pHandle);
                return NULL;
            }

            //����Ǽ�����������Ѱ����һ���ַ�
            if (IsDelimeterToken(line[i]))
            {
                continue;
            }

            E_WALK eWalk = Char2Int(line[i]);
            m_ppMap[lineNo][m] = static_cast<int>(eWalk);
            m++;

            //ȡ���������
            if (m > colNo)
            {
                colNo = m;
            }
        }

        //�ۼ��кţ�����������ֵ��������ͼ���Ϸ�
        lineNo++;
        if (lineNo >= MAX_X)
        {
            printf("Map is so larger, the line should be less than %d\n", MAX_X);
            fclose(pHandle);
            return NULL;
        }
    }

    x = lineNo;
    y = colNo;
    
    fclose(pHandle);
    
    return m_ppMap;
}

//�����ļ���
void CMapfile::SetFileName(char filename[])
{
    memset(m_FileName, 0, sizeof(m_FileName));
    memcpy(m_FileName, filename, sizeof(m_FileName));
}

//���ÿ����ߵı�ʶ��
void CMapfile::SetCanWalkToken(char token[])
{
    memset(m_CanWalk, 0, sizeof(m_CanWalk));
    memcpy(m_CanWalk, token, sizeof(m_CanWalk));
}

//�����޷����ߵı�ʶ��
void CMapfile::SetCannotWalkToken(char token[])
{
    memset(m_CannotWalk, 0, sizeof(m_CannotWalk));
    memcpy(m_CannotWalk, token, sizeof(m_CannotWalk));
}

//�����ַ��������
void CMapfile::SetDelimeterToken(char token[])
{
    memset(m_DelimeterToken, 0, sizeof(m_DelimeterToken));
    memcpy(m_DelimeterToken, token, sizeof(m_DelimeterToken));
}

//����Map����
void CMapfile::CreateMap()
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

//�ͷ�Map����
void CMapfile::DestoryMap()
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

//��ʼ��Map����
void CMapfile::InitMap()
{
    if (NULL == m_ppMap)  
    {
        return;
    }
    
    for (int i = 0; i < MAX_X; i++)
    {   
        if (NULL == m_ppMap[i])
        {
            return;
        }
        
        for (int j = 0; j < MAX_Y; j++)
        {            
            m_ppMap[i][j] = 1;
        }
    }
}

//��ͼ���ַ�ת��Ϊ���� 0:ͨ· 1:�ϰ� -1:�Ƿ�ֵ
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

//��ͼ�ַ��Ƿ�Ϸ�
bool CMapfile::IsValidOfMapChar(char ch)
{
    char *pdestCan = strstr(static_cast<char *>(m_CanWalk), &ch);
    char *pdestCannot = strstr(static_cast<char *>(m_CannotWalk), &ch);
    char *pdestToken = strstr(static_cast<char *>(m_DelimeterToken), &ch);

    //������ַ��������κ�һ�����ϣ��򲻺Ϸ�
    if ((NULL == pdestCan) && (NULL == pdestCannot) && (NULL == pdestToken))
    {
        return false;
    }

    //��������������ַ�����ͬһ�����ϣ��򲻺Ϸ�
    if (((NULL != pdestCan) && (NULL != pdestCannot))
        || ((NULL != pdestCan) && (NULL != pdestToken))
        || ((NULL != pdestCannot) && (NULL != pdestToken))
        )
    {
        printf("repeat char [%c] \n", ch);
        return false;
    }
    return true;
}

//�Ƿ��Ǽ����
bool CMapfile::IsDelimeterToken(char ch)
{
    char *pdestToken = strstr(static_cast<char *>(m_DelimeterToken), &ch);
    if (NULL == pdestToken)
    {
        return false;
    }
    return true;
}

