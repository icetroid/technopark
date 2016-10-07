/*
������������. � ���� ��������� N �������, ��������������� ������� �� 1 �� N. ����� ���������
������� k���� �� ��� ���, ���� �� ������� ������ ���� �������. (��������, ���� N=10, k=3, �� �������
����� 3��, ����� 6��, ����� 9��, ����� 2��, ����� 7��, ����� 1��, ����� 8��, �� ��� � 5��, � ����� 10��. �����
�������, ������� 4��.) ���������� ���������� ����� ����������.
*/

#include <iostream>
#include <assert.h>
using namespace std;

int findSurvived(int N, int k)
{
	bool *survivedPeople = new bool[N];
	
	//���������� �����������
	int excludedCount = 0;
	
	for(int i = 0; i < N; i++)
	{
		survivedPeople[i] = true;
	}
	
	int currentIndex = -1;
	
	while(excludedCount < N - 1)
	{
		int i = 0;
		while(i < k)
		{
			currentIndex++;
			if(currentIndex == N)
			{
				currentIndex = 0;	
			}
			
			if(survivedPeople[currentIndex])
			{
				i++;
			}
		}
		
		
		survivedPeople[currentIndex] = false;
		excludedCount++;
	}
	

	for(int i = 0; i < N; i++)
	{
		if(survivedPeople[i])
		{
			
			return i+1;
		}
	}
		
	delete[] survivedPeople;
	
	return 0;
}

int main()
{
	int N = 0;
	int k = 0;
	cin >> N >> k;
	
	assert(N >= 0);
	assert(k > 0);
	
	int survivedIndex = findSurvived(N, k);
	
	cout << survivedIndex;
	return 0;
}
