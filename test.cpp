// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

#include <iostream>
#include <vector>

#include <assert.h>
#include <time.h>

#include <algorithm>
#include <unordered_map>



#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

#include "Tree.h"
#include "RB_Tree.h"
#include "Order_Tree.h"
#include "Interval_Tree.h"
#include "HaffmanTree.h"
#include "Minheap.h"
#include "B_Tree.h"
#include <windows.h>
//#include "..\common\Win32specific.h"
//#include "..\common\thread_test.h"
//
//#include "CryThreadImpl_windows.h"

template<typename T>
void move(typename T && t);


template<typename T>
struct Node
{
	Node()
	{
		pNext = NULL;
	}
	T data;
	Node* pNext;
};

class NodeList
{
public:
	NodeList()
	{
		pHead = pTail = NULL;
	}

	~NodeList()
	{
		Node<int> *pCurr = pHead;
		while (pCurr)
		{
			Node<int> *pTemp = pCurr;
			pCurr = pCurr->pNext;
			delete pTemp;
		}
	}

	bool InsertSort(Node<int>* pNode)
	{
		//空链表
		if (pHead == NULL)
		{
			pHead = pTail = pNode;
			return true;
		}
		//查找插入位置
		Node<int>* pCurr = pHead;
		//插入头结点之前
		if (pCurr->data > pNode->data)
		{
			pNode->pNext = pCurr;
			pHead = pNode;
			return true;
		}
		else
		{
			while (pCurr != pTail)
			{
				if (pCurr->pNext != NULL)
				{
					if (pCurr->data <= pNode->data && pCurr->pNext->data > pNode->data)
					{
						break;
					}
				}
				pCurr = pCurr->pNext;
			}
			//插入到尾节点之后
			if (pCurr == pTail)
			{
				pCurr->pNext = pNode;
				pTail = pNode;
			}
			//插到中间
			else
			{
				pNode->pNext = pCurr->pNext;
				pCurr->pNext = pNode;
			}
		}
		return true;
	}
	Node<int>* pHead;
	Node<int>* pTail;

};

template<typename ELEMENT>
struct Link
{
	Link<ELEMENT>* m_pPrev;
	Link<ELEMENT>* m_pNext;
	ELEMENT* m_pElem;
};

class SomeElement
{
public:
	Link<SomeElement> m_link;
};

template<typename ELEMENT>
struct Link1
{
	Link1<ELEMENT>* m_pPrev;
	Link1<ELEMENT>* m_pNext;
};

class SomeElement1 : public Link1<SomeElement1>
{

};

//插入排序
void insert_sort(int array[], int n)
{
	for (int i = 1; i < n; ++i)
	{
		int temp = array[i];
		int j = i - 1;
		for (; j >= 0; --j)
		{
			if (array[j] > temp)
			{
				array[j + 1] = array[j];
			}
			else
				break;
		}
		array[j + 1] = temp;
	}
}

//归并
void merge(int array[], int left, int mid, int right, int array_help[])
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
			array_help[k++] = array[i++];
		else
			array_help[k++] = array[j++];
	}
	while (i <= mid)
	{
		array_help[k++] = array[i++];
	}
	while (j <= right)
	{
		array_help[k++] = array[j++];
	}

	for (int m = 0; m < right - left + 1; ++m)
	{
		array[left + m] = array_help[m];
	}
}
//归并排序
void merge_sort(int array[], int left, int right, int array_help[])
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		merge_sort(array, left, mid, array_help);
		merge_sort(array, mid + 1, right, array_help);
		merge(array, left, mid, right, array_help);
	}
}

//最大子数组
struct subarray
{
	int low;
	int high;
	int sum;
	subarray(int _low, int _high, int _sum)
		: low(_low), high(_high), sum(_sum)
	{

	}
};

subarray find_cross_maxsubarray(int array[], int low, int mid, int high)
{
	int left_maxsum = array[mid];
	int sum = left_maxsum;
	int left_max_low = mid;
	for (int i = mid - 1; i >= low; i--)
	{
		sum += array[i];
		if (sum > left_maxsum)
		{
			left_maxsum = sum;
			left_max_low = i;
		}
	}

	int right_maxsum = array[mid + 1];
	int right_max_high = mid + 1;
	sum = right_maxsum;
	for (int k = mid + 2; k <= high; k++)
	{
		sum += array[k];
		if (sum > right_maxsum)
		{
			right_maxsum = sum;
			right_max_high = k;
		}
	}

	return subarray(left_max_low, right_max_high, left_maxsum + right_maxsum);
}

subarray find_max_subarray(int array[], int low, int high)
{
	if (low == high)
	{
		return subarray(low, low, array[low]);
	}
	else
	{
		int mid = (low + high) / 2;
		subarray left_array = find_max_subarray(array, low, mid);
		subarray right_array = find_max_subarray(array, mid + 1, high);
		subarray cross_array = find_cross_maxsubarray(array, low, mid, high);
		if (left_array.sum >= right_array.sum && left_array.sum >= cross_array.sum)
			return left_array;
		else if (right_array.sum >= left_array.sum && right_array.sum >= cross_array.sum)
			return right_array;
		else
			return cross_array;
	}
}

//Strassen矩阵乘法
void ADD(int **A, int **B, int **Result, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Result[i][j] = A[i][j] + B[i][j];
		}
	}
}

void SUB(int **A, int **B, int **Result, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Result[i][j] = A[i][j] - B[i][j];
		}
	}
}


