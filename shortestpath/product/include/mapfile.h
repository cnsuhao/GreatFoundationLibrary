/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �Դ��տռ������޹�˾

 ******************************************************************************
  �� �� ��   : mapfile.h
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��6��
  ����޸�   :
  ��������   : ��ͼ��ȡ�ļ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��6��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MAPFILE_H__
#define __MAPFILE_H__

#define MAX_PATH_LEN 200        //����ļ�·���ַ�������
#define MAX_TOKEN_COUNT 20      //����ʾ����
#define MAX_LINE_CHAR 200       //һ������ַ���

enum E_WALK
{
    E_WALK_CAN = 0,  //ͨ·
    E_WALK_CANNOT,   //�ϰ�
};

class CMapfile
{
public:
    //���캯��
    CMapfile();

    //��������
    ~CMapfile();
    
    //��ȡ��ͼ����        
    int **GetMap(int &x, int &y);

    //�����ļ���
    void SetFileName(char filename[]);

    //���ÿ����ߵı�ʶ��
    void SetCanWalkToken(char token[]);

    //�����޷����ߵı�ʶ��
    void SetCannotWalkToken(char token[]);

    //�����ַ��������
    void SetDelimeterToken(char token[]);

private:
    DISALLOW_COPY_ASSIGN(CMapfile);

    //����Map����
    void InitMap();

    //�ͷ�Map����
    void CleanMap();

    //��ͼ���ַ�ת��Ϊ���� 0:ͨ· 1:�ϰ� -1:�Ƿ�ֵ
    E_WALK Char2Int(char ch);

    //��ͼ�ַ��Ƿ�Ϸ�
    bool IsValidOfMapChar(char ch);

    //�Ƿ��Ǽ����
    bool IsDelimeterToken(char ch);
    
private:
    char m_FileName[MAX_PATH_LEN];      //�ļ�������
    char m_CanWalk[MAX_TOKEN_COUNT];    //����ͨ·��ʶ�ַ���
    char m_CannotWalk[MAX_TOKEN_COUNT]; //����ͨ·��ʶ�ַ���
    char m_DelimeterToken[MAX_TOKEN_COUNT];   //�ַ��м�ļ����
    int **m_ppMap;   //Map����
};

#endif //__MAPFILE_H__

