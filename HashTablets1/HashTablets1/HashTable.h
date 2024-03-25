#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

#include "Human.h"

const int MinusOne = -1;

using namespace std;

struct Node
{
	Human Value;
	string key;

	bool has_been_deleted = false;
};

struct HashTable
{
	Node** table;
	int Size;
	int CollisionCounter;

private:

	double mod1(double n)
	{
		int intPart = (int) n;

		return n - intPart;
	}

	int getHash(int n)
	{
		return (int) (Size * mod1(n * M_PI_4));
	}

	int getHash(string Line)
	{
		int k = 0;

		for (int i = 0; i < Line.length(); i++)
			k += (int) Line[i];

		return getHash(abs(k));
	}

	void SerString(ofstream* f, string line)
	{
		size_t Length = line.length();
		f->write((char*) (&Length), sizeof(Length));
		f->write((char*) (line.data()), Length);
	}

	string DesString(ifstream* f)
	{
		size_t Length = 0;
		f->read((char*) (&Length), sizeof(Length));

		string Line;
		Line.resize(Length);
		f->read((char*) (Line.data()), Length);

		return Line;
	}

public:

	void Print()
	{
		cout << endl << endl;

		for (int i = 0; i < Size; i++)
		{
			if (table[i] == nullptr || table[i]->has_been_deleted)
				continue;

			cout << i << ": ";

			table[i]->Value.Print();
		}

		cout << endl << endl;
	}

	HashTable(int LenghtOfTheTablet)
	{
		table = new Node*[LenghtOfTheTablet];
		Size = LenghtOfTheTablet;
		CollisionCounter = 0;

		for (int i = 0; i < Size; i++)
			table[i] = nullptr;
	}

	~HashTable()
	{
		for (int i = 0; i < Size; i++)
			delete table[i];

		delete[] table;
	}

	void Add(string birthDay, Human human)
	{
		int orgiginalHash = getHash(birthDay);
		int hash = orgiginalHash;

		if (table[hash] != nullptr && !table[hash]->has_been_deleted  && birthDay == table[hash]->key)
		{
			cout << "Ёлемент с данным ключем уже есть в хеш-таблице" << endl;
			return;
		}

		bool flag = false;
		int counterOfTakenPositions = 0;

		while (table[hash] != nullptr && !table[hash]->has_been_deleted && !flag && counterOfTakenPositions < Size)
		{
			if (table[hash]->key == birthDay) 
				flag = true;
			else
			{
				hash++;
				counterOfTakenPositions++;

				if (hash >= Size)
					hash = 0;
			}
		}

		if (flag)
		{
			cout << "Ёлемент с таким ключем уже есть в таблице!" << endl;
			return;
		}	

		if (counterOfTakenPositions >= Size)
		{
			cout << "¬ таблице не осталось места" << endl;
			return;
		}

		if (hash != orgiginalHash)
			CollisionCounter++;

		Node* new_node = new Node;

		new_node->Value = human;
		new_node->key = birthDay;

		table[hash] = new_node;
	}

	int FindByKey(string key)
	{
		int hash = getHash(key);

		bool flag = false;

		while (table[hash] != nullptr && !flag)
		{
			flag = table[hash]->key == key && !table[hash]->has_been_deleted;

			if (!flag)
			{
				hash++;

				if (hash >= Size)
					hash = 0;
			}
		}

		if (!flag)
			return -1;
		else
			return hash;
	}

	bool RemoveByKey(string key)
	{
		int index = FindByKey(key);

		if (index != -1)
		{
			table[index]->has_been_deleted = true;
			return true;
		}
		else
			return false;
	}

	bool RemoveByValue(Human human)
	{
		bool flag = false;

		for (int i = 0; i < Size && !flag; i++)
		{
			if (table[i] == nullptr || table[i]->has_been_deleted)
				continue;

			flag = table[i]->Value.Compare(&human);

			if (flag)
				table[i]->has_been_deleted = true;
		}

		return flag;
	}

	void WriteIntoFile(ofstream *output) 
	{
		output->write((char*)&CollisionCounter, sizeof(int));

		for (int i = 0; i < Size; i++)
		{
			if (table[i] == nullptr)
				continue;

			output->write((char*) &i, sizeof(int));

			Human human = table[i]->Value;

			SerString(output, human.FullName);
			SerString(output, human.BirthDay);

			output->write((char*) &human.PassportNumber, sizeof(int));

			output->write((char*) &(table[i]->has_been_deleted), sizeof(bool));
		}

		output->write((char*) &MinusOne, sizeof(int));
	}

	void ReadFromFile(ifstream *input)
	{
		input->read((char*)&CollisionCounter, sizeof(int));

		while (!input->eof())
		{
			int index;
			
			input->read((char*) &index, sizeof(int));

			if (index != -1)
			{
				Human human;

				human.FullName = DesString(input);
				human.BirthDay = DesString(input);

				input->read((char*)&(human.PassportNumber), sizeof(int));

				bool has_been_deleted;

				input->read((char*)&has_been_deleted, sizeof(bool));

				Node* new_node = new Node;

				new_node->Value = human;
				new_node->key = human.BirthDay;
				new_node->has_been_deleted = has_been_deleted;

				table[index] = new_node;
			}
		}
	}
};