int MUL(int** A, int** B, int** Result, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Result[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				Result[i][j] = Result[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	return 0;
}


void FillMatrix(int** A, int** B, int n)
{
	for (int row = 0; row < n; row++)
	{
		for (int column = 0; column < n; column++)
		{

			A[row][column] = (B[row][column] = rand() % 5);
			//matrix2[row][column] = rand() % 2;//ba hazfe in khat 50% afzayeshe soorat khahim dasht
		}

	}
}


void PrintMatrix(int **A, int n)
{
	std::cout << std::endl;
	for (int row = 0; row < n; row++)
	{
		for (int column = 0; column < n; column++)
		{


			cout << A[row][column] << "\t";
			if ((column + 1) % ((n)) == 0)
				cout << endl;
		}

	}
	cout << endl;
}


void Strassen(int **A, int **B, int **C, int n)
{
	if (n == 1)
		C[0][0] = A[0][0] * B[0][0];
	else
	{
		int rowsize = n / 2;
		int **A11 = new int*[rowsize];
		int **A12 = new int*[rowsize];
		int **A21 = new int*[rowsize];
		int **A22 = new int*[rowsize];

		int **B11 = new int*[rowsize];
		int **B12 = new int*[rowsize];
		int **B21 = new int*[rowsize];
		int **B22 = new int*[rowsize];

		int **C11 = new int*[rowsize];
		int **C12 = new int*[rowsize];
		int **C21 = new int*[rowsize];
		int **C22 = new int*[rowsize];

		int **P1 = new int*[rowsize];
		int **P2 = new int*[rowsize];
		int **P3 = new int*[rowsize];
		int **P4 = new int*[rowsize];
		int **P5 = new int*[rowsize];
		int **P6 = new int*[rowsize];
		int **P7 = new int*[rowsize];

		int **Result1 = new int*[rowsize];
		int **Result2 = new int*[rowsize];

		for (int i = 0; i < rowsize; i++)
		{
			A11[i] = new int[rowsize];
			A12[i] = new int[rowsize];
			A21[i] = new int[rowsize];
			A22[i] = new int[rowsize];

			B11[i] = new int[rowsize];
			B12[i] = new int[rowsize];
			B21[i] = new int[rowsize];
			B22[i] = new int[rowsize];

			C11[i] = new int[rowsize];
			C12[i] = new int[rowsize];
			C21[i] = new int[rowsize];
			C22[i] = new int[rowsize];

			P1[i] = new int[rowsize];
			P2[i] = new int[rowsize];
			P3[i] = new int[rowsize];
			P4[i] = new int[rowsize];
			P5[i] = new int[rowsize];
			P6[i] = new int[rowsize];
			P7[i] = new int[rowsize];

			Result1[i] = new int[rowsize];
			Result2[i] = new int[rowsize];
		}

		for (int i = 0; i < rowsize; i++)
		{
			for (int j = 0; j < rowsize; j++)
			{
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + rowsize];
				A21[i][j] = A[i + rowsize][j];
				A22[i][j] = A[i + rowsize][j + rowsize];


				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + rowsize];
				B21[i][j] = B[i + rowsize][j];
				B22[i][j] = B[i + rowsize][j + rowsize];

			}
		}
		//P1 = A11 * (B12 - B22)
		SUB(B12, B22, Result1, rowsize);
		Strassen(A11, Result1, P1, rowsize);
		//P2 = (A11 + A12) * B22
		ADD(A11, A12, Result1, rowsize);
		Strassen(Result1, B22, P2, rowsize);
		//P3 = (A21 + A22) * B11
		ADD(A21, A22, Result1, rowsize);
		Strassen(Result1, B11, P3, rowsize);
		//P4 = A22 * (B21 - B11)
		SUB(B21, B11, Result1, rowsize);
		Strassen(A22, Result1, P4, rowsize);
		//P5 = (A11 + A22) * (B11 + B22)
		ADD(A11, A22, Result1, rowsize);
		ADD(B11, B22, Result2, rowsize);
		Strassen(Result1, Result2, P5, rowsize);
		//P6 = (A12 - A22) * (B21 + B22)
		SUB(A12, A22, Result1, rowsize);
		ADD(B21, B22, Result2, rowsize);
		Strassen(Result1, Result2, P6, rowsize);
		//P7 = (A11 - A21) * (B11 + B12)
		SUB(A11, A21, Result1, rowsize);
		ADD(B11, B12, Result2, rowsize);
		Strassen(Result1, Result2, P7, rowsize);


		//C11 = P5 + P4 - P2 + P6
		ADD(P5, P4, Result1, rowsize);
		SUB(P6, P2, Result2, rowsize);
		ADD(Result1, Result2, C11, rowsize);
		//C12 = P1 + P2
		ADD(P1, P2, C12, rowsize);
		//C21 = P3 + P4
		ADD(P3, P4, C21, rowsize);
		//C22 = P5 + P1 - P3 - P7
		ADD(P5, P1, Result1, rowsize);
		ADD(P3, P7, Result2, rowsize);
		SUB(Result1, Result2, C22, rowsize);

		for (int i = 0; i < rowsize; i++)
		{
			for (int j = 0; j < rowsize; j++)
			{
				C[i][j] = C11[i][j];
				C[i][j + rowsize] = C12[i][j];
				C[i + rowsize][j] = C21[i][j];
				C[i + rowsize][j + rowsize] = C22[i][j];
			}
		}

		for (int i = 0; i < rowsize; i++)
		{
			delete[] A11[i];
			delete[] A12[i];
			delete[] A21[i];
			delete[] A22[i];

			delete[] B11[i];
			delete[] B12[i];
			delete[] B21[i];
			delete[] B22[i];

			delete[] C11[i];
			delete[] C12[i];
			delete[] C21[i];
			delete[] C22[i];

			delete[] P1[i];
			delete[] P2[i];
			delete[] P3[i];
			delete[] P4[i];
			delete[] P5[i];
			delete[] P6[i];
			delete[] P7[i];

			delete[] Result1[i];
			delete[] Result2[i];
		}

		delete[] A11;
		delete[] A12;
		delete[] A21;
		delete[] A22;

		delete[] B11;
		delete[] B12;
		delete[] B21;
		delete[] B22;

		delete[] C11;
		delete[] C12;
		delete[] C21;
		delete[] C22;

		delete[] P1;
		delete[] P2;
		delete[] P3;
		delete[] P4;
		delete[] P5;
		delete[] P6;
		delete[] P7;

		delete[] Result1;
		delete[] Result2;

	}
}


class MyClass
{
public:
	MyClass()
	{}

	MyClass(int k)
	{

	}
};
//////////////////////////////////////////////////////////////////////////
//堆排序
void max_heap(int a[], int n, int i)
{
	int max_i = i;
	if (2 * i < n && a[2 * i] > a[max_i])
		max_i = 2 * i;
	if (2 * i + 1 < n && a[2 * i + 1] > a[max_i])
		max_i = 2 * i + 1;
	if (max_i != i)
	{
		int temp = a[i];
		a[i] = a[max_i];
		a[max_i] = temp;

		max_heap(a, n, max_i);
	}
}

void build_max_heap(int a[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		max_heap(a, n, i);
	}
}

void heap_sort(int a[], int n)
{
	build_max_heap(a, n);
	for (int i = n - 1; i > 0; i--)
	{
		int temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		max_heap(a, --n, 0);
	}
}
//堆实现最大优先队列
int heap_maxnum(int a[])
{
	return a[0];
}

void exchange(int& l, int& r)
{
	int temp = l;
	l = r;
	r = temp;
}

int heap_extract_max(int a[], int n)
{
	int max = a[0];
	//丢失原始堆数据
	//a[0] = a[n - 1];
	//保留堆数据
	exchange(a[0], a[n - 1]);
	max_heap(a, n - 1, 0);
	return max;
}

void maxheap_insert_key(int a[], int n, int key)
{
	a[n] = key;
	int i = n;
	while (i > 0 && a[i] > a[i / 2])
	{
		exchange(a[i], a[i / 2]);
		i = i / 2;
	}
}

//最小堆 最小优先队列
void min_heap(int a[], int n, int i)
{
	int min_i = i;
	if (2 * i < n && a[2 * i] < a[min_i])
		min_i = 2 * i;
	if (2 * i + 1 < n && a[2 * i + 1] < a[min_i])
		min_i = 2 * i + 1;
	if (min_i != i)
	{
		int temp = a[i];
		a[i] = a[min_i];
		a[min_i] = temp;

		min_heap(a, n, min_i);
	}
}

void build_min_heap(int a[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		min_heap(a, n, i);
	}
}

int heap_minnum(int a[])
{
	return a[0];
}

int heap_extract_min(int a[], int n)
{
	int min = a[0];
	//丢失原始堆数据
	//a[0] = a[n - 1];
	//保留堆数据
	exchange(a[0], a[n - 1]);
	min_heap(a, n - 1, 0);
	return min;
}

void minheap_insert_key(int a[], int n, int key)
{
	a[n] = key;
	int i = n;
	while (i > 0 && a[i] < a[i / 2])
	{
		exchange(a[i], a[i / 2]);
		i = i / 2;
	}
}
//////////////////////////////////////////////////////////////////////////
//快速排序
int partition(int a[], int p, int r)
{
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (a[j] <= a[r])
		{
			i++;
			exchange(a[i], a[j]);
		}
	}
	exchange(a[i + 1], a[r]);
	return i + 1;
}

void quicksort(int a[], int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}
//////////////////////////////////////////////////////////////////////////
//计数排序
void counting_sort(int* a, int* b, int n, int k)
{
	int* c = new int[k + 1];

	for (int i=0; i<=k; i++)
	{
		c[i] = 0;
	}

	for (int i=0; i<n; i++)
	{
		c[a[i]]++;
	}

	for (int i=1; i<=k; i++)
	{
		c[i] += c[i - 1];
	}

	for (int i=n-1; i>=0; i--)
	{
		//c[a[i]]累计数量
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}
	delete[] c;
}

