#pragma once
#include <iostream>
#include <fstream>

#include "Human.h"

constexpr auto NOTFOUND = "NOTFOUND";

using namespace std;

struct Node //Структура элемента списка
{
    Human human; //Данные, которые он содержит
    Node* next = nullptr; //Следующий элемент списка
    Node* prev = nullptr; //Предыдущий элемент списка
};

struct List
{
    Node* head = nullptr; //Первый элемент списка
    Node* tail = nullptr; //Последний элемент списка

    bool Push_Back(Human element) //Метод добавления элемента в конец списка
    {

        Node* new_node = new Node; //Создаем новый элемент
        new_node->human = element; //Записываем в новый элемент нужные данные

        if (head == nullptr) //Если список пуст
        {
            //Голова и хвост = новый элемент
            head = new_node;
            tail = new_node;
            return true;
        }
        else
        {
            bool flag = false;

            Node* cur_node = head;

            while (cur_node != nullptr && !flag)
            {
                flag = cur_node->human.BirthDay == element.BirthDay;
                cur_node = cur_node->next;
            }

            if (flag)
            {
                cout << "Элемент с таким ключем уже есть в таблице" << endl;
                return true;
            }

            tail->next = new_node; //Ставим новый элемент после хвоста
            new_node->prev = tail; //Ставим хвост перед новым элементом
            tail = new_node; //Новый элемент становится хвостом

            return false;
        }
    }

    void print() //Метод печати списка
    {
        Node* current = head; //Инициализируем переменную, которая хранит в себе текущий элемент списка

        if (current == nullptr) //Если самый первый элемент списка оказался пустым
            return; //Значит список пуст

        else
        {

            while (current != nullptr) //Пока не дошли до конца списка
            {
                current->human.Print(); //Выводим данные текущего элемента

                current = current->next; //Переходим к следующему
            }

            cout << endl;
        }
    }

    Human FindByBirthDate(string birthDate)
    {
        Human result;
        result.BirthDay = NOTFOUND;

        Node* current = head;

        while (current != nullptr && result.BirthDay == NOTFOUND)
        {
            if (current->human.BirthDay == birthDate)
                result = current->human;

            current = current->next;
        }

        return result;
    }

    bool RemoveByBirthDate(string birthDate)
    {
        Node* curren = new Node; //Инициализируем переменную, обозначающую текущий элемент списка
        curren->next = head; //Следующий после этого элемент - голова
        bool flag = false;

        while (curren != nullptr) //Пока не дошли до конца списка
        {
            Node* tmp = curren; //Записываем текущий элемент в временный 
            curren = curren->next; //Идем дальше

            if (tmp->human.BirthDay == birthDate) //Если данные соответствуют ключу
            {
                flag = true;

                if (tmp->next == nullptr && tmp->prev == nullptr) //Если в списке один элемент
                {
                    //Голова и хвост = нулевые указатели
                    head = nullptr;
                    tail = nullptr;
                }

                else if (tmp == head) // Если мы в голове
                {
                    head = tmp->next; //Голова = следующий элемент
                    head->prev = nullptr;  // Предыдущий элемент головы = нулевой указатель
                }

                else if (tmp == tail) //Если мы в хвосте
                {
                    tail = tmp->prev; //Хвост = предыдущий элемент
                    tail->next = nullptr; //Следующий элемент после хвоста = нулевой указатель
                }

                else //Если в другом месте списка
                {
                    tmp->prev->next = tmp->next; //Следующий элемент предыдущего = следующий элемент
                    tmp->next->prev = tmp->prev; //Предыдущий элемент предыдущего = предыдущий элемент
                }

                delete tmp; //Удаляем временную переменную
            }
        }

        return flag;
    }

    int GetSize() //Метод получения размера списка
    {
        int counter = 0; //Счетчик

        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца списка
        {
            current = current->next; //Переходим на следующий элемент
            counter++; //Увеличиваем счетчик
        }

        return counter; //Возвращаем счетчик
    }

    void Write_Into_File(ofstream* f) //Метод для записи списка в файл
    {
        int Size = GetSize();

        f->write((char*) &Size, sizeof(int));

        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца списка
        {
            current->human.WriteIntoFile(f); //Записываем данные текущего элемента в список
            current = current->next; //Переходим на следующий элемент
        }
    }

    void Read_From_File(ifstream* f) //Метод для востановления списка из файла
    {
        int Size = 0;

        f->read((char*) &Size, sizeof(int));

        for (int i = 0; i < Size; i++)
        {
            Human human;
            human.ReadFromFile(f);
            Push_Back(human);
        }
    }

    ~List() //Метод очистки списка
    {
        while (head != nullptr) //Пока не дошли до конца списка
        {
            Node* tmp = head; //Записываем голову во временную переменную
            head = head->next; //Головой теперь является элемент после головы
            delete tmp; //Удалить текущий элемент
        }

        tail = nullptr; //Сделать хвост нулевым указателем
    }
};
