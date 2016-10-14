#include <iostream>

long long countPyramids(int cubesCount, int lastLayerSize, long long **foundValues)
{
	if (cubesCount <= 0 || lastLayerSize < 1)
	{
		return 0;
	}
	if (cubesCount == 1) 
	{
		return 1;
	}
	if (foundValues[cubesCount][lastLayerSize] != -1)
	{
		return foundValues[cubesCount][lastLayerSize];
	}

	foundValues[cubesCount][lastLayerSize] = countPyramids(cubesCount - lastLayerSize, lastLayerSize - 1, foundValues) + countPyramids(cubesCount, lastLayerSize - 1, foundValues) + (cubesCount == lastLayerSize);
	
	return foundValues[cubesCount][lastLayerSize];
}

int main()
{
	int N = 0;
	std::cin >> N;
	// выделение памяти под массив, в котором будут храниться найденные значения количества пирамид
	long long **foundValues = new long long*[N + 1];
	for (int i = 0; i < N + 1; i++)
	{
		foundValues[i] = new long long[N + 1];
		for (int j = 0; j < N + 1; j++)
		{
			foundValues[i][j] = -1;
		}
	}

	long long pyramidsCount = countPyramids(N, N, foundValues);

	std::cout << pyramidsCount;

	// освобождение памяти
	for (int i = 0; i < N + 1; i++)
	{
		delete foundValues[i];
	}
	delete[] foundValues;

	return 0;
}