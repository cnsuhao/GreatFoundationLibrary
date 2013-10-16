/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : searchstrategy.h
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��16��
  ����޸�   :
  ��������   : ��������,�㼯�����е������㷨
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��16��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __SEARCHSTRATEGY_H__
#define __SEARCHSTRATEGY_H__

//�������
class ISortStrategy
{
public:
    virtual void Sort(int *Array, int len) = 0;
protected:
    virtual void Swap(int &i, int &j);
};

//ð������
class CSortStrategyBubble : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
};

//��������
class CSortStrategyInsert : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
};

//ѡ������
class CSortStrategySelect : public ISortStrategy
{
public:
    void Sort(int *Array, int len);    
};

//��������
class CSortStrategyQuick : public ISortStrategy
{
public:
    void Sort(int *Array, int len);
private:
    void Sort(int *Array, int iBegin, int iEnd);    
};


#endif  //__SEARCHSTRATEGY_H__

