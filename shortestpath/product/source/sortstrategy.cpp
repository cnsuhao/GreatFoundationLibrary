/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : searchstrategy.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��16��
  ����޸�   :
  ��������   : �������Լ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��16��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/

#include "sortstrategy.h"

void ISortStrategy::Swap(int &i, int &j)
{
    int iTmp = i;
    i = j;
    j = iTmp;
}

//���������ð�ݣ�ѡ�񣬲����������򷽷�
//ð������ ��ˮ��һ��һ����һ��������ȥ
void CSortStrategyBubble::Sort(int *Array, int len)
{
    for (int i = 0; i < len - 1; i++)      //ð��ѭ������
    {
        for (int j = 0; j < len - 1 - i; j++)  //һ��ð������ʱ��
        {   
            if (Array[j] < Array[j+1])
            {
                Swap(Array[j], Array[j+1]);
            }
        }  
    }
}

//������������ǰ�����Ѿ��ź��ˣ��ȶ�ͷ����Ԫ������
//8 5 4 3
void CSortStrategyInsert::Sort(int *Array, int len)
{   
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (Array[j] < Array[i])
            {
                for (int k = i; k > j; k--) //�ȽϺ�Ҫ������
                {
                    Swap(Array[k], Array[k-1]);
                }
            }
        }
    }
}

//ѡ��������ѡ����С�ģ�Ȼ��ѡ��С�ġ�����
void CSortStrategySelect::Sort(int *Array, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if (Array[i] < Array[j]) //һֱ��ͬһԪ�ز���
            {
                Swap(Array[i], Array[j]);               
            }
        }
    } 
}

//�������� ���ַ� ����ݹ�
//10 8 5 12 7
void CSortStrategyQuick::Sort(int *Array, int len)
{
     Sort(Array, 0, len-1);
}

void CSortStrategyQuick::Sort(int *Array, int iBegin, int iEnd)
{
    if (iBegin >= iEnd)
    {
        return;
    }
    int k = Array[iBegin];
    int i = iBegin;
    int j = iEnd + 1;
    while (true)
    {
        while ((i < iEnd) && (Array[++i] > k));
        while ((j > iBegin) && (Array[--j] < k));
        if (i < j)
        {
            Swap(Array[i], Array[j]);
        }
        else
        {
            break;
        }
    }
    
    Swap(Array[iBegin], Array[j]);
    Sort(Array, 0, j-1);
    Sort(Array, j+1, iEnd);
}
