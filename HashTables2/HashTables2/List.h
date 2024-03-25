#pragma once
#include <iostream>
#include <fstream>

#include "Human.h"

constexpr auto NOTFOUND = "NOTFOUND";

using namespace std;

struct Node //��������� �������� ������
{
    Human human; //������, ������� �� ��������
    Node* next = nullptr; //��������� ������� ������
    Node* prev = nullptr; //���������� ������� ������
};

struct List
{
    Node* head = nullptr; //������ ������� ������
    Node* tail = nullptr; //��������� ������� ������

    bool Push_Back(Human element) //����� ���������� �������� � ����� ������
    {

        Node* new_node = new Node; //������� ����� �������
        new_node->human = element; //���������� � ����� ������� ������ ������

        if (head == nullptr) //���� ������ ����
        {
            //������ � ����� = ����� �������
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
                cout << "������� � ����� ������ ��� ���� � �������" << endl;
                return true;
            }

            tail->next = new_node; //������ ����� ������� ����� ������
            new_node->prev = tail; //������ ����� ����� ����� ���������
            tail = new_node; //����� ������� ���������� �������

            return false;
        }
    }

    void print() //����� ������ ������
    {
        Node* current = head; //�������������� ����������, ������� ������ � ���� ������� ������� ������

        if (current == nullptr) //���� ����� ������ ������� ������ �������� ������
            return; //������ ������ ����

        else
        {

            while (current != nullptr) //���� �� ����� �� ����� ������
            {
                current->human.Print(); //������� ������ �������� ��������

                current = current->next; //��������� � ����������
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
        Node* curren = new Node; //�������������� ����������, ������������ ������� ������� ������
        curren->next = head; //��������� ����� ����� ������� - ������
        bool flag = false;

        while (curren != nullptr) //���� �� ����� �� ����� ������
        {
            Node* tmp = curren; //���������� ������� ������� � ��������� 
            curren = curren->next; //���� ������

            if (tmp->human.BirthDay == birthDate) //���� ������ ������������� �����
            {
                flag = true;

                if (tmp->next == nullptr && tmp->prev == nullptr) //���� � ������ ���� �������
                {
                    //������ � ����� = ������� ���������
                    head = nullptr;
                    tail = nullptr;
                }

                else if (tmp == head) // ���� �� � ������
                {
                    head = tmp->next; //������ = ��������� �������
                    head->prev = nullptr;  // ���������� ������� ������ = ������� ���������
                }

                else if (tmp == tail) //���� �� � ������
                {
                    tail = tmp->prev; //����� = ���������� �������
                    tail->next = nullptr; //��������� ������� ����� ������ = ������� ���������
                }

                else //���� � ������ ����� ������
                {
                    tmp->prev->next = tmp->next; //��������� ������� ����������� = ��������� �������
                    tmp->next->prev = tmp->prev; //���������� ������� ����������� = ���������� �������
                }

                delete tmp; //������� ��������� ����������
            }
        }

        return flag;
    }

    int GetSize() //����� ��������� ������� ������
    {
        int counter = 0; //�������

        Node* current = head; //���������� �������� ��������

        while (current != nullptr) //���� �� ����� �� ����� ������
        {
            current = current->next; //��������� �� ��������� �������
            counter++; //����������� �������
        }

        return counter; //���������� �������
    }

    void Write_Into_File(ofstream* f) //����� ��� ������ ������ � ����
    {
        int Size = GetSize();

        f->write((char*) &Size, sizeof(int));

        Node* current = head; //���������� �������� ��������

        while (current != nullptr) //���� �� ����� �� ����� ������
        {
            current->human.WriteIntoFile(f); //���������� ������ �������� �������� � ������
            current = current->next; //��������� �� ��������� �������
        }
    }

    void Read_From_File(ifstream* f) //����� ��� ������������� ������ �� �����
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

    ~List() //����� ������� ������
    {
        while (head != nullptr) //���� �� ����� �� ����� ������
        {
            Node* tmp = head; //���������� ������ �� ��������� ����������
            head = head->next; //������� ������ �������� ������� ����� ������
            delete tmp; //������� ������� �������
        }

        tail = nullptr; //������� ����� ������� ����������
    }
};
