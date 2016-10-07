/*
* Вывести разложение натурального числа n на простые множители. Простые множители должны быть
* упорядочены по возрастанию и разделены пробелами.
*/

#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
	assert(num > 1);
	for(int i = 2; i * i <= num; i++)
	{
		if(num % i == 0)
		{
			return false;	
		}
	}
	return true;
}

int findPrimes(int n, int* primes)
{
	assert(n >= 2);
	
	int currentPrimeIndex = 0;
	
	for(int i = 2;  i <= n; i++)
	{		
		if((n % i == 0) && isPrime(i))
		{
			while(n % i == 0)
			{
				n /= i;
				primes[currentPrimeIndex++] = i;
			}
		}
	}
	
	return currentPrimeIndex;

}

void printPrimes(int primeCount, int* primes)
{
	assert(primeCount >= 0);
	
	for(int i = 0; i < primeCount; i++)
	{
		cout << primes[i] << " ";
	}
}

int main()
{
	int n = 0;
	cin >> n;
	int maxPrimeCount = log(n) / log(2);
	int* primes = new int[maxPrimeCount];
	
	int primeCount = findPrimes(n, primes);
	
	printPrimes(primeCount, primes);
	delete [] primes;
	return 0;
}
