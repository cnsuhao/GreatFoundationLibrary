/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �Դ��տռ������޹�˾

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

#include <memory.h>
#include "mapfile.h"

//���캯��
CMapfile::CMapfile()
{
    memset(m_FileName, 0, sizeof(m_FileName));
    memset(m_CanWalk, 0, sizeof(m_CanWalk));
    memset(m_CannotWalk, 0, sizeof(m_CannotWalk));
    memset(m_DelimeterToken, 0, sizeof(m_DelimeterToken));
}

//��ȡ��ͼ����        
int CMapfile::**GetMap()
{
    return NULL;
}

//�����ļ���
void CMapfile::SetFileName(char filename[])
{
}

//���ÿ����ߵı�ʶ��
void CMapfile::SetCanWalkToken(char token[])
{
}

//�����޷����ߵı�ʶ��
void CMapfile::SetCannotWalkToken(char token[])
{
}

//�����ַ��������
void CMapfile::SetDelimeterToken(char token[])
{

}


