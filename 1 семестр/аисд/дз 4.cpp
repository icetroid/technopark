/*
​Реализовать дек с динамическим зацикленным буфером.
*/
#include <iostream>
#include <assert.h>
using namespace std;

#define INITIAL_SIZE 8

class Deque
{
public:
	Deque();
	~Deque();
	void PushFront(int data);
	void PushBack(int data);
	int PopFront();
	int PopBack();
	bool IsEmpty() const;
private:
	void increaseSize();
	void decreaseSize();
	int *buffer;
	int tail;
	int head;
	int size;
	int length;
};

Deque::Deque() : tail(0), head(0), length(0)
{
	buffer = new int[INITIAL_SIZE];
	size = INITIAL_SIZE;
}

Deque::~Deque()
{
	delete[] buffer;
}

void Deque::increaseSize()
{
	int *newBuffer = new int[size * 2];

	//копируем все элементы от head до конца буфера
	memcpy(newBuffer, buffer + head, (size - head) * sizeof(int));

	if (head != 0)
	{
		//копируем все элементы от 0 до tail
		memcpy(newBuffer + (size - head), buffer, tail * sizeof(int));
	}

	delete[] buffer;
	buffer = newBuffer;
	head = 0;
	tail = size;
	size *= 2;
}

void Deque::decreaseSize()
{
	int *newBuffer = new int[size / 2];

	int end = tail < head ? size : tail;

	//копируем все элементы от head до end
	memcpy(newBuffer, buffer + head, (end - head) * sizeof(int));
	if (tail < head)
	{
		//копируем все элементы от 0 до tail
		memcpy(newBuffer + (end - head), buffer, tail * sizeof(int));
	}

	delete[] buffer;
	buffer = newBuffer;
	head = 0;
	tail = size / 4;
	size /= 2;
}

void Deque::PushFront(int data)
{
	length++;
	head = ((head - 1) + size) % size;
	buffer[head] = data;
	if (length == size)
	{
		increaseSize();
	}
}

void Deque::PushBack(int data)
{
	length++;
	buffer[tail] = data;
	tail = (tail + 1) % size;
	if (length == size)
	{
		increaseSize();
	}
}

int Deque::PopFront()
{
	if (IsEmpty())
	{
		return -1;
	}

	int date = buffer[head];
	head = (head + 1) % size;
	length--;
	if (length <= size / 4 && length >= 8)
	{
		decreaseSize();
	}
	return date;
}

int Deque::PopBack()
{
	if (IsEmpty())
	{
		return -1;
	}

	tail = ((tail - 1) + size) % size;
	int date = buffer[tail];
	length--;
	if (length < size / 4 && length >= 8)
	{
		decreaseSize();
	}
	return date;
}

bool Deque::IsEmpty() const
{
	return length == 0;
}

int main()
{
	int n = 0;
	cin >> n;
	assert(n > 0);
	Deque deque;
	bool result = true;

	for (int i = 0; i < n; i++)
	{
		int operation = 0;
		int number = 0;
		cin >> operation;
		cin >> number;
		switch (operation)
		{
		case 1:
			deque.PushFront(number);
			break;
		case 2:
			if (number != deque.PopFront())
			{
				result = false;
			}
			break;
		case 3:
			deque.PushBack(number);
			break;
		case 4:
			number = deque.PopBack();
			if (number != deque.PopFront())
			{
				result = false;
			}
			break;
		}
	}

	cout << (result ? "YES" : "NO");
	return 0;
}