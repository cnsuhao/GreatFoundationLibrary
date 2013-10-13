/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : comm_macro.h
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��6��
  ����޸�   :
  ��������   : ������ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��6��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __COMM_MACRO_H__
#define __COMM_MACRO_H__

#define DISALLOW_COPY_ASSIGN(classname) classname(const classname &); \
    classname& operator=(const classname &)

//MapFile
#define INVALID_VALID -1
#define MAX_X 15
#define MAX_Y 8

//�����������Ͷ���
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//���������С
#define COUNTOF(arr) sizeof(arr)/sizeof(arr[0])

#endif //__COMM_MACRO_H__