//////////////////////////////////////////////////////////////////////////
//基数排序
void counting_sort_digit(int a[], int n, int exp)
{
	int c[10];
	for (int i = 0; i < 10; i++)
	{
		c[i] = 0;
	}

	int* b = new int[n];


	for (int i = 0; i < n; i++)
	{
		c[(a[i] / exp) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		c[i] += c[i - 1];
	}

	for (int i = n-1; i>=0; i--)
	{
		b[c[(a[i] / exp) % 10] - 1] = a[i];
		c[(a[i] / exp) % 10]--;
	}

	for (int i = n - 1; i >= 0; i--)
	{
		a[i] = b[i];
	}
	delete[] b;
}

void radix_sort(int a[], int n)
{
	int max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	for (int exp = 1; max / exp > 0; exp *= 10)
	{
		counting_sort_digit(a, n, exp);
	}
}
//////////////////////////////////////////////////////////////////////////
//桶排序
int putin(int num, int max)
{
	int put = 0;
	for (int i = 0; i < 10; i++)
	{
		if (num > (max * i) / 10 && num <= (max*(i + 1)) / 10)
		{
			put = i;
			break;
		}
	}
	return put;
}

void insert_sort(vector<int>& v)
{
	for (int i=1; i<v.size(); i++)
	{
		int temp = v[i];
		int j = i - 1;
		while (j >= 0 && v[j] > temp)
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = temp;
	}
}

void bucket_sort(int a[], int n)
{
	int max = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	vector<vector<int> > vbucket;
	vbucket.resize(10);
	for (int i = 0; i < n; i++)
	{
		vbucket[putin(a[i], max)].push_back(a[i]);
	}
	for (int i = 0; i < vbucket.size(); i++)
	{
		insert_sort(vbucket[i]);
	}

	int num = 0;
	for (int i = 0; i < vbucket.size(); i++)
	{
		for (int j = 0; j < vbucket[i].size(); j++)
		{
			a[num++] = vbucket[i][j];
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//选择算法(查找第i小的元素)
int rand_partition(int a[], int p, int r)
{
	int i = p + rand() % (r - p + 1);
	exchange(a[i], a[r]);
	return partition(a, p, r);
}


int rand_select(int a[], int p, int r, int i)
{
	if (p == r)
		return a[p];
	int q = rand_partition(a, p, r);
	int k = q - p + 1;
	if (k == i)
		return a[q];
	else if (i < k)
		return rand_select(a, p, q - 1, i);
	else
		return rand_select(a, q + 1, r, i - k);
}
//查找最大最小值
void get_min_max(int a[], int& min, int& max, int n)
{
	assert(n > 0);
	int i = 0;
	if (n % 2 == 0)
	{
		min = a[i];
		max = a[++i];
	}
	else
	{
		min = max = a[i];
	}

	for (int j = i + 1; j < n - 1; j++)
	{
		int curr_min;
		int curr_max;
		if (a[j] <= a[j + 1])
		{
			curr_min = a[j];
			curr_max = a[j + 1];
		}
		else
		{
			curr_min = a[j + 1];
			curr_max = a[j];
		}
		if (curr_min < min)
			min = curr_min;
		if (curr_max > max)
			max = curr_max;
	}
}

//////////////////////////////////////////////////////////////////////////
//最坏情况为线性时间的算法
int Partition_Mid(int a[], int p, int r, int data);
int Find_Mid(int a[], int p, int r);

int Select(int a[], int p, int r, int i)
{
	if (p == r)
		return a[p];
	int mid = Find_Mid(a, p, r);
	int q = Partition_Mid(a, p, r, mid);
	int k = q - p + 1;
	if (k == i)
		return a[q];
	else if (i < k)
		return Select(a, p, q - 1, i);
	else
		return Select(a, q + 1, r, i - k);
}

int Partition_Mid(int a[], int p, int r, int data)
{
	int len = r - p + 1;
	for (int i=0; i<len; i++)
	{
		if (a[i] == data)
		{
			exchange(a[i], a[r]);
			break;
		}
	}
	int i = p - 1;
	for (int j=p; j<r; j++)
	{
		if (a[j] <= a[r])
		{
			i++;
			exchange(a[i], a[j]);
		}
	}
	exchange(a[i + 1], a[r]);
	return i + 1;
}

int Insert_Mid(int a[], int p, int r)
{
	int len = r - p + 1;
	for (int i=p+1; i<=r; i++)
	{
		int temp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > temp)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
	return a[len / 2];
}

int Find_Mid(int a[], int p, int r)
{
	int len = r - p + 1;
	int *pMid = new int[len / 5 + 1];
	int j = 0;
	int start, end;
	for (int i = 0; i < len; i++)
	{
		if (i % 5 == 0)
			start = i + p;
		if ((i + 1) % 5 == 0 || i == len - 1)
		{
			end = i + p;
			j++;
			pMid[j - 1] = Insert_Mid(a, start, end);
		}			
	}
	int result = Select(pMid, 0, j - 1, (j - 1) / 2);
	delete pMid;
	return result;
}

//////////////////////////////////////////////////////////////////////////
//数据结构
//栈和队列
#define MAX 8

//栈
struct Stack
{
	int top;
	int array[MAX];
};

bool IsEmpty(Stack* s)
{
	if (s->top == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Push(Stack *s, int x)
{
	if (s->top + 1 == MAX)
	{
		cout << "Stack overflow" << endl;
		return;
	}
	else
	{
		s->top++;
		s->array[s->top] = x;
	}
}

int Pop(Stack* s)
{
	if (IsEmpty(s))
	{
		cout << "Stack underflow" << endl;
		return -9999;
	}
	else
	{
		int x = s->array[s->top];
		s->top--;
		return x;
	}
}
//双向链表
#define List_nil_Node//哨兵节点

struct ListNode
{
	int key;
	ListNode* prev;
	ListNode* next;
	ListNode(int _key)
	{
		key = _key;
		prev = next = NULL;
	}
};

struct List
{
	List()
	{
#ifdef List_nil_Node
		nil = new ListNode(-1);
		nil->next = nil->prev = nil;
#else
		head = NULL;
#endif
	}
	~List()
	{
		delete nil;
	}
#ifdef List_nil_Node
	ListNode* nil;
#else
	ListNode* head;
#endif
};

ListNode* List_Search(List* l, int key)
{
#ifdef List_nil_Node
	ListNode* curr = l->nil->next;
	while (curr != l->nil && curr->key != key)
	{
		curr = curr->next;
	}
	return curr;
#else
	ListNode* curr = l->head;
	while (curr != NULL && curr->key != key)
	{
		curr = curr->next;
	}
	return curr;
#endif
}


void List_Insert(List* l, ListNode* x)
{
#ifdef List_nil_Node
	//插入到哨兵节点之后
	x->next = l->nil->next;
	l->nil->next->prev = x;
	l->nil->next = x;
	x->prev = l->nil;
#else
	x->next = l->head;
	if (l->head != NULL)
	{
		l->head->prev = x;
	}
	l->head = x;
	x->prev = NULL;
#endif
}

void List_Delete(List* l, ListNode* x)
{
#ifdef List_nil_Node
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
#else
	if (x->prev != NULL)
		x->prev->next = x->next;
	else
		l->head = x->next;
	if (x->next != NULL)
		x->next->prev = x->prev;
	delete x;
#endif

}

//队列，队列满时，队列尾没有元素
struct Queue
{
	int head;
	int tail;
	int array[MAX];
};

void EnQueue(Queue* Q, int x)
{
	if (Q->head == (Q->tail + 1) % MAX)//队尾加，队头减
	{
		cout << "Queue overflow" << endl;
		return;
	}
	Q->array[Q->tail] = x;             //队列尾无元素
	Q->tail = (Q->tail + 1) % MAX;
}

int DeQueue(Queue* Q)
{
	if (Q->head == Q->tail)
	{
		cout << "Queue underflow" << endl;
		return -9999;
	}
	int x = Q->array[Q->head];
	Q->head = (Q->head + 1) % MAX;
	return x;
}

//////////////////////////////////////////////////////////////////////////
//散列表
//链表法解决hash冲突
struct Hash_ListNode
{
	Hash_ListNode()
	{
		prev = NULL;
		next = NULL;
	}
	int key;
	Hash_ListNode* prev;
	Hash_ListNode* next;
	//表头总是有效
	static Hash_ListNode* Search(Hash_ListNode* hln, int key)
	{
		Hash_ListNode* pNode = hln->next;
		while (pNode != NULL && pNode->key != key)
		{
			pNode = pNode->next;
		}
		return pNode;
	}
	static void Insert(Hash_ListNode* hln, int key)
	{
		Hash_ListNode* pNode = new Hash_ListNode;
		pNode->key = key;
		if (hln->next != NULL)
		{
			hln->next->prev = pNode;
			pNode->next = hln->next;
		}
		hln->next = pNode;
		pNode->prev = hln;
	}
	static void Delete(Hash_ListNode* hln, int key)
	{
		Hash_ListNode* pNode = Search(hln, key);
		if (pNode != NULL)
		{
			pNode->prev->next = pNode->next;
			if (pNode->next != NULL)
			{
				pNode->next->prev = pNode->prev;
			}
			delete pNode;
		}
	}
};

int Hash_Func(int n)
{
	return n % MAX;
}

struct Hash_table
{
	Hash_ListNode* hash_List[MAX];
	Hash_table()
	{
		for (int i=0; i<MAX; i++)
		{
			hash_List[i] = new Hash_ListNode;
		}
	}
	~Hash_table()
	{
		for (int i=0; i<MAX; i++)
		{
			delete hash_List[i];
		}
	}
};

Hash_ListNode* Hash_table_Search(Hash_table* ht, int key)
{
	return Hash_ListNode::Search(ht->hash_List[Hash_Func(key)], key);
}

void Hash_table_Insert(Hash_table* ht, int key)
{
	Hash_ListNode::Insert(ht->hash_List[Hash_Func(key)], key);
}

void Hash_table_Delete(Hash_table* ht, int key)
{
	Hash_ListNode::Delete(ht->hash_List[Hash_Func(key)], key);
}

void Print_Hash_table(Hash_table* ht)
{
	for (int i=0; i<MAX; i++)
	{
		Hash_ListNode* pNode = ht->hash_List[i]->next;
		cout << "Hash_List " << i << " ";
		while (pNode != NULL)
		{
			cout << pNode->key << " ";
			pNode = pNode->next;
		}
		cout << endl;
	}
}
//完全散列(perfect hashing)
//完全散列将关键字通过一级散列函数h1和二级散列函数h2后映射到二级散列中，其中，关键字个数等于桶数(n = m)，二级散列的大小N(T[i])为关键字个数的平方，用以保证完全O(n)的存储空间，以及O(1)的访问效率。但实际上，不可能真正地完全实现无冲突。

int *T[MAX] = {0,};
#define P 101

struct stRandFunc 
{
	stRandFunc(int _m, int _a, int _b)
		:m(_m), a(_a), b(_b)
	{

	}
	int m;
	int a;
	int b;
	int Hashing(int k)
	{
		return ((a * k + b) % P) % m;
	}
};

stRandFunc Create_Random_Hash_Func(int m)
{
	int a = rand() % (P - 1) + 1;
	int b = rand() % P;
	return stRandFunc(m, a, b);
}

void Init_Perfect_Hash_table(stRandFunc& srf, int keys[], int num)
{
	int Count[MAX];
	memset(Count, 0, MAX * sizeof(int));
	for (int i = 0; i < num; i++)
	{
		Count[srf.Hashing(keys[i])]++;
	}
	for (int i=0; i<MAX; i++)
	{
		if (Count[i] == 1)
		{
			T[i] = new int[sizeof(stRandFunc) / sizeof(int) + 1];
			(*T[i]) = 1;
			*(T[i] + 1) = 0;
			*(T[i] + 2) = 0;
			*(T[i] + 3) = 0;
		}
		else if (Count[i] > 1)
		{
			stRandFunc T_srf = Create_Random_Hash_Func(Count[i] * Count[i]);
			T[i] = new int[sizeof(stRandFunc) / sizeof(int) + Count[i] * Count[i]];
			memset(T[i], 0, (sizeof(stRandFunc) / sizeof(int) + Count[i] * Count[i]) * sizeof(int));
			memcpy(T[i], &T_srf, sizeof(stRandFunc));
		}
	}
}

void DestroyHash_table()
{
	for (int i=0; i<MAX; i++)
	{
		delete[] T[i];
	}
}

void Perfect_Hash_table_Insert(stRandFunc& srf, int keys[], int num)
{
	for (int i = 0; i < num; i++)
	{
		int n = srf.Hashing(keys[i]);
		stRandFunc T_srf(*T[n], *(T[n] + 1), *(T[n] + 2));
		int j = T_srf.Hashing(keys[i]);
		
		if (*(T[n] + 3 + j) != 0)
		{
			cout << *(T[n] + 3 + j) << " and " << keys[i] << " m,a,b " << T_srf.m << " " << T_srf.a << " " << T_srf.b << " " << "hash collision" << endl;
			continue;
		}
		*(T[n] + 3 + j) = keys[i];
	}
}

int Perfect_Hash_table_Search(stRandFunc& srf, int key)
{
	int n = srf.Hashing(key);
	stRandFunc T_srf(*T[n], *(T[n] + 1), *(T[n] + 2));
	int j = T_srf.Hashing(key);
	if (T[n] == NULL)
		return -1;
	else
		return *(T[n] + 3 + j);
}


void print_hash_table(int* T[])
{
	int i = 0, j = 0;
	printf("*********************************\n");
	printf("The hash table is:\n");
	for (i = 0; i < MAX; i++)
	{
		if (!T[i])
		{
			printf("slot%-2d: NUL\n", i);
		}
		else
		{
			printf("slot%-2d: m=%-4da=%-4db=%-4dVALUE:", i, *T[i], *(T[i] + 1), *(T[i] + 2));
			for (j = 0; j < *T[i]; j++)
			{
				printf("<%-4d>", *(T[i] + 3 + j));
			}
			printf("\n");
		}
	}
	printf("\n\n");
}
//////////////////////////////////////////////////////////////////////////
//动态规划

//钢条切割问题
int CUT_ROD(int p[], int n)
{
	if (n == 0)
		return 0;
	int q = -1;
	for (int i=1; i<=n; i++)
	{
		q = std::max(q, p[i] + CUT_ROD(p, n - i));
	}
	return q;
}

int MEMOIZED_CUT_ROD_AUX(int p[], int n, int r[])
{
	if (r[n] >= 0)
		return r[n];
	int q = -1;
	if (n == 0)
		q = 0;
	else
	{ 
		for (int i = 1; i <= n; i++)
		{
			q = std::max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i, r));
		}
	}
	r[n] = q;
	return q;
}

int MEMOIZED_CUT_ROD(int p[], int n)
{
	int *r = new int[n + 1];
	for (int i=0; i<=n; i++)
	{
		r[i] = -1;
	}
	int q = MEMOIZED_CUT_ROD_AUX(p, n, r);
	delete[] r;
	return q;
}

int BOTTOM_UP_ROD(int p[], int n)
{
	int *r = new int[n + 1];
	r[0] = 0;
	for (int i=1; i<=n; i++)
	{
		int q = -1;
		for (int j=1; j<=i; j++)
		{
			q = std::max(q, p[j] + r[i - j]);
		}
		r[i] = q;
	}
	int result = r[n];
	delete[] r;
	return result;
}

#define LEN 11
//test
int Bottom_Up_Cut_Rod(int p[], int n)
{
	int r[LEN] = { 0 };
	int temp = 0;
	int i, j;
	for (j = 1; j <= n; j++)
	{
		temp = 0;
		for (i = 1; i <= j; i++)
		{
			temp = (temp >= r[i] + r[j - i]) ? temp : (r[i] + r[j - i]);
			//temp = (temp >= p[i] + r[j - i]) ? temp : (p[i] + r[j - i]);
		}
		r[j] = (temp > p[j]) ? temp : p[j];
		//r[j] = temp;
	}
	return r[n];
}
//////////////////////////////////////////////////////////////////////////
//重构解 切割方案
struct CUT_SOLUTION
{
	int* r;
	int* s;
	CUT_SOLUTION(int n)
	{
		r = new int[n + 1];
		s = new int[n + 1];
	}
	~CUT_SOLUTION()
	{
		delete[] r;
		delete[] s;
	}
};

void EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int n, CUT_SOLUTION& cs)
{
	cs.r[0] = 0;
	for (int j = 1; j <= n; j++)
	{
		int q = -1;
		for (int i=1; i<=j; i++)
		{
			if (q < p[i] + cs.r[j - i])
			{
				q = p[i] + cs.r[j - i];
				cs.s[j] = i;
			}
		}
		cs.r[j] = q;
	}
}

void PRINT_EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int n)
{
	CUT_SOLUTION cs(n);
	EXTENDED_BOTTOM_UP_CUT_ROD(p, n, cs);
	while (n > 0)
	{
		cout << cs.s[n] << endl;
		n -= cs.s[n];
	}
}
//////////////////////////////////////////////////////////////////////////
struct stIndex
{
	int i;
	int j;
	stIndex(int _i, int _j)
		: i(_i), j(_j)
	{

	}
	bool operator== (const stIndex& si) const
	{
		return i == si.i && j == si.j;
	}
};

template <>
struct hash<stIndex>
{
	size_t operator()(const stIndex &si) const
	{
		return (si.i << 3) + si.j;
	}
};

//矩阵链乘法
struct PARENS_SOLUTION
{
	unordered_map<stIndex, int> m;
	unordered_map<stIndex, int> s;
};

void MATRIX_CHAIN_ORDER(int p[], int psize, PARENS_SOLUTION& ps)
{
	int n = psize - 1;
	//要用到p[0],所以会多出一些内存.m[0..][...0]无效
	for (int i=1; i<=n; i++)
	{
		stIndex si(i, i);
		ps.m[si] = 0;
	}

	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			stIndex si(i, j);
			ps.m[si] = 999999;
			for (int k = i; k <= j - 1; k++)
			{
				int q = ps.m[stIndex(i, k)] + ps.m[stIndex(k + 1, j)] + p[i - 1] * p[k] * p[j];
				if (q < ps.m[stIndex(i, j)])
				{
					stIndex si(i, j);
					ps.m[si] = q;
					ps.s[si] = k;
				}
			}
		}
	}
}

