#pragma once

#include <stdio.h>
#include<stdlib.h>

#define Order	4	//�������

typedef enum {
	Diag_Row_Frist		= 0,		//�Գƾ���������
	Diag_Col_Frist		= 1,		//�Գƾ���������
	Triag_Row_Frist		= 2,		//���Ǿ���������
	Triag_Col_Frist		= 3,		//���Ǿ���������
	Tridiag_Row_Frist	= 4,		//���ԽǾ���������
	Tridiag_Col_Frist	= 5,		//���ԽǾ���������
	Idle				= 6
}Matrix_Type;


