#include <string> 
#include <windows.h>

#include "HashTable.h"

int main()
{
	srand(time(0));

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int AmountOfHumans;

	do
	{
		cout << "Введите кол-во человек." << endl;
		cin >> AmountOfHumans;
	} while (AmountOfHumans <= 0);

	HashTable* hashTable = new HashTable(AmountOfHumans);

	for (int i = 0; i < AmountOfHumans; i++)
	{
		Human human;
		human.RandomlyGenerate();

		hashTable->Add(human.BirthDay, human);
	}

	hashTable->Print();

	bool should_stop = false;

	while (!should_stop)
	{
		int action;
		cout << "Выберите действие:" << endl << "1. Добавить в таблицу больше элементов." << endl << "2. Добавить один элемент вручную." << endl << "3. Найти элемент в таблице по ключу." << endl << "4. Удалить элемент в таблице по ключу." << endl << "5. Удалить элемент в таблице по значению." << endl << "6. Записать хеш-таблицу в файл и считать её заново из него." << endl << "7. Напечатать таблицу" << endl << "8. Закончить исполнение программы." << endl;

		cin >> action;

		Human human;
		string key;
		ofstream output;
		ifstream input;
		int index = 0;

		switch (action)
		{
		case 1:
			int howManyHumansToAdd;

			do
			{
				cout << endl << "Введите, сколько людей вы еще хотите добавить." << endl;
				cin >> howManyHumansToAdd;
			} 
			while (howManyHumansToAdd <= 0);

			for (int i = 0; i < howManyHumansToAdd; i++)
			{
				human.RandomlyGenerate();

				hashTable->Add(human.BirthDay, human);
			}

			cout << endl << endl;

			break;

		case 2:

			cin.ignore();

			human.FillByUser();

			hashTable->Add(human.BirthDay, human);

			cout << endl;

			break;

		case 3:

			cout << endl << "Введите ключ элемента, который вы хотите найти: " << endl;

			cin.ignore();

			getline(cin, key);

			human = hashTable->FindByKey(key);

			if (human.BirthDay == NOTFOUND)
				cout << "Элемента с таким ключем не существует" << endl;
			else
				human.Print();

			cout << endl;

			break;

		case 4:

			cout << endl << endl << "Введите ключ элемента, который вы хотите удалит: " << endl;

			cin.ignore();
			getline(cin, key);

			if (hashTable->RemoveByKey(key))
				cout << "Элемент успешно удален" << endl << endl;
			else
				cout << "Элемента с таким ключем нет в хеш-таблице" << endl;

			cout << endl;

			break;

		case 5:

			cin.ignore();

			human.FillByUser();

			if (hashTable->RemoveByValue(human))
				cout << "Элемент успешно удален" << endl << endl;
			else
				cout << "Такого элемента нет в таблице" << endl;

			cout << endl;

			break;

		case 6:

			output.open("F1.bin", ios_base::binary);

			if (!output.is_open())
				cout << "Файл не найден!" << endl;

			else
			{
				hashTable->WriteIntoFile(&output);

				output.close();

				delete hashTable;

				hashTable = new HashTable(AmountOfHumans);

				input.open("F1.bin", ios_base::binary);

				hashTable->ReadFromFile(&input);

				input.close();
			}

			cout << endl;

			break;

		case 7:

			hashTable->Print();
			break;

		case 8:

			should_stop = true;
			break;

		default:

			cout << "Нету такого действия" << endl << endl;
			break;
		}

	}

	cout << endl << "Итоговое кол-во коллизий: " << hashTable->CollisionCounter << endl;

	delete hashTable;
}