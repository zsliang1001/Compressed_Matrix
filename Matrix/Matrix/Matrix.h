#pragma once

#include <stdio.h>
#include<stdlib.h>

#define Order	4	//矩阵阶数

typedef enum {
	Diag_Row_Frist		= 0,		//对称矩阵行优先
	Diag_Col_Frist		= 1,		//对称矩阵列优先
	Triag_Row_Frist		= 2,		//三角矩阵行优先
	Triag_Col_Frist		= 3,		//三角矩阵列优先
	Tridiag_Row_Frist	= 4,		//三对角矩阵行优先
	Tridiag_Col_Frist	= 5,		//三对角矩阵列优先
	Idle				= 6
}Matrix_Type;


