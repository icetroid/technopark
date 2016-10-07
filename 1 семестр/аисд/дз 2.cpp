/*
“Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N. Будем исключать
каждого k­ого до тех пор, пока не уцелеет только один человек. (Например, если N=10, k=3, то сначала
умрет 3­й, потом 6­й, затем 9­й, затем 2­й, затем 7­й, потом 1­й, потом 8­й, за ним ­ 5­й, и потом 10­й. Таким
образом, уцелеет 4­й.) Необходимо определить номер уцелевшего.
*/

#include <iostream>
#include <assert.h>
using namespace std;

int findSurvived(int N, int k)
{
	bool *survivedPeople = new bool[N];
	
	//количество исключенных
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
