#include <iostream>

using namespace std;

int	countPyramid(int cubesCount, int *pyramidCountFound, int maxLen = -1)
{
	static int c, d;
	c++;

	if (cubesCount == 1 || cubesCount == 2)
	{
		c--;
		return 1;
	}
	if (maxLen != -1 && (maxLen*maxLen + maxLen / 2) < cubesCount)
	{
		c--;
		return 0;
	}
	else if (maxLen != -1 && (maxLen*maxLen + maxLen / 2) <= cubesCount + 2)
	{
		c--;
		return 1;
	}

	int count = 1;
	int beginLen = maxLen == -1 ? 1 : cubesCount - maxLen;
	int endLen = maxLen == -1 ? (cubesCount + 1) / 2 : maxLen;
	int minLen = sqrt(1 + 8 * cubesCount) / 2;

	if (beginLen > endLen)
	{
		for (int i = minLen; i <= maxLen; i++)
		{
			count += countPyramid(cubesCount - i, pyramidCountFound, i - 1);
		}
	}
	else
	{
		for (int i = beginLen; i < endLen; i++)
		{
			if (pyramidCountFound[i] == -1)
			{

				pyramidCountFound[i] = countPyramid(i, pyramidCountFound);
				d++;
				cout << " d = " << d << endl;
			}
			count += pyramidCountFound[i];
		}


		for (int i = cubesCount - 1 - (cubesCount + 1) / 2; i >= minLen; i--)
		{
			count += countPyramid(cubesCount - i, pyramidCountFound, i - 1);
		}
	}
	c--;
	return count;
}

int main()
{
	int N = 0;
	cin >> N;
	int *pyramidCountFound = new int[N];
	for (int i = 0; i < N; i++)
	{
		pyramidCountFound[i] = -1;
	}
	int pyramidCount = countPyramid(N, pyramidCountFound);

	cout << pyramidCount;
	delete[] pyramidCountFound;
	return 0;
}