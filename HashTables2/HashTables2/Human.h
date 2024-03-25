#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string PossibleNames[] = { "������" , "����", " ������", "�����", "����", "�������"};

string PossibleSurnames[] = { "��������", "�������� ", "��������", "���������", "���������"};

string PossiblePatronimycs[] = { "����������", "��������", "����������"};

struct Human
{

private:
	void SerString(ofstream* f, string line)
	{
		size_t Length = line.length();
		f->write((char*)(&Length), sizeof(Length));
		f->write((char*)(line.data()), Length);
	}

	string DesString(ifstream* f)
	{
		size_t Length = 0;
		f->read((char*)(&Length), sizeof(Length));

		string Line;
		Line.resize(Length);
		f->read((char*)(Line.data()), Length);

		return Line;
	}

public:
	string FullName;
	string BirthDay;
	int PassportNumber;

	void Print()
	{
		cout << " ���: " << FullName << ", ���� ��������: " << BirthDay << ", ����� ��������: " << PassportNumber << endl;
	}

	void RandomlyGenerate()
	{
		string name = PossibleNames[rand() % 6];
		string surname = PossibleSurnames[rand() % 5];
		string patronimyc = PossiblePatronimycs[rand() % 3];

		FullName = surname + " " + name + " " + patronimyc;

		BirthDay = to_string(rand() % 28 + 1) + '.' + to_string(rand() % 12 + 1) + '.' + to_string(rand() % 11 + 2000);

		PassportNumber = rand() % 1000 + 1001;
	}

	void FillByUser()
	{
		cout << "������� ���: "; getline(cin, FullName);
		cout << "������� ���� ��������: "; getline(cin, BirthDay);
		cout << "������� ����� ��������: "; cin >> PassportNumber;
	}

	void WriteIntoFile(ofstream *file)
	{
		SerString(file, FullName);
		SerString(file, BirthDay);

		file->write((char*) &PassportNumber, sizeof(int));
	}

	void ReadFromFile(ifstream *file)
	{
		FullName = DesString(file);
		BirthDay = DesString(file);

		file->read((char*)&PassportNumber, sizeof(int));
	}
};
