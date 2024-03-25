#pragma once

#include <iostream>
#include <string>

using namespace std;

string PossibleNames[] = {"���������" , "����", "�����", "���������", "����", "������", "��������", "���������", "�������"};

string PossibleSurnames[] = {"���������", "������", "�����������", "�����", "�������", "������", "�������", "������", "����������"};

string PossiblePatronimycs[] = {"����������", "�������", "������", "��������", "�����������", "����������", "����������", "�����������", "������"};

struct Human 
{
	string FullName;
	string BirthDay;
	int PassportNumber;

	bool Compare(Human *anotherHuman) 
	{
		return FullName == anotherHuman->FullName && PassportNumber == anotherHuman->PassportNumber;
	};

	void Print()
	{
		cout << "���: " << FullName << ", ���� ��������: " << BirthDay << ", ����� ��������: " << PassportNumber << endl;
	}

	void RandomlyGenerate()
	{
		string name = PossibleNames[rand() % 9];
		string surname = PossibleSurnames[rand() % 9];
		string patronimyc = PossiblePatronimycs[rand() % 9];

		FullName = name + " " + surname + " " + patronimyc;

		BirthDay = to_string(rand() % 28 + 1) + '.' + to_string(rand() % 12 + 1) + '.' + to_string(rand() % 100 + 2000);

		PassportNumber = rand() % 1000;
	}

	void FillByUser() 
	{
		cout << "������� ���: "; getline(cin, FullName);
		cout << "������� ���� ��������: "; getline(cin, BirthDay);
		cout << "������� ����� ��������: "; cin >> PassportNumber;
	}
};
