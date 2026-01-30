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
    enum point {back, show, edit, add, pop};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {
        cout << "1. Список студентов" << endl;
        cout << "2. Редактировать" << endl;
        cout << "3. Добавить " << endl;
        cout << "4. Исключить " << endl;
        cout << "0. Назад " << endl;

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
    cin.ignore(1000, '\n');
    cin.getline(lastname, Student::MAX_NAME_LEN);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    

    cout << endl;
    cout << "Введите ID группы: ";
    cin >> groupID;
    cin.ignore(1000, '\n');

    // pushSorted???
    school->push_back(lastname, groupID);
}

void menu::StudentsEdit()
{
    enum point {back, name, group};
    short inputValue = -1;

    while(inputValue != 0)
    {
        cout << "1. Изменить фамилию " << endl;
        cout << "2. Изменить группу " << endl;
        cout << "3. Назад " << endl;

        switch(inputValue)
        {
        case(back):
            break;
        case(name):
            cout << "Введите фамилию или ID студента: ";

            StudentsEditLastname();
            break;
        }
    }

}

void menu::StudentsEditLastname()
{
    unsigned groupID;
    char lastname[Student::MAX_NAME_LEN];

    
    cout << "Новая фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(lastname, Student::MAX_NAME_LEN);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

}