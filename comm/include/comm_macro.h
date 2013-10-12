/******************************************************************************

                  版权所有 (C), 2010-2020, 中国开源基础类库

 ******************************************************************************
  文 件 名   : comm_macro.h
  版 本 号   : 初稿
  作    者   : ndkk
  生成日期   : 2013年10月6日
  最近修改   :
  功能描述   : 公共宏头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月6日
    作    者   : ndkk
    修改内容   : 创建文件

******************************************************************************/

#ifndef __COMM_MACRO_H__
#define __COMM_MACRO_H__

#define DISALLOW_COPY_ASSIGN(classname) classname(const classname &); \
    classname& operator=(const classname &)

//MapFile
#define INVALID_VALID -1
#define MAX_X 100
#define MAX_Y 100

#endif //__COMM_MACRO_H__

