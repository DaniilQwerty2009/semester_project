#include "menu.h"


// Пункты отдельно в enum?
void menu::init(School* school)
{
    this->school = school;

    enum point {exit, students};

    while(inputValue != 0)
    {
        cout << "Учет посещаемости индивидуальных и коллективных занятий" << endl;

        cout << "Общее колличество студентов: " << school->getCapacity() << endl;

        cout << "1. Cтуденты" << endl;

        cout << "0. Выход" << endl;


        switch(inputValue)
        {
        case(point::exit):
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

    while(inputValue != 0)
    {
        switch(inputValue)
        {
            case(back):
                break;
            case(show):
                StudentsFormatShow();
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
    }
}

void menu::StudentsAdd()
{
    unsigned studentID, groupID;
    char lastname[Student::MAX_NAME_LEN];

    cout << "Введите ID: " << endl;
    
    

    // pushSorted???
    school->push_back(studentID, lastname, groupID);
}