void PRINT_OPTIMAL_PARENS(PARENS_SOLUTION& ps, int i, int j)
{
	if (i == j)
		cout << "A" << i;
	else
	{
		cout << "(";
		PRINT_OPTIMAL_PARENS(ps, i, ps.s[stIndex(i, j)]);
		PRINT_OPTIMAL_PARENS(ps, ps.s[stIndex(i, j)] + 1, j);
		cout << ")";
	}
}
//////////////////////////////////////////////////////////////////////////
//最长公共子序列
struct LCS_SOLUTION
{
	int **c;
	string **b;
	int m, n;
	LCS_SOLUTION(int _m, int _n) : m(_m), n(_n)
	{
		c = new int*[m + 1];
		b = new string*[m + 1];
		for (int i = 0; i <= m; i++)
		{
			c[i] = new int[n + 1];
			b[i] = new string[n + 1];
		}
	}
	~LCS_SOLUTION()
	{
		for (int i = 0; i <= m; i++)
		{
			delete[] c[i];
			delete[] b[i];
		}
		delete[] c;
		delete[] b;
	}
};

void LCS_LENGTH(string& X, string& Y, LCS_SOLUTION& LCS)
{
	int m = X.length();
	int n = Y.length();
	for (int i = 1; i <= m; i++)
	{
		LCS.c[i][0] = 0;
	}
	for (int j = 0; j <= n; j++)
	{
		LCS.c[0][j] = 0;
	}

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			//X,Y的索引从0开始
			if (X[i-1] == Y[j-1])
			{
				LCS.c[i][j] = LCS.c[i - 1][j - 1] + 1;
				LCS.b[i][j] = "↖";
			} 
			else if (LCS.c[i - 1][j] >= LCS.c[i][j - 1])
			{
				LCS.c[i][j] = LCS.c[i - 1][j];
				LCS.b[i][j] = "↑";
			}
			else
			{
				LCS.c[i][j] = LCS.c[i][j - 1];
				LCS.b[i][j] = "←";
			}
		}
	}
}

