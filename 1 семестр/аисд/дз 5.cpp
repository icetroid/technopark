/*
Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники
расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). Требуется найти M ­
площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой
фигуры.
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
	// высота последнего прямоугольника
	int prevHeight = -1;
	// высота предпоследнего прямоугольника
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
			// берем из стека последний прямоугольник, увеличиваем его ширину на width, кладем обратно
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
			// кладем новый прямоугольник в стек 
			Node node(width, height);
			stack.Push(node);
			prevPrevHeight = prevHeight;
			prevHeight = height;
		}
		else if (height < prevHeight)
		{
			// берем из стека последний прямоугольник
			Node prevRect = stack.Pop();

			if (!stack.IsEmpty())
			{
				// берем из стека предпоследний прямоугольник, если он есть
				Node prevPrevRect = stack.Pop();

				if (height > prevPrevRect.Height)
				{
					// уменьшаем высоту последнего прямоугольника до height, 
					// а ширину увеличиваем на width, кладем получившийся прямоугольник в стек
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
					// уменьшаем высоту последнего прямоугольника до высота предпоследнего, 
					// а к ширине прибавляем ширину предпоследнего прямоугольника, 
					// кладем в стек получившийся прямоугольник
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
					// высоту последнего прямоугольника уменьшаем до height, 
					// а к ширине прибавляем ширину предпоследнего прямоугольника и width, 
					// кладем его в стек 
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
				// уменьшаем высоту последнего прямоугольника до height, 
				// а к ширине прибавляем width, кладем его обратно
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

	// выталкивание оставшихся прямоугольников из стека
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