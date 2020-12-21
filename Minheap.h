#pragma once

template<class T>
class Minheap
{
private:
	T* a;
	int size;
	int max_size;
public:
	Minheap(int _max_size, int _size) : max_size(_max_size), size(_size)
	{
		a = new T[_max_size];
	}
	~Minheap()
	{
		delete [] a;
	}
	void min_heap(int n, int i)
	{
		int min_i = i;
		if (2 * i < n && *a[2 * i] < *a[min_i])
			min_i = 2 * i;
		if (2 * i + 1 < n && *a[2 * i + 1] < *a[min_i])
			min_i = 2 * i + 1;
		if (min_i != i)
		{
			T temp = a[i];
			a[i] = a[min_i];
			a[min_i] = temp;

			min_heap(n, min_i);
		}
	}
	void build_min_heap(T* _a, int n)
	{
		memcpy(a, _a, sizeof(int) * n);
		for (int i = size / 2; i >= 0; i--)
		{
			min_heap(size, i);
		}
	}
	T heap_minnum()
	{
		return a[0];
	}
	void exchange(T& l, T& r)
	{
		T temp = l;
		l = r;
		r = temp;
	}
	T heap_extract_min()
	{
		T min = a[0];
		//exchange(a[0], a[size - 1]);
		T temp = a[0];
		a[0] = a[size - 1];
		a[size - 1] = temp;
		min_heap(size - 1, 0);
		size--;
		return min;
	}
	void minheap_insert_key(T key)
	{
		if (size == max_size)
			return;
		a[size] = key;
		int i = size;
		while (i > 0 && *a[i] < *a[i / 2])
		{
			//exchange(a[i], a[i / 2]);
			T temp = a[i];
			a[i] = a[i / 2];
			a[i / 2] = temp;
			i = i / 2;
		}
		size++;
	}
};
