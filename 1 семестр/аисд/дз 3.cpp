/*
​Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n­1] и B[0..m­1].
n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k ­ позиция элементта B[m­1] в
массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
элемента B[i­1].
*/

#include <iostream>
#include <assert.h>
using namespace std;

/*
возращает индекс первого элемента, который больше или равен key
*/
int binarySearchAscend(int* arr, int size, int key)
{
	assert(size >= 0);
	int index = 0;
	while (index < size)
	{
		if (arr[index] >= key)
		{
			return index;
		}
		index = index * 2 + 1;
	}
	return -1;
}

int binarySearch(int* arr, int left, int right, int key)
{
	assert(left >= 0);
	assert(left <= right);

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (key < arr[mid])
		{
			right = mid - 1;
		}
		else if (key > arr[mid])
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;

}

int findIntersection(int* A, int n, int* B, int m, int* intersection)
{
	assert(n >= 0);
	assert(m >= 0);

	//текущий индекс в массиве А
	int currentIndexA = 0;
	//текущий индекс в массиве intersection
	int currentIndexIntersection = 0;

	// последний элемент массива B находится между left и right
	int left = 0;
	int right = 0;
	
	int approxIndexLastElementB = binarySearchAscend(A, n, B[m - 1]);

	if (approxIndexLastElementB == -1)
	{
		right = n - 1;
	}
	else
	{
		left = ((approxIndexLastElementB - 1) / 2) + 1;
		right = approxIndexLastElementB;
	}

	//индекс последнего элемента массива B
	int k = binarySearch(A, left, right, B[m - 1]);

	for (int i = 0; i < m - 1; i++)
	{
		while (A[currentIndexA] < B[i])
		{
			currentIndexA++;
		}

		if (k != -1 && currentIndexA >= k)
		{
			break;
		}

		if (A[currentIndexA] == B[i])
		{
			intersection[currentIndexIntersection++] = B[i];
			currentIndexA++;
		}
	}

	if (k != -1)
	{
		//в массиве А есть элемент, равный последнему элемент массива В
		intersection[currentIndexIntersection++] = B[m - 1];
	}

	return currentIndexIntersection;
}

int main()
{
	int n = 0;
	int m = 0;
	cin >> n >> m;
	assert(n >= 0);
	assert(m >= 0);
	int *A = new int[n];
	int *B = new int[m];

	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}

	for (int i = 0; i < m; i++)
	{
		cin >> B[i];
	}

	int *intersection = new int[m];
	int intersectionCount = findIntersection(A, n, B, m, intersection);

	for (int i = 0; i < intersectionCount; i++)
	{
		cout << intersection[i] << " ";
	}

	delete[] intersection;
	delete[] A;
	delete[] B;
	return 0;
}