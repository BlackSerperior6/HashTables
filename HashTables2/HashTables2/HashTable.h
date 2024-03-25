#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "List.h"

const int MinusOne = -1;

struct HashTable
{
private:

	double mod1(double n)
	{
		int intPart = (int)n;

		return n - intPart;
	}

	int getHash(int n)
	{
		return (int)(Size * mod1(n * M_PI_4));
	}

	int getHash(string Line)
	{
		int k = 0;

		for (int i = 0; i < Line.length(); i++)
			k += (int)Line[i];

		return getHash(abs(k));
	}

public:
	List** table;
	int Size;
	int CollisionCounter;

	HashTable(int LenghtOfTheTablet)
	{
		Size = LenghtOfTheTablet;
		CollisionCounter = 0;

		table = new List*[Size];

		for (int i = 0; i < Size; i++)
			table[i] = new List;
	}

	~HashTable()
	{
		for (int i = 0; i < Size; i++)
			delete table[i];

		delete[] table;
	}

	void Add(string birthDate, Human human) 
	{
		int hash = getHash(birthDate);

		if (!table[hash]->Push_Back(human))
			CollisionCounter++;
	}

	Human FindByKey(string key) 
	{
		int hash = getHash(key);

		return table[hash]->FindByBirthDate(key);
	}

	bool RemoveByKey(string key) 
	{
		int hash = getHash(key);

		return table[hash]->RemoveByBirthDate(key);
	}

	bool RemoveByValue(Human value)
	{
		bool flag = false;

		for (int i = 0; i < Size && !flag; i++)
			flag = table[i]->RemoveByBirthDate(value.BirthDay);

		return flag;
	}

	void Print() 
	{
		for (int i = 0; i < Size; i++)
		{
			if (table[i]->head == nullptr)
				continue;

			cout << i << ":" << endl;

			table[i]->print();
			cout << endl;
		}
	}

	void WriteIntoFile(ofstream *f) 
	{
		f->write((char*) &CollisionCounter, sizeof(int));

		for (int i = 0; i < Size; i++)
		{
			if (table[i]->head == nullptr)
				continue;

			f->write((char*)&i, sizeof(int));

			table[i]->Write_Into_File(f);
		}

		f->write((char*) &MinusOne, sizeof(int));
	}

	void ReadFromFile(ifstream *f)
	{
		f->read((char*) &CollisionCounter, sizeof(int));

		while (!f->eof())
		{
			int index = 0;
			f->read((char*) &index, sizeof(int));

			if (index != MinusOne)
				table[index]->Read_From_File(f);
		}
	}
};
