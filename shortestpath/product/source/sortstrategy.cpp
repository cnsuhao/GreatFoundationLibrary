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

void CSortStrategyQuick::Sort(int *Array, int low, int high)
{
    if (0 == Array) return;
    if (low < 0) return;
    if (high < 0) return;
    
    if (low >= high)
    {
        return;
    }
    
    int Begin = low;
    int End = high;
    
    int pivot = Array[low];
    while (low < high)
    {
        while ((low < high) && (Array[high] <= pivot)) --high;    
        Array[low] =  Array[high];
        
        while ((low < high) && (Array[low] >= pivot)) ++low;
        Array[high] =  Array[low];
    }
    Array[low] = pivot;
    
    Sort(Array, Begin, low-1);
    Sort(Array, low+1, End);
    
}
