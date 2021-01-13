#include "Matrix.h"

bool Init_DiagMatrix(int* arr_Prt) {
	if (NULL == (arr_Prt = (int*)malloc(Order * (Order + 1) / 2)))
		return false;
	return true;
}

bool Init_TrigMatrix(int* arr_Prt) {
	if (NULL == (arr_Prt = (int*)malloc(Order * (Order + 1) / 2 + 1)))
		return false;
	return true;
}

bool Init_TridiagMatrix(int* arr_Prt) {
	if (NULL == (arr_Prt = (int*)malloc(3*Order-2)))
		return false;
	return true;
}

bool Data_Into_Arry(int* arr_Prt, int Data, int Row, int Col, Matrix_Type Type) {	//row 为行号，col为列号(不是数组下标),type组合形式（行优先，列优先）
	int k = 0;	//一维数组的下标

	if (NULL == arr_Prt || Row > Order || Col > Order)
		return false;
	switch (Type)
	{
	case Diag_Row_Frist://对称行优先矩阵
		if (Row >= Col)
			k = (Row * (Row - 1) / 2) + Col - 1;
		else
			k = (Col * (Col - 1) / 2) + Row - 1;
		break;
	case Diag_Col_Frist://对称列优先矩阵
		if (Row >= Col)
			k = ((Col - 1) * (2 * Order - Col + 2) / 2) + (Row - Col + 1) - 1;
		else
			k = ((Row - 1) * (2 * Order - Row + 2) / 2) + (Col - Row + 1) - 1;
		break;
	case Triag_Row_Frist://三角行优先矩阵
		if (Row >= Col)
			k = (Row * (Row - 1) / 2) + Col - 1;
		else
			k = Order * (Order + 1) / 2;
		break;
	case Triag_Col_Frist://三角列优先矩阵
		if (Row >= Col)
			k = ((Col - 1) * (2 * Order - Col + 2) / 2) + (Row - Col + 1) - 1;
		else
			k = Order * (Order + 1) / 2;
		break;
	case Tridiag_Row_Frist://三对角行优先矩阵
			k = (3 * (Row - 1) - 1) + (Col - Row + 2) - 1;
		break;
	case Tridiag_Col_Frist://三对角列优先矩阵
			k = (3 * (Col - 1) - 1) + (Row - Col + 2) - 1;
		break;
	default:
		return false;
		break;
	}

	*(arr_Prt+k) = Data;
	return true;
}

bool Assecc_Data(int* arr_Prt, int& Data, int Row, int Col, Matrix_Type Type) {
	int k = 0;	//一维数组的下标

	if (NULL == arr_Prt || Row > Order || Col > Order)
		return false;
	switch (Type)
	{
	case Diag_Row_Frist://对称行优先矩阵
		if (Row >= Col)
			k = (Row * (Row - 1) / 2) + Col - 1;
		else
			k = (Col * (Col - 1) / 2) + Row - 1;
		break;
	case Diag_Col_Frist://对称列优先矩阵
		if (Row >= Col)
			k = ((Col - 1) * (2 * Order - Col + 2) / 2) + Row - Col;
		else
			k = ((Row - 1) * (2 * Order - Row + 2) / 2) + Col - Row;
		break;
	case Triag_Row_Frist://三角行优先矩阵
		if (Row >= Col)
			k = (Row * (Row - 1) / 2) + Col - 1;
		else
			k = Order * (Order + 1) / 2;
		break;
	case Triag_Col_Frist://三角列优先矩阵
		if (Row >= Col)
			k = ((Col - 1) * (2 * Order - Col + 2) / 2) + (Row - Col + 1) - 1;
		else
			k = Order * (Order + 1) / 2;
		break;
	case Tridiag_Row_Frist://三对角行优先矩阵
			k = (3 * (Row - 1) - 1) + (Col - Row + 2) - 1;
		break;
	case Tridiag_Col_Frist://三对角列优先矩阵
			k = (3 * (Col - 1) - 1) + (Row - Col + 2) - 1;
		break;
	default:
		return false;
		break;
	}

	Data = *(arr_Prt + k);
	return true;
}