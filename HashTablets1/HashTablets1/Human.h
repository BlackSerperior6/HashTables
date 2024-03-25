#pragma once

#include <iostream>
#include <string>

using namespace std;

string PossibleNames[] = {"Александр" , "Люся", "Мария", "Александр", "Дима", "Деннис", "Светлана", "Валентино", "Аластор"};

string PossibleSurnames[] = {"Герасимов", "Дудкин", "Морнингстар", "Собек", "Светлый", "Темный", "Злобный", "Добрый", "Пасхальный"};

string PossiblePatronimycs[] = {"Викторовна", "Плюшкин", "Зушкин", "Метелкин", "Советсвккий", "Николаевич", "Николаевна", "Пасхальновн", "Тубкин"};

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
		cout << "ФИО: " << FullName << ", дата рождения: " << BirthDay << ", номер паспорта: " << PassportNumber << endl;
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
		cout << "Введите имя: "; getline(cin, FullName);
		cout << "Введите дату рождения: "; getline(cin, BirthDay);
		cout << "Введите номер паспорта: "; cin >> PassportNumber;
	}
};
