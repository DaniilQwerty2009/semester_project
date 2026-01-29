#include "menu.h"

// cin.tie(cout&);????

// Пункты отдельно в enum?
void menu::init(School* school)
{
    this->school = school;

    enum point {exit, students};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {
        cout << "Учет посещаемости индивидуальных и коллективных занятий" << endl;

        cout << "Общее колличество студентов: " << school->getCapacity() << endl;

        cout << "1. Cтуденты" << endl;

        cout << "0. Выход" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(point::exit):
            cout << "Завершение работы" << endl;
            break;
        
        case(point::students):
            inStudents();
            break;
            
        }


    }
}



void menu::inStudents()
{
    enum point {back, show, edit, add};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {
        cout << "1. Список студентов" << endl;
        cout << "2. Редактировать" << endl;
        cout << "3. Добавить " << endl;
        cout << "0. Выход " << endl;

        cin >> inputValue;

        switch(inputValue)
        {
            case(back):
                break;
            case(show):
                StudentsFormatShow();
                // inStudentsList(); - редактиррование по ID, сортировка, добавление
                break;
            case(edit):
                break;
            case(add):
                StudentsAdd();
        }

    }
}


void menu::StudentsFormatShow()
{
    School::iterator iter(school->begin());

    cout << "ID - lastname - groupID - visits" << endl;

    while(iter)
    {
        cout << (*iter).ID << " - ";
        cout << (*iter).lastname << " - ";
        cout << (*iter).groupID << " - ";
        cout << (*iter).visits << endl;

        ++iter;
    }
}

void menu::StudentsAdd()
{
    unsigned groupID;
    char lastname[Student::MAX_NAME_LEN];

    
    cout << "Фамилия: ";
    cin.get(lastname, Student::MAX_NAME_LEN);
    // Отчистка буфера!

    

    cout << endl;
    cout << "Введите ID группы: ";
    cin >> groupID;


    

    // pushSorted???
    school->push_back(lastname, groupID);
}