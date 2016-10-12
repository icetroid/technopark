/*
В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д. Каждый атлет характеризуется силой si(kg) и массой mi(kg). 
Сила — это максимальная масса, которую атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее:
если mi>mj, то si> sj. Атлеты равной массы могут иметь различную силу.
*/

#include <iostream>
#include <assert.h>  

using namespace std;

struct Athlet
{
	int Mass;
	int Strength;
};

int compareAthlet(const void *athlet1, const void *athlet2)
{
	Athlet *athletP1 = (Athlet*)athlet1;
	Athlet *athletP2 = (Athlet*)athlet2;
	if (athletP1->Mass < athletP2->Mass)
	{
		return -1;
	}
	else if (athletP1->Mass > athletP2->Mass)
	{
		return 1;
	}
	else
	{
		if (athletP1->Strength < athletP2->Strength)
		{
			return -1;
		}
		else if (athletP1->Strength > athletP2->Strength)
		{
			return 1;
		}
	}
	return 0;
}

int findHeight(Athlet *athlets, int size)
{
	assert(size > 0);
	int height = 1;
	int totalMass = athlets[0].Mass;

	for (int i = 1; i < size; i++)
	{
		if (athlets[i].Strength >= totalMass)
		{
			height++;
			totalMass += athlets[i].Mass;
		}
	}

	return height;
}

int main()
{
	Athlet *athlets = new Athlet[100000];
	int size = 0;
	int mass = 0, strength = 0;
	while (scanf("%d%d", &mass, &strength) != EOF)
	{
		assert(mass > 0);
		assert(strength > 0);
		athlets[size].Mass = mass;
		athlets[size].Strength = strength;
		size++;
	}
	
	qsort(athlets, size, sizeof(Athlet), compareAthlet);

	int height = findHeight(athlets, size);

	cout << height;

	delete[] athlets;
	return 0;
}