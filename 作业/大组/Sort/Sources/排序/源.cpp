#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int* inita(int max,int min) {
	int* array = (int*)malloc(((max-min)+1) * sizeof(int));
	if (array == NULL) {
		printf("!");
		return NULL;
	}

	for (int i = 0; i <(max-min)+1; i++) {
		array[i] = 0;
	}
	return array;
}
void insert(int* array, int* marray, int max,int min)
{
	int a = 0;
	for (int i = 0; i < (max-min)+1; i++)
	{
		for (int j = 0; j < marray[i]; j++)
		{
			array[a++] = i + min;
		}
	}
	free(marray);
}
void printsort(int* array, int num)
{
	for (int i = 0; i < num; i++)
		printf("%d ", array[i]);
}
void insertsort(int* array, int num)
{
	int i, j;
	for (i = 1; i < num; i++)
	{
		int sensor = array[i];
		for (j = i - 1; (j >= 0 && sensor < array[j]); j--)
		{
			if (sensor >= array[j])
				break;
			array[j + 1] = array[j];
		}
		array[j + 1] = sensor;
	}
}
void fastsort(int* array, int num)
{
	int model = array[0];
	int l = 0;
	int r = num - 1;
	int direct = 1;
	if (num < 2)
		return;
	while (l < r)
	{
		if (direct == 1)
		{
			if (array[r] <= model)
			{
				array[l] = array[r];
				int direct = 0;
				l++;
			}
			r--;
		}
		if (direct == 0)
		{
			if (array[l] > model)
			{
				array[r] = array[l];
				int direct = 1;
				r--;
			}
			l++;
		}
	}
	array[l] = model;
	fastsort(array, l);
	fastsort(array + l + 1, num - l - 1);
}
void countsort(int* array, int num)
{
	int max = array[0];
	int min= array[0];
	if (num < 2)
		return;
	for (int i = 0; i < num; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	for (int i = 0; i < num; i++)
	{
		if (array[i] < min)
			min = array[i];
	}
	int* marray = inita(max,min);
	for (int i = 0; i < num; i++)
	{
		marray[array[i]-min]++;
	}
	insert(array, marray, max,min);
}
void funderinset(int* array, int a[][100], int num)
{
	int c = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (a[i][j] != -1)
			{
				array[c] = a[i][j];
				c++;
				a[i][j] = -1;
			}
		}
	}
}
void fundersort(int* array, int num)
{
	int a[10][100];
	int c = 0;
	int max = array[0];
	int maxw=1;
	for (int i = 0; i < num; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	int q = 1;
	while(max/q!=0)
	{
		q *= 10;
		maxw++;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			a[i][j] = -1;
		}
	}
	q = 1;
	for (int j = 0; j < maxw; j++)
	{
		c = 0;
		for (int i = 0; i < num; i++)
		{
			a[(array[i]/q)% 10][c] = array[i];
			c++;
		}
		funderinset(array, a, num);
		q *= 10;
	}
}
void merge(int* arr, int l, int m, int r) {
	int n1 = m - l + 1, n2 = r - m;
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	for (int i = 0; i < n1; i++) L[i] = arr[l + i];
	for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
	}
	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];

	free(L); free(R);
}

void merge_sort(int* arr, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
void merge_sort_wrapper(int* arr, int num) {
	merge_sort(arr, 0, num - 1);
}
// 生成随机数据
int* generate_data(int size) {
	int* data = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		data[i] = rand() % 1000;
	return data;
}

// 性能测试函数
void performance_test(void (*sort_func)(int*, int), int size) {
	int* data = generate_data(size);
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	sort_func(data, size);

	QueryPerformanceCounter(&end);
	double time = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
	printf("Size: %d\tTime: %.3f ms\n", size, time);
	free(data);
}
int main() {
	int choice, size;
	while (1) {
		printf("排序算法测试\n1.快速排序\n2.插入排序\n3.归并排序\n4.基数排序\n5.计数排序\n请输入序号：");
		scanf("%d", &choice);
		printf("输入测试数据量（如10000）：");
		scanf("%d", &size);
		switch (choice) {
		case 1: performance_test(fastsort, size); break;
		case 2: performance_test(insertsort, size); break;
		case 3: performance_test(merge_sort_wrapper, size); break;
		case 4: performance_test(fundersort, size); break;
		case 5: performance_test(countsort, size); break;
		default: printf("无效输入\n");
		}
		system("pause");
	}
	return 0;
}