void PRINT_LCS(LCS_SOLUTION& LCS, string& X, int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (LCS.b[i][j] == "↖")
	{
		PRINT_LCS(LCS, X, i - 1, j - 1);
		//X,Y的索引从0开始
		cout << X[i-1];
	}
	else if (LCS.b[i][j] == "↑")
	{
		PRINT_LCS(LCS, X, i - 1, j);
	}
	else
	{
		PRINT_LCS(LCS, X, i, j - 1);
	}
}

//////////////////////////////////////////////////////////////////////////
//最优二叉搜索树
struct O_BST_Index
{
	int i;
	int j;

	bool operator== (const O_BST_Index& bi) const
	{
		return i == bi.i && j == bi.j;
	}
	O_BST_Index(int _i, int _j) : i(_i), j(_j)
	{

	}
};

template <>
struct hash<O_BST_Index>
{
	size_t operator()(const O_BST_Index &si) const
	{
		//long hash = 5381;
		//hash = ((hash << 5) + hash) + si.i;
		//hash = ((hash << 5) + hash) + si.j;
		//return hash;
		return si.i * 1000 + si.j;
	}
};

struct OPT_BST_SOLUTION
{
	unordered_map<O_BST_Index, float> e;
	unordered_map<O_BST_Index, float> w;
	unordered_map<O_BST_Index, int> root;
};
//////////////////////////////////////////////////////////////////////////
//贪心算法
//活动选择问题
void Recursive_Activity_Selector(int s[], int f[], int k, int n, vector<int>& va)
{
	int m = k + 1;
	while (m <= n && s[m] < f[k])
	{
		m++;
	}
	if (m <= n)
	{
		va.push_back(m);
		Recursive_Activity_Selector(s, f, m, n, va);
	}
}

void Greedy_Activity_Selector(int s[], int f[], int n, vector<int> &va)
{
	va.push_back(1);
	int k = 1;
	for (int m = 2; m <= n; m++)
	{
		if (s[m] >= f[k])
		{
			va.push_back(m);
			k = m;
		}
	}
}

void OPTIMAL_BST(float p[], float q[], int n, OPT_BST_SOLUTION& obs)
{
	for (int i=1; i<=n+1; i++)
	{
		obs.e[O_BST_Index(i, i - 1)] = q[i - 1];
		obs.w[O_BST_Index(i, i - 1)] = q[i - 1];
	}
	for (int l = 1; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			obs.e[O_BST_Index(i, j)] = 0x0fffffff;
			obs.w[O_BST_Index(i, j)] = obs.w[O_BST_Index(i, j - 1)] + p[j] + q[j];
			for (int r = i; r <= j; r++)
			{
				float t = obs.e[O_BST_Index(i, r - 1)] + obs.e[O_BST_Index(r + 1, j)] + obs.w[O_BST_Index(i, j)];
				if (t < obs.e[O_BST_Index(i, j)])
				{
					obs.e[O_BST_Index(i, j)] = t;
					obs.root[O_BST_Index(i, j)] = r;
				}
			}
		}
	}
}
//哈夫曼编码
template<class T>
HaffmanNode<T>* Huffman(int code[], int n, Minheap<HaffmanNode<T>*> & mn)
{
	for (int i = 0; i < n; i++)
	{
		HaffmanNode<T>* pNode = new HaffmanNode<T>;
		pNode->data = code[i];
		mn.minheap_insert_key(pNode);
	}

	for (int i = 0; i <= n - 2; i++)
	{
		HaffmanNode<T>* z = new HaffmanNode<T>;
		HaffmanNode<T>* x = mn.heap_extract_min();
		HaffmanNode<T>* y = mn.heap_extract_min();
		z->left = x;
		z->right = y;
		z->data = x->data + y->data;
		mn.minheap_insert_key(z);		
	}
	return mn.heap_extract_min();
}
//任务调度问题
struct task
{
	int id;
	int d;
	int w;
};

bool cmpW(task t1, task t2)
{
	return t1.w > t2.w;
}

bool cmpD(task t1, task t2)
{
	return t1.d < t2.d;
}

void greedy(task a[], task b[], task ta[], int n, int &ans, int& a_num, int & b_num)
{
	a_num = 0;
	b_num = 0;
	int j;
	sort(ta, ta + n, cmpW);
	int fla[9999];
	memset(fla, 0, sizeof(fla));
	for (int i = 0; i < n; i++)
	{
		for (j = ta[i].d; j > 0; j--)
		{
			if (fla[j] == 0)
			{
				fla[j] = 1;
				break;
			}
		}
		if (j > 0)
		{
			a[a_num++] = ta[i];
			ans -= ta[i].w;
		}
		else
		{
			b[b_num++] = ta[i];
		}
	}
}

//思路：
//
//根据题意，需要特判，对于空矩阵直接返回空数组。
//接下来：
//
//定义出二维数组的左右上下四个边界，left、right、top、bottom;
//循环打印：
//沿着top，从左向右打印，top++;
//沿着right, 从上向下打印，right--;
//沿着bottom，从右向左打印，bottom--；
//沿着left, 从下向上打印，left++;
//注：在沿着下边界和左边界打印时，要确保left <= right，top <= bottom。

class Solution {
public:
	//矩阵螺旋输出法，顺时针，左上角开始
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		//特判
		if (matrix.size() == 0) {
			return {};
		}

		//初始化
		int left = 0, top = 0;
		int bottom = matrix.size() - 1;
		int right = matrix[0].size() - 1;
		//int* res = new int[(right + 1) * (bottom + 1)];
		vector<int> order;
		order.resize((right + 1) * (bottom + 1));
		int k = 0;

		//循环打印
		while (top <= bottom && left <= right) {
			for (int i = left; i <= right; i++) { //从左到右
				order[k++] = matrix[top][i];
			}
			top++;
			for (int i = top; i <= bottom; i++) { //从上到下
				order[k++] = matrix[i][right];
			}
			right--;
			for (int i = right; i >= left && top <= bottom; i--) {    //从右到左
				order[k++] = matrix[bottom][i];
			}
			bottom--;
			for (int i = bottom; i >= top && left <= right; i--) {    //从下到上
				order[k++] = matrix[i][left];
			}
			left++;
		}
		return order;
	}
	//矩阵螺旋输出法，顺时针，右下角开始
	vector<int> spiralOrder_end(vector<vector<int>>& matrix) {
		//特判
		if (matrix.size() == 0) {
			return {};
		}

		//初始化
		int left = 0, top = 0;
		int bottom = matrix.size() - 1;
		int right = matrix[0].size() - 1;

		vector<int> order;
		order.resize((right + 1) * (bottom + 1));
		int k = 0;

		//循环打印
		while (top <= bottom && left <= right) {
			for (int i = right; i >= left; i--) {    //从右到左
				order[k++] = matrix[bottom][i];
			}
			bottom--;
			for (int i = bottom; i >= top; i--) {    //从下到上
				order[k++] = matrix[i][left];
			}
			left++;
			for (int i = left; i <= right; i++) { //从左到右
				order[k++] = matrix[top][i];
			}
			top++;
			for (int i = top; i <= bottom; i++) { //从上到下
				order[k++] = matrix[i][right];
			}
			right--;
		}
		return order;
	}
};

