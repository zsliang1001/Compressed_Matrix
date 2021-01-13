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

	Data = *(arr_Prt + k);
	return true;
}

bool Init_SparseMatrix(SparMatrix& Head) {			//初始化稀疏矩阵
	SparMatrix_Node* Pr_Array[Order] = { NULL };
	SparMatrix_Node* Pr = NULL;

	//行列指针的头结点，并记录行列的长度
	if (NULL == (Head = (SparMatrix_Node*)malloc(sizeof(SparMatrix_Node))))
		return false;
	Head->Row = Head->Col = Order;

	Pr = Head;

	for (int i = 1; i <= Order; i++) {
		if (NULL == (Pr_Array[i] = (SparMatrix_Node*)malloc(sizeof(SparMatrix_Node))))
			return false;
		Pr_Array[i]->down = Pr_Array[i]->right = Pr_Array[i];	//让行列头指针指向自己
		Pr_Array[i]->Row = Pr_Array[i]->Col = 0;//我一开的想法是=i，但是哪一行那一列完全可以用数组下标直接得到
		Pr->uni.next = Pr_Array[i];
		Pr = Pr_Array[i];
	}
	Pr->uni.next = NULL;

	return true;
}

bool Insert_Sparse_Matrix(SparMatrix Head, int Row, int Col, int Value) {
	if (Row > Order || Col > Order || NULL == Head->uni.next)return false;
	
	SparMatrix_Node* Node = NULL;
	SparMatrix_Node* Prt  = NULL;
	
	if (NULL == (Node = (SparMatrix_Node*)malloc(sizeof(SparMatrix_Node))))
		return false;
	Node->Row = Row;
	Node->Col = Col;
	Node->uni.data = Value;

	//行插入
	Prt = Head->uni.next + Row-1;
	while (Prt->right != Prt && Prt->right->Col < Col)//找到要插入位置的前一个node
		Prt = Prt->right;
	Node->right = Prt->right;
	Prt->right = Node;

	//列插入
	Prt = Head->uni.next + Col - 1;
	while (Prt->down != Prt && Prt->down->Row < Row)//找到要插入位置的前一个node
		Prt = Prt->down;
	Node->down = Prt->down;
	Prt->down = Node;

	return true;
}