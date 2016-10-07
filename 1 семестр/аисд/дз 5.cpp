/*
���� ������������������ N ��������������� ��������� ������ � ������ (wi,hi). ��������������
�����������, ������� � ����� (0, 0), �� ��� �� �������� ���� �� ������ (������). ��������� ����� M �
������� ������������� �������������� (������������� ���� ���������), ������� ����� �������� �� ����
������.
*/
#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
	int Width;
	int Height;
	Node *Next;
	Node::Node(int width, int height) : Width(width), Height(height){}
};

class Stack
{
public:
	Stack();
	~Stack();
	Node Pop();
	void Push(Node &node);
	bool IsEmpty() const;
private:
	Node *head;
};


Stack::Stack() : head(0) {}

Stack::~Stack()
{
	Node *node = head;
	while (node != NULL)
	{
		Node *current = node;
		node = node->Next;
		delete current;
	}
}

bool Stack::IsEmpty() const
{
	return head == NULL;
}

void Stack::Push(Node &node)
{
	Node *newNode = new Node(node.Width, node.Height);
	newNode->Next = head;
	head = newNode;
}

Node Stack::Pop()
{
	Node *temp = head;
	Node node(temp->Width, temp->Height);
	head = head->Next;
	delete temp;
	return node;
}

int findMaxArea(int N)
{
	Stack stack;
	// ������ ���������� ��������������
	int prevHeight = -1;
	// ������ �������������� ��������������
	int prevPrevHeight = -1;

	int maxArea = 0;
	int width = 0;
	int height = 0;
	int index = 0;
	cin >> width;
	cin >> height;

	assert(width >= 0);
	assert(height >= 0);

	while (true)
	{
		
		if (width * height > maxArea)
		{
			maxArea = width * height;
		}

		if (height == prevHeight)
		{
			// ����� �� ����� ��������� �������������, ����������� ��� ������ �� width, ������ �������
			Node node = stack.Pop();

			if ((node.Width + width) * height > maxArea)
			{
				maxArea = (node.Width + width) * height;
			}

			node.Width = node.Width + width;
			stack.Push(node);
		}
		else if (height > prevHeight)
		{
			// ������ ����� ������������� � ���� 
			Node node(width, height);
			stack.Push(node);
			prevPrevHeight = prevHeight;
			prevHeight = height;
		}
		else if (height < prevHeight)
		{
			// ����� �� ����� ��������� �������������
			Node prevRect = stack.Pop();

			if (!stack.IsEmpty())
			{
				// ����� �� ����� ������������� �������������, ���� �� ����
				Node prevPrevRect = stack.Pop();

				if (height > prevPrevRect.Height)
				{
					// ��������� ������ ���������� �������������� �� height, 
					// � ������ ����������� �� width, ������ ������������ ������������� � ����
					prevHeight = height;

					if ((width + prevRect.Width) * height > maxArea)
					{
						maxArea = (width + prevRect.Width) * height;
					}

					prevRect.Width = width + prevRect.Width;
					prevRect.Height = height;
					stack.Push(prevPrevRect);
					stack.Push(prevRect);
				}
				else if (height < prevPrevRect.Height)
				{
					// ��������� ������ ���������� �������������� �� ������ ��������������, 
					// � � ������ ���������� ������ �������������� ��������������, 
					// ������ � ���� ������������ �������������
					prevPrevHeight = 0;

					if (!stack.IsEmpty())
					{
						Node node = stack.Pop();
						prevPrevHeight = node.Height;
						stack.Push(node);
					}

					prevHeight = height;
					
					if ((prevRect.Width + prevPrevRect.Width) * prevPrevRect.Height > maxArea)
					{
						maxArea = (prevRect.Width + prevPrevRect.Width) * prevPrevRect.Height;
					}

					prevRect.Width = width + prevRect.Width;
					prevRect.Height = height;
					stack.Push(prevRect);
					continue;
				}
				else
				{
					// ������ ���������� �������������� ��������� �� height, 
					// � � ������ ���������� ������ �������������� �������������� � width, 
					// ������ ��� � ���� 
					prevPrevHeight = 0;

					if (!stack.IsEmpty())
					{
						Node node = stack.Pop();
						prevPrevHeight = node.Height;
						stack.Push(node);
					}

					prevHeight = height;

					if ((prevRect.Width + prevPrevRect.Width + width) * height > maxArea)
					{
						maxArea = (prevRect.Width + prevPrevRect.Width + width) * height;
					}

					prevPrevRect.Height = height;
					prevPrevRect.Width = prevRect.Width + prevPrevRect.Width + width;
					stack.Push(prevPrevRect);
				}
			}
			else
			{
				// ��������� ������ ���������� �������������� �� height, 
				// � � ������ ���������� width, ������ ��� �������
				if ((prevRect.Width + width) * height > maxArea)
				{
					maxArea = (prevRect.Width + width) * height;
				}

				prevRect.Width = prevRect.Width + width;
				prevRect.Height = height;
				stack.Push(prevRect);
				prevPrevHeight = -1;
				prevHeight = height;
			}
		}		

		index++;
		if (index >= N)
		{
			break;
		}
		cin >> width;
		cin >> height;
	}

	int lastWidth = 0;

	// ������������ ���������� ��������������� �� �����
	while (!stack.IsEmpty())
	{
		Node node = stack.Pop();
		if ((node.Width + lastWidth) * node.Height > maxArea)
		{
			maxArea = (node.Width + lastWidth) * node.Height;
		}
		lastWidth = node.Width + lastWidth;
	}

	return maxArea;
}


int main()
{
	int N;
	cin >> N;
	assert(N >= 1);

	int area = findMaxArea(N);

	cout << area;
	return 0;
}