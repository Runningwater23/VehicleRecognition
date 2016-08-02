#pragma once
#include <math.h>

template <class T> class CMyAbs
{
public:
	CMyAbs();
	~CMyAbs();
	static T Abs(T data);
};
template <class T> CMyAbs<T>::CMyAbs()
{

}
template <class T> CMyAbs<T>::~CMyAbs()
{

}
template <class T> T CMyAbs<T>::Abs(T data)
{
	if (data < 0) return -(data);
	return (data);
}
class CSolveEqution_AXB
{
public:
public:
	int n;
	long double *x, **A;
	void GetResultX(long double a[], int m);
};
inline void CSolveEqution_AXB::GetResultX(long double a[], int m)
{
	n = m;
	x = new long double[m];
	A = new long double *[m];
	for (int i = 0; i<m; i++)
	{
		A[i] = new long double[m + 1];
	}
	for (int i = 0; i<m; i++)
	for (int j = 0; j<m + 1; j++)
	{
		A[i][j] = a[i*(m + 1) + j];
	}
	for (int i = 0; i<m - 1; i++)
	{
		int maxIndex = i;
		long double maxVal = A[i][i];
		for (int j = i + 1; j<m; j++)
		{
			if ((int)abs(maxVal / A[j][i])<1)
			{
				maxIndex = j;
				maxVal = A[j][i];
			}
		}
		long double temp;
		for (int k = 0; k<m + 1; k++)
		{
			temp = A[i][k];
			A[i][k] = A[maxIndex][k];
			A[maxIndex][k] = temp;
		}
		for (int w = i + 1; w<m; w++)
		{
			long double ratio = 1.0*A[w][i] / A[i][i];
			for (int t = i; t<m + 1; t++)
			{
				A[w][t] -= ratio*A[i][t];
			}
		}

	}

	for (int i = m - 1; i >= 0; i--)
	{
		x[i] = A[i][m];
		for (int k = 0; k<m - i - 1; k++)
		{
			x[i] -= A[i][m - 1 - k] * x[m - 1 - k];
		}
		x[i] /= A[i][i];
	}
}
//////////////////////////////////////////////////////////////
class CMatrix
{
public:
	int rows;
	int cols;
	float *data;

	//��ʼ��  
	CMatrix(int m = 0, int n = 0);
	//����m  
	void setRows(int m);
	//����n  
	void setCols(int n);
	//��ʼ��  
	void initCMatrix(int m,int n);
	//�ͷ�  
	void freeCMatrix();
	//��ȡi,j���������  
	//ʧ�ܷ���-31415,�ɹ�����ֵ  
	float readData(int i, int j);
	//д��i,j���������  
	//ʧ�ܷ���-1,�ɹ�����1  
	int setData(int i, int j, float val);
};
//�����෽��  
//��ʼ��  
inline CMatrix::CMatrix(int m, int n)
{
	rows = m;
	cols = n;
	data = new float[m*n];
}

//����m  
inline void CMatrix::setRows(int m)
{
	rows = m;
}

//����cols  
inline void CMatrix::setCols(int n)
{
	cols = n;
}

//��ʼ��  
inline void CMatrix::initCMatrix(int m, int n)
{
	rows = m;
	cols = n;
	data = new float[m*n];
}
//�ͷ�  
inline void CMatrix::freeCMatrix()
{
		delete[]data;
}

//��ȡi,j���������  
//ʧ�ܷ���-31415,�ɹ�����ֵ  
inline float CMatrix::readData(int i, int j)
{
	if (i >= rows || j >= cols)
	{
		return -31415;
	}

	return data[i*cols+j];
}

//д��i,j���������  
//ʧ�ܷ���-1,�ɹ�����1  
inline int CMatrix::setData(int i, int j, float val)
{
	if (i >= rows || j >= cols)
	{
		return -1;
	}

	data[i*cols+j] = val;
	return 1;
}
class CMyMatrix
{
public:
	static int add(CMatrix *A, CMatrix *B, CMatrix *C);
	//C = A - B  
	//�ɹ�����1,ʧ�ܷ���-1  
	static int subtract(CMatrix *A, CMatrix *B, CMatrix *C);
	//C = A * B  
	//�ɹ�����1,ʧ�ܷ���-1  
	static int multiply(CMatrix *A, CMatrix *B, CMatrix *C);
	//��ת�þ���,B = AT  
	//�ɹ�����1,ʧ�ܷ���-1  
	static int transpos(CMatrix *A, CMatrix *B);
	//�������,B = A^(-1)  
	//�ɹ�����1,ʧ�ܷ���-1  
	static int inverse(CMatrix *A, CMatrix *B);
};
//C = A + B  
//�ɹ�����1,ʧ�ܷ���-1  
inline int CMyMatrix::add(CMatrix *A, CMatrix *B, CMatrix *C)
{
	int i = 0;
	int j = 0;
	//�ж��Ƿ��������  
	if (A->rows != B->rows || A->cols != B->cols
		|| A->rows != C->rows || A->cols != C->cols)
	{
		return -1;
	}
	//����  
	for (i = 0; i < C->rows; i++)
	{
		for (j = 0; j < C->cols; j++)
		{
			C->setData(i, j, A->readData(i, j) + B->readData(i, j));
		}
	}

	return 1;
}

//C = A - B  
//�ɹ�����1,ʧ�ܷ���-1  
inline int CMyMatrix::subtract(CMatrix *A, CMatrix *B, CMatrix *C)
{
	int i = 0;
	int j = 0;

	//�ж��Ƿ��������  
	if (A->rows != B->rows || A->cols != B->cols
		|| A->rows != C->rows || A->cols != C->cols)
	{
		return -1;
	}
	//����  
	for (i = 0; i < C->rows; i++)
	{
		for (j = 0; j < C->cols; j++)
		{
			C->setData(i, j, A->readData(i, j) - B->readData(i, j));
		}
	}

	return 1;
}

//C = A * B  
//�ɹ�����1,ʧ�ܷ���-1  
inline int CMyMatrix::multiply(CMatrix *A, CMatrix *B, CMatrix *C)
{
	int i = 0;
	int j = 0;
	int k = 0;
	float temp = 0;

	//�ж��Ƿ��������  
	if (A->rows != C->rows || B->cols != C->cols
		|| A->cols != B->rows)
	{
		return -1;
	}
	//����  
	CMatrix tempC(A->rows, B->cols);
	for (i = 0; i < C->rows; i++)
		for (j = 0; j < C->cols; j++)
		{
			temp = 0;
			for (k = 0; k < A->cols; k++)
			{
				temp += A->readData(i, k) * B->readData(k, j);
			}
			tempC.setData(i, j, temp);
		}
	for (i = 0; i < C->rows; i++)
	   for (j = 0; j < C->cols; j++)
	   {
		   C->data[i*C->cols + j] = tempC.data[i*C->cols + j];
	   }
	   tempC.freeCMatrix();
	return 1;
}

//��ת�þ���,B = AT  
//�ɹ�����1,ʧ�ܷ���-1  
inline int CMyMatrix::transpos(CMatrix *A, CMatrix *B)
{
	int i = 0;
	int j = 0;

	//�ж��Ƿ��������  
	if (A->rows != B->cols || A->cols != B->rows)
	{
		return -1;
	}
	//����  
	for (i = 0; i < B->rows; i++)
	{
		for (j = 0; j < B->cols; j++)
		{
			B->setData(i, j, A->readData(j, i));
		}
	}

	return 1;
}

//�������,B = A^(-1)  
//�ɹ�����1,ʧ�ܷ���-1  
inline int CMyMatrix::inverse(CMatrix *A, CMatrix *B)
{
	int i = 0;
	int j = 0;
	int k = 0;
	CMatrix m(A->rows, 2 * A->rows);
	float temp = 0;
	float b = 0;

	//�ж��Ƿ��������  
	if (A->rows != A->cols || B->rows != B->cols || A->rows != B->rows)
	{
		return -1;
	}

	//�������m = A | B��ʼ��  
	for (i = 0; i < m.rows; i++)
	{
		for (j = 0; j < m.cols; j++)
		{
			if (j <= A->cols - 1)
			{
				m.setData(i, j, A->readData(i, j));
			}
			else
			{
				if (i == j - A->cols)
				{
					m.setData(i, j, 1);
				}
				else
				{
					m.setData(i, j, 0);
				}
			}
		}
	}
	//��˹��Ԫ  
	//�任������  
	for (k = 0; k < m.rows - 1; k++)
	{
		//�������Ϊk,k����Ϊ0,���б任  
		if (m.readData(k, k) == 0)
		{
			for (i = k + 1; i < m.rows; i++)
			{
				if (m.readData(i, k) != 0)
				{
					break;
				}
			}
			if (i >= m.rows)
			{
				return -1;
			}
			else
			{
				//������  
				for (j = 0; j < m.cols; j++)
				{
					temp = m.readData(k, j);
					m.setData(k, j, m.readData(k + 1, j));
					m.setData(k + 1, j, temp);
				}
			}
		}
		//��Ԫ  
		for (i = k + 1; i < m.rows; i++)
		{
			//��ñ���  
			b = m.readData(i, k) / m.readData(k, k);
			//�б任  
			for (j = 0; j < m.cols; j++)
			{
				temp = m.readData(i, j) - b * m.readData(k, j);
				m.setData(i, j, temp);
			}
		}
	}
	//�任������  
	for (k = m.rows - 1; k > 0; k--)
	{
		//�������Ϊk,k����Ϊ0,���б任  
		if (m.readData(k, k) == 0)
		{
			for (i = k + 1; i < m.rows; i++)
			{
				if (m.readData(i, k) != 0)
				{
					break;
				}
			}
			if (i >= m.rows)
			{
				return -1;
			}
			else
			{
				//������  
				for (j = 0; j < m.cols; j++)
				{
					temp = m.readData(k, j);
					m.setData(k, j, m.readData(k + 1, j));
					m.setData(k + 1, j, temp);
				}
			}
		}

		//��Ԫ  
		for (i = k - 1; i >= 0; i--)
		{
			//��ñ���  
			b = m.readData(i, k) / m.readData(k, k);
			//�б任  
			for (j = 0; j < m.cols; j++)
			{
				temp = m.readData(i, j) - b * m.readData(k, j);
				m.setData(i, j, temp);
			}
		}
	}
	//����߷���Ϊ��λ����  
	for (i = 0; i < m.rows; i++)
	{
		if (m.readData(i, i) != 1)
		{
			//��ñ���  
			b = 1 / m.readData(i, i);
			//�б任  
			for (j = 0; j < m.cols; j++)
			{
				temp = m.readData(i, j) * b;
				m.setData(i, j, temp);
			}
		}
	}
	//��������  
	for (i = 0; i < B->rows; i++)
	{
		for (j = 0; j < B->rows; j++)
		{
			B->setData(i, j, m.readData(i, j + m.rows));
		}
	}
	//�ͷ��������  
	m.freeCMatrix();

	return 1;
}