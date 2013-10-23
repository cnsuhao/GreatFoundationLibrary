/******************************************************************************

                  ��Ȩ���� (C), 2010-2020, �й���Դ�������

 ******************************************************************************
  �� �� ��   : llt_searchstrategy.cpp
  �� �� ��   : ����
  ��    ��   : ndkk
  ��������   : 2013��10��16��
  ����޸�   :
  ��������   : �����������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��16��
    ��    ��   : ndkk
    �޸�����   : �����ļ�

******************************************************************************/


#include <gtest/gtest.h>
#include <stdio.h>
#include "comm_macro.h"
#include "sortstrategy.h"
#include <time.h>

class CSortSSuite : public testing::Test
{
protected:
    void SetUp() 
    {        
    }
    
    void TearDown() 
    {        
    }    
};

#define TWO_DIMEN_LEN 200

#define BEFORE_ARRAYSORT \
    {10,1,6,2,4,9,12,3}, \
    {10,59,156,32,24,49,66,333},   

#define AFTER_ARRAYSORT \
    {12,10,9,6,4,3,2,1}, \
    {333,156,66,59,49,32,24,10},


int iArray1[][TWO_DIMEN_LEN] = 
{
    BEFORE_ARRAYSORT            
};

int iArray2[][TWO_DIMEN_LEN] = 
{
    BEFORE_ARRAYSORT            
};

int iArray3[][TWO_DIMEN_LEN] = 
{
    BEFORE_ARRAYSORT            
};

int iArray4[][TWO_DIMEN_LEN] = 
{
    BEFORE_ARRAYSORT            
};

int iExpArray[][TWO_DIMEN_LEN] = 
{
    AFTER_ARRAYSORT
};

#define MYTEST_CASE(TNAME, CLASSNAME, ARNO) \
TEST_F(CSortSSuite, TNAME) \
{ \
    CLASSNAME m_sort; \
    clock_t curTime = clock(); \
    printf("now time %d\n", curTime); \
    for (int k = 0; k < COUNTOF(iArray##ARNO); k++) \
    { \
        m_sort.Sort(iArray##ARNO[k], COUNTOF(iArray##ARNO[k])); \
        for (int i = 0; i < COUNTOF(iArray##ARNO[k]); i++) \
        { \
            printf("%d ", iArray##ARNO[k][i]); \
            EXPECT_EQ(iArray##ARNO[k][i], iExpArray[k][i]); \
        } \
        printf("\n"); \
    } \
    curTime = clock(); \
    printf("now time %d\n", curTime); \
    printf("\n"); \
}

MYTEST_CASE(bubble, CSortStrategyBubble, 1)
MYTEST_CASE(insert, CSortStrategyInsert, 2)
MYTEST_CASE(select, CSortStrategySelect, 3)
MYTEST_CASE(quick, CSortStrategyQuick,  4)