//c++11 std::move用法
class Person {
private:
	int* data;
public:
	Person() : data(new int[1000000]) {}
	~Person() { delete[] data; }

	Person(const Person& other) = delete;

	Person(Person&& other) : data(other.data) {
		other.data = nullptr;
	}

};

void func(Person p) {

};
//二分查找算法
int BinarySearch(int start, int end, int* a, int target)
{
	if (start > end) {
		return -100;
	}
	int mid = (start + end) / 2;
	if (a[mid] == target) {
		return mid;
	}
	else if (target < a[mid])
	{
		return BinarySearch(start, mid-1, a, target);
	}
	else
	{
		return BinarySearch(mid+1, end, a, target);
	}
}

void insert_sort_test(int* a, int size)
{
	for (int i = 1; i < size; ++i)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (a[j] > a[i])
			{
				int temp = a[j];
				a[j] = a[i];
				a[i] = temp;
				i = j;
			}
			else {
				break;
			}
		}
	}
}
//右下角开始螺旋遍历矩阵
void SpiralMatrix(vector<vector<int>>& matrix)
{
	int col = matrix.size();
	int row = matrix[0].size();
	int left = 0;
	int right = row - 1;
	int top = 0;
	int bottom = col - 1;
	while (left <= right && top <= bottom)
	{
		for (int i = right; i >= left; --i)
		{
			cout << matrix[bottom][i] << " ";
		}
		--bottom;
		for (int j = bottom; j >= top; --j)
		{
			cout << matrix[j][left] << " ";
		}
		++left;
		for (int k = left; k <= right; ++k)
		{
			cout << matrix[top][k] << " ";
		}
		++top;
		for (int l = top; l <= bottom; ++l)
		{
			cout << matrix[l][right] << " ";
		}
		--right;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	MyClass mc = MyClass();


	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag(tmpFlag);

	std::vector<int> binaryarray = { 1,3, 6, 9, 10, 12, 18 };
	int binaryarray_index = BinarySearch(0, binaryarray.size(), binaryarray.data(), 3);

	int array[] = { 0,3,4,5,7,9,8,3,2,4,9,0,3,9,5,8,0,3,8,9,5,3,5 };

	insert_sort_test(array, sizeof(array) / sizeof(int));

	//插入排序
	insert_sort(array, sizeof(array) / sizeof(int));

	//vector<vector<int>> testMatrix = { {0,1,2,3}, {4,5,6,7}, {8,9,10,11}, {12,13,14,15} };
	vector<vector<int>> testMatrix = { {0,1,2}, {5,6,7}, {8,9,10}, {12,13,14}, {17,18,19} };
	SpiralMatrix(testMatrix);

	//归并排序
	int merge_array[] = { 9, 0, 3, 5, 7, 9, 0, 5, 8, 9, 0, 2, 3, 4, 5, 0, 3, 7, 3, 9, 0, 1, 4, 0, 9, 1, 2, 3, 9, 0, 4, 0, 5, 8, 0, 2, 3, 4, 5, 8, 0, 3, 9, 4, 8, 5, 0 };
	int length = sizeof(merge_array) / sizeof(int);
	int* array_help = new int[length];
	merge_sort(merge_array, 0, length - 1, array_help);
	delete array_help;

	//最大子数组
	int max_subarray[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5 , -22, 15, -4, 7 };

	subarray sa = find_max_subarray(max_subarray, 0, sizeof(max_subarray) / sizeof(int));

	//////////////////////////////////////////////////////////////////////////
	int MatrixSize = 8;
	int N = MatrixSize;//for readiblity.


	int **A = new int *[MatrixSize];
	int **B = new int *[MatrixSize];
	int **C = new int *[MatrixSize];

	for (int i = 0; i < MatrixSize; i++)
	{
		A[i] = new int[MatrixSize];
		B[i] = new int[MatrixSize];
		C[i] = new int[MatrixSize];
	}

	FillMatrix(A, B, MatrixSize);

	PrintMatrix(C, MatrixSize);

	Strassen(A, B, C, N);

	PrintMatrix(C, MatrixSize);

	MUL(A, B, C, MatrixSize);

	PrintMatrix(C, MatrixSize);

	for (int i = 0; i < MatrixSize; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}

	delete[] A;
	delete[] B;
	delete[] C;

	//////////////////////////////////////////////////////////////////////////
	//堆排序
	int heap_array[] = { 8,9,3,47,9,8,57,2,9,35,7,9,234,62,0,3,9,4,2,37,49,2,3,59,2,3,5,7,9,2,3,7,9,2,390,5 };

	heap_sort(heap_array, sizeof(heap_array) / sizeof(int));
	//堆构建最大优先队列
	int* heap_array_max = new int[sizeof(heap_array) / sizeof(int) + 1];
	memcpy(heap_array_max, heap_array, sizeof(heap_array));
	build_max_heap(heap_array_max, sizeof(heap_array) / sizeof(int));
	cout << heap_maxnum(heap_array_max) << endl;
	//输出之后堆数据已经发生变化
	for (int i = sizeof(heap_array) / sizeof(int); i > 0; i--)
	{
		cout << heap_extract_max(heap_array_max, i) << " ";
	}
	cout << endl;
	build_max_heap(heap_array_max, sizeof(heap_array) / sizeof(int));
	maxheap_insert_key(heap_array_max, sizeof(heap_array) / sizeof(int), 400);

	for (int i = sizeof(heap_array) / sizeof(int) + 1; i > 0; i--)
	{
		cout << heap_extract_max(heap_array_max, i) << " ";
	}
	cout << endl;

	delete[] heap_array_max;

	int __1 = 16;
	int __2 = 14;
	int __3 = 10;
	int __4 = 8;
	int __5 = 7;
	int __6 = 9;
	int __7 = 3;
	int __8 = 2;
	int __9 = 4;
	int __10 = 1;
	int* minmap_array[] = { &__1, &__2, &__3, &__4, &__5, &__6, &__7, &__8, &__9, &__10 };
	Minheap<int*> mi(100, sizeof(minmap_array)/sizeof(int));
	mi.build_min_heap(minmap_array, sizeof(minmap_array) / sizeof(int));
	//////////////////////////////////////////////////////////////////////////
	//快速排序
	int quick_array[] = { 9,2,3,48,92,3,85,9,2,3,5,9,03,2,38,492,73,894,2,89,349,0,23,49,02,37,4,9,28,9,3,79,5,80,92,3,5,90,2,3,80,52 };

	quicksort(quick_array, 0, sizeof(quick_array) / sizeof(int) - 1);
	//////////////////////////////////////////////////////////////////////////
	//计数排序
	int count_array[] = { 24,87,90,79,02,3,859,5,95,9,5,84,9,58,1,9,03,4,8,0,3,4,9,80,239,48,2,3,9,48,02,3,98,4,0,23,4,7,982,3,74,9,0,23,78,4,90,28,73,49,0,827,3,49,02,37,84,90,28,34,79,24,83 };
	int* cout_array_b = new int[sizeof(count_array) / sizeof(int)];
	//int cout_array_b[] = { 24,87,90,79,02,3,859,5,95,9,5,84,9,58,1,9,03,4,8,0,3,4,9,80,239,48,2,3,9,48,02,3,98,4,0,23,4,7,982,3,74,9,0,23,78,4,90,28,73,49,0,827,3,49,02,37,84,90,28,34,79,24,83 };
	counting_sort(count_array, cout_array_b, sizeof(count_array) / sizeof(int), 1000);

	delete[] cout_array_b;
	//////////////////////////////////////////////////////////////////////////
	//基数排序
	int radix_sort_array[] = { 39,8,90,340,48,90,23,49,02,3,4,82,0,91,2,1,4,1,48,2,30,8,4,2,0,3,489,1,4,7,81,0,1,2,4,89,2,9,03,52 };
	//int* radix_sort_array_b = new int[sizeof(radix_sort_array) / sizeof(int)];
	//int radix_sort_array_b[] = { 39,8,90,340,48,90,23,49,02,3,4,82,0,91,2,1,4,1,48,2,30,8,4,2,0,3,489,1,4,7,81,0,1,2,4,89,2,9,03,52 };
	radix_sort(radix_sort_array, sizeof(radix_sort_array) / sizeof(int));
	//delete[] radix_sort_array_b;

	//////////////////////////////////////////////////////////////////////////
	//桶排序
	int bucket_sort_array[] = { 35,9,25,8,35,0,23,9,52,59,1,5,0,18,51,35,0,-1,59,1,69,13,4,69,35,81,358,8,905,130,5 };
	bucket_sort(bucket_sort_array, sizeof(bucket_sort_array) / sizeof(int));

	//选择算法
	int rand_select_array[] = { 9,81,4,791,79,0,57,1,9,0,23,57, 357,81,3,79,0,1,247,89,12,83,74,912,378,490,123,84,790,123,847,19,23,47,819,023,748,90,12,7,34,90,2 };
	//随机选择算法
	int order = rand_select(rand_select_array, 0, sizeof(rand_select_array) / sizeof(int) - 1, 22);

	int max, min;
	//获取最大值，最小值算法
	get_min_max(rand_select_array, min, max, sizeof(rand_select_array) / sizeof(int));
	//最坏情况时间复杂度为线性的算法
	int select_array[] = { 2,39,04,83,90,28,01,9,35,84,810,3,94,83,35,7,89,34,57,2,39,457,1,345,190,8,347,59,1,83,749,37,65,8,34,92,340,76,2,34,5,60,23,85,7,23,0,9,57,8 };
	order = Select(select_array, 0, sizeof(select_array) / sizeof(int) - 1, 31);
	bucket_sort(select_array, sizeof(select_array) / sizeof(int));
	
	//////////////////////////////////////////////////////////////////////////
	//栈和队列
	Stack* S = new Stack;
	S->top = -1;
	Pop(S);
	for (int i=0; i<=9; i++)
	{
		Push(S, i);
	}
	for (int i = 0; i <= 9; i++)
	{
		cout << Pop(S) << " ";
	}
	cout << endl;


	Queue* Q = new Queue;
	Q->head = Q->tail = 0;
	for (int i=0; i<=9; i++)
	{
		EnQueue(Q, i);
	}
	for (int i = 0; i <= 9; i++)
	{
		cout << DeQueue(Q) << " ";
	}
	cout << endl;
	delete S;
	delete Q;
	//////////////////////////////////////////////////////////////////////////
	//双向链表
	List *l = new List;
	for (int i=0; i<9; i++)
	{
		List_Insert(l, new ListNode(i));
	}

	ListNode* curr = NULL;
	for (int i=8; i>=0; i--)
	{
		curr = List_Search(l, i);
		cout << curr->key << " ";
	}
	cout << endl;

	for (int i = 0; i<9; i++)
	{
		List_Delete(l, List_Search(l, i));
	}
	delete l;
	//散列表
	//链表法解决hash冲突
	Hash_table* pHt = new Hash_table;
	int Hash_key_Array[] = { 38,4793,57,03,8,4,5,70,9,3,2,8,45,03,9,84,7,59,03,28,4,75,90,3,28,7,45,9,03,8,74,59 };
	for (int i = 0; i < sizeof(Hash_key_Array) / sizeof(int); i++)
	{
		Hash_table_Insert(pHt, Hash_key_Array[i]);
	}
	Print_Hash_table(pHt);
	for (int i= sizeof(Hash_key_Array) / sizeof(int) -1; i>=0; i--)
	{
		Hash_table_Delete(pHt, Hash_key_Array[i]);
	}
	delete pHt;
	//完全散列(perfect hashing)
	int Perfect_Hash_table_array[] = { 10, 22, 37, 40, 60, 70, 75, 85, 55, 19 };
	srand((unsigned int)(time(NULL)));
	stRandFunc srf = Create_Random_Hash_Func(MAX);
	Init_Perfect_Hash_table(srf, Perfect_Hash_table_array, sizeof(Perfect_Hash_table_array) / sizeof(int));
	print_hash_table(T);
	Perfect_Hash_table_Insert(srf, Perfect_Hash_table_array, sizeof(Perfect_Hash_table_array) / sizeof(int));
	print_hash_table(T);
	printf("The search 22's key is:%d\n", Perfect_Hash_table_Search(srf, 22));
	DestroyHash_table();
	//////////////////////////////////////////////////////////////////////////
	//二叉搜索树
	Tree* T = new Tree;
	int Tree_array[] = { 10,20,18,19,9,8,6,3,32,1 };

	for (int i = sizeof(Tree_array) / sizeof(int) - 1; i >= 0; i--)
	{
		TreeNode* pNode = new TreeNode;
		pNode->key = Tree_array[i];
		Tree_Insert(T, pNode);
	}

	TreeNode *s = Tree_Search(T->root, 3);
	if (s != NULL)
		printf("%d\n", s->key);
	Inorder_Tree_Walk(T->root);

	printf("\n");
	printf("%d\n", Tree_Minimum(T->root)->key);
	printf("%d\n", T->root->key);
	printf("%d\n", Tree_Maximum(T->root)->key);

	printf("%d\n", Tree_Successor(s)->key);
	printf("%d\n", Tree_Predecessor(s)->key);
	Tree_Delete(T, s);
	Inorder_Tree_Walk(T->root);
	printf("\n");
	free_mem(T->root);
	delete T;
	//////////////////////////////////////////////////////////////////////////
	//红黑树
	RB_Tree *RB_T = new RB_Tree;
	int RB_Tree_array[] = { 10,20,18,19,9,8,6,3,32,1,45,59,89 };
	for (int i = 0; i < sizeof(RB_Tree_array) / sizeof(int); i++) {
		RB_TreeNode* x = new RB_TreeNode();
		x->k = RB_Tree_array[i];
		x->color = RED;
		x->p = x->left = x->right = RB_T->nil;
		RB_Insert(RB_T, x);
		Inorder_RB_Tree_Walk(RB_T, RB_T->root);
		printf("\n");

	}
	RB_TreeNode *rb_s = RB_Search(RB_T, RB_T->root, 3);
	if (rb_s != RB_T->nil)
		printf("%d is exists!\n", rb_s->k);
	/*Inorder_RB_Tree_Walk(T->root);
			   64
			   65     printf("\n");*/
	printf("%d\n", RB_Tree_Minimum(RB_T, RB_T->root)->k);
	printf("%d\n", RB_Tree_Maximum(RB_T, RB_T->root)->k);
	printf("%d\n", RB_Tree_Successor(RB_T, rb_s)->k);
	printf("%d\n", RB_Tree_Predecesor(RB_T, rb_s)->k);
	RB_Delete(RB_T, rb_s);
	Inorder_RB_Tree_Walk(RB_T, RB_T->root);
	printf("\n");
	Free_Mem(RB_T, RB_T->root);
	delete RB_T;
	//////////////////////////////////////////////////////////////////////////
	//顺序树
	Order_Tree *Order_T = new Order_Tree;

	int Order_Tree_array[] = { 26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 21, 28, 38, 7, 12, 14, 20, 35, 39, 3 };

	for (int i = 0; i < sizeof(Order_Tree_array) / sizeof(int); i++) {
		Order_TreeNode* x = new Order_TreeNode();
		x->k = Order_Tree_array[i];
		x->color = RED;
		x->p = x->left = x->right = Order_T->nil;
		x->size = 1;
		RB_Insert(Order_T, x);
		Inorder_Order_Tree_Walk(Order_T, Order_T->root);
		printf("\n");

	}


	Order_TreeNode *order_s = RB_Search(Order_T, Order_T->root, 3);
	if (order_s != Order_T->nil)
		printf("%d is exists!\n", order_s->k);
	/*Inorder_RB_Tree_Walk(T->root);
	88
	89     printf("\n");*/

	printf("%d\n", OS_Select(Order_T->root, 3)->k);

	printf("%d\n", OS_Rank(Order_T, order_s));

	//printf("%d\n", RB_Tree_Minimum(T->root)->value);
	//printf("%d\n", RB_Tree_Maximum(T->root)->value);
	//printf("%d\n", RB_Tree_Successor(s)->value);
	//printf("%d\n", RB_Tree_Predecesor(s)->value);
	RB_Delete(Order_T, order_s);
	Inorder_Order_Tree_Walk(Order_T, Order_T->root);
	printf("\n");

	Free_Mem(Order_T, Order_T->root);

	delete Order_T;



	//////////////////////////////////////////////////////////////////////////
	//区间树
	Interval_Tree* Interval_T = new Interval_Tree;

	int Interval_Tree_Array[10][2] = { {16, 21}, {25, 30}, {17,19}, {26, 26}, {19 ,20}, {8,9}, {5,8}, {15,23}, {0,3}, {6, 10} };
	for (int i=0; i<10; i++)
	{
			Interval_TreeNode* x = new Interval_TreeNode;
			x->k = x->Int.low = Interval_Tree_Array[i][0];
			x->Int.high = Interval_Tree_Array[i][1];
			x->color = RED;
			x->p = x->left = x->right = Interval_T->nil;
			RB_Insert(Interval_T, x);
	}
	Inorder_Interval_Tree_Walk(Interval_T, Interval_T->root);
	Interval interval_i;
	interval_i.low = 22;
	interval_i.high = 25;

	Interval_TreeNode* x2 = Interval_Serach(Interval_T, interval_i);

	cout << "重叠区间：[" << x2->Int.low << " " << x2->Int.high << "]" << endl;

	Free_Mem(Interval_T, Interval_T->root);

	delete Interval_T;

	//钢条切割问题
	int Price_array[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	//朴素算法
	for (int i=1; i<=10; i++)
	{
		cout << "r " << i << " " << CUT_ROD(Price_array, i) << endl;
	}
	cout << endl;
	//备忘法
	for (int i = 1; i <= 10; i++)
	{
		cout << "r " << i << " " << MEMOIZED_CUT_ROD(Price_array, i) << endl;
	}
	cout << endl;
	//自底向上
	for (int i = 1; i <= 10; i++)
	{
		cout << "r " << i << " " << BOTTOM_UP_ROD(Price_array, i) << endl;
	}
	//自底向上测试
	for (int i = 1; i <= 10; i++)
	{
		cout << "r " << i << " " << Bottom_Up_Cut_Rod(Price_array, i) << endl;
	}

	//重构解 切割方案
	for (int i = 1; i <= 10; i++)
	{
		PRINT_EXTENDED_BOTTOM_UP_CUT_ROD(Price_array, i);
		cout << endl;
	}
	//////////////////////////////////////////////////////////////////////////
	//矩阵链乘法
	int Matrix_Chain_Array[] = { 30,35,15,5,10,20,25 };
	PARENS_SOLUTION ps;
	int psize = sizeof(Matrix_Chain_Array) / sizeof(int);
	MATRIX_CHAIN_ORDER(Matrix_Chain_Array, psize, ps);
	PRINT_OPTIMAL_PARENS(ps, 1, psize - 1);
	//////////////////////////////////////////////////////////////////////////
	//最长公共子序列
	string X = "ABCBDA";
	string Y = "BDCABA";
	LCS_SOLUTION lcs(X.length(), Y.length());

	LCS_LENGTH(X, Y, lcs);
	PRINT_LCS(lcs, X, X.length(), Y.length());

	//最优二叉搜索树
	float Opt_Bst_p[] = { 0.0, 0.15, 0.10, 0.05, 0.10, 0.20 };
	float Opt_Bst_q[] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };

	OPT_BST_SOLUTION obs;
	OPTIMAL_BST(Opt_Bst_p, Opt_Bst_q, sizeof(Opt_Bst_q)/sizeof(float) - 1, obs);

	//贪心算法
	//活动选择问题
	int Activity_s[] = { 0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	int Activity_f[] = { 0, 4, 5, 6 ,7, 9, 9, 10, 11, 12, 14, 16 };
	vector<int> va;
	Recursive_Activity_Selector(Activity_s, Activity_f, 0, sizeof(Activity_s) / sizeof(int) - 1, va);
	Greedy_Activity_Selector(Activity_s, Activity_f, sizeof(Activity_s) / sizeof(int) - 1, va);

	//哈夫曼编码
	int huffmancode[] = {45, 13, 12, 16, 9, 5 };
	Minheap<HaffmanNode<int>*> mn(1000, 0);
	HaffmanNode<int>* root = Huffman(huffmancode, sizeof(huffmancode) / sizeof(int), mn);

	HaffmanNode<int>::freemem(root);

	//任务调度问题
	task a[7], b[7], ta[7];
	ta[0].id = 0;
	ta[0].d = 4;
	ta[0].w = 70;

	ta[1].id = 1;
	ta[1].d = 2;
	ta[1].w = 60;

	ta[2].id = 2;
	ta[2].d = 4;
	ta[2].w = 50;

	ta[3].id = 3;
	ta[3].d = 3;
	ta[3].w = 40;

	ta[4].id = 4;
	ta[4].d = 1;
	ta[4].w = 30;

	ta[5].id = 5;
	ta[5].d = 4;
	ta[5].w = 20;

	ta[6].id = 6;
	ta[6].d = 6;
	ta[6].w = 10;

	int ans = ta[0].w + ta[1].w + ta[2].w + ta[3].w + ta[4].w + ta[5].w + ta[6].w;
	int a_num, b_num;
	greedy(a, b, ta, sizeof(ta) / sizeof(task), ans, a_num, b_num);

	printf("任务惩罚为：%d\n", ans);
	sort(a, a + a_num, cmpD);

	printf("将完成执行的任务按照时间递增顺序排列输出：\n");
	for (int i = 0; i < a_num; i++) {
		printf("ID：%d，期限：%d，惩罚：%d\n", a[i].id, a[i].d, a[i].w);
	}

	printf("贪心算法拒绝的任务：\n");
	for (int i = 0; i < b_num; i++) {
		printf("ID：%d，期限：%d，惩罚：%d\n", b[i].id, b[i].d, b[i].w);
	}
	//////////////////////////////////////////////////////////////////////////

	//测试数据
	{
		char ch[] = { 'F','S','Q','K','C','L','H','T','V','W','M','R','N','P','A','B','X','Y','D','Z','E' };
		//生成一棵B树
		B_Tree *T_B = new B_Tree;
		T_B->B_Tree_Create();
		//依次插入关键字
		cout << "插入测试" << endl;
		int i;
		for (i = 0; i < 21; i++)
		{
			T_B->B_Tree_Insert(ch[i]);
			T_B->Print(T_B->root);
			cout << endl;
		}
		//输出这棵树
		T_B->Print(T_B->root);
		cout << endl;
		//B树删除操作测试
		cout << "查找与删除测试" << endl;
		char c;
		for (i = 0; i < sizeof(ch) / sizeof(char) - 5; i++)
		{
			c = ch[i];
			T_B->B_Tree_Delete(T_B->root, c);
			T_B->Print(T_B->root);
			cout << endl;
		}

		T_B->Destory(T_B->root);

		delete T_B;
	}

	//////////////////////////////////////////////////////////////////////////
	//thread: 临界区 信号量 互斥量 事件
	//CThread_test thread_test;
	


	int i = 0;
	int& k = i;
	//move(i);
	SomeElement *pSE0 = new SomeElement;
	SomeElement *pSE1 = new SomeElement;
	SomeElement *pSE2 = new SomeElement;

	pSE0->m_link.m_pNext = &pSE1->m_link;
	pSE1->m_link.m_pPrev = &pSE0->m_link;


	pSE1->m_link.m_pNext = &pSE2->m_link;
	pSE2->m_link.m_pPrev = &pSE1->m_link;

	delete pSE0;
	delete pSE1;
	delete pSE2;

	SomeElement1* pSE1_0 = new SomeElement1;


	delete pSE1_0;

	unsigned __int64 time0 = 0xffffffffffffffffu;
	unsigned __int64 time1 = 3 * 1000000000u;

	unsigned __int64 year = time0 / (time1 * 365 * 24 * 3600u);

	std::string str1 = "1231242535";
	str1 = "123124253";
	std::string str2 = str1;



	NodeList nl;
	Node<int>* p = new Node<int>;
	p->data = 1;
	nl.InsertSort(p);

	p = new Node<int>;
	p->data = 0;
	nl.InsertSort(p);

	p = new Node<int>;
	p->data = 3;
	nl.InsertSort(p);

	p = new Node<int>;
	p->data = 2;
	nl.InsertSort(p);

	//std::move
	Person person;
	//func(person);
	func(std::move(person));


	return 0;
}

