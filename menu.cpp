#include "menu.h"

// cin.tie(cout&);????

// Пункты отдельно в enum?
void menu::init(School* school)
{
    this->school = school;

    enum point {exit, students, visits};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {
        cout << "Учет посещаемости индивидуальных и коллективных занятий" << endl;

        cout << "Общее колличество студентов: " << school->getCapacity() << endl;

        cout << "1. Cтуденты" << endl;

        cout << "2. Посещения" << endl;

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

        case(point::visits):
            
            
        }


    }
}

// ================================================================================= //
        // IN_STUDENTS
// ================================================================================= //

void menu::inStudents()
{
    enum point {back, show, search};
    unsigned inputValue = -1;
    School::iterator iter;

    while(inputValue != 0)
    {
        cout << "1. Список студентов" << endl;
        cout << "2. Поиск студента" << endl;
        cout << "0. Назад " << endl;

        cin >> inputValue;

        switch(inputValue)
        {
            case(back):
                break;
            case(show):
                StudentsFormatShow();
                inStudentsList();
                break;
            case(search):
                iter = school->begin();

                if(StudentsSearch(iter))
                    StudentsEdit(iter);
                else
                    cout << "Совпадений не найдено" << endl;
                break;
        }

    }
}

// ================================================================================= //

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

// ================================================================================= //

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

    // pushSorted???
    school->push_back(lastname, groupID);
}

// ================================================================================= //

bool menu::StudentsSearch(School::iterator& iter)
{
    char identificator[Student::MAX_NAME_LEN];

    cout << "Введите фамилию или ID студента: ";

    cin.ignore(1000, '\n');
    cin.getline(identificator, Student::MAX_NAME_LEN);
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
    
    if(isdigit(*identificator))
    {
        unsigned studentID = atoi(identificator);
        if(SchoolAlg::search(iter, IDCompare, studentID))
        {
            cout << (*iter).ID << " - ";
            cout << (*iter).lastname << " - ";
            cout << (*iter).groupID << " - ";
            cout << (*iter).visits << endl; 

            return true;        
        }
        else
        {
            return false;
        }
        
    }
    else
    {
        int counter = 0;
        School::iterator finded;
        while(iter)
        {
            if(SchoolAlg::search(iter, lastnameCompare, identificator))
            {
                if(counter == 0)
                    finded = iter;

                cout << (*iter).ID << " - ";
                cout << (*iter).lastname << " - ";
                cout << (*iter).groupID << " - ";
                cout << (*iter).visits << endl;
                counter++;
                iter++;
            }
            
        }
        iter = finded;

        if(counter == 1)
        {
            return true;
        }
        else if(counter > 1)
        {
            unsigned studentID;
            cout << "Найдено несколько совпадений." << endl;
            cout << "Введите ID: ";
            cin >> studentID;

            SchoolAlg::search(iter, IDCompare, studentID);
            
            return true;
        }
        else
        {
            return false;
        }

    }
}

// ================================================================================= //

void menu::StudentsEdit(School::iterator& iter)
{  
    enum point {back, changeGroup, changeLastname};
    short inputValue = -1;

    while(inputValue)
    {    
        cout << "1. Изменить группу" << endl;
        cout << "2. Изменить фамилию" << endl;
        cout << "0. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(changeGroup):
            StudentsEditGroup(iter);
            break;
        case(changeLastname):
            StudentsEditLastname(iter);
            break;
        }
    }
}

// ================================================================================= //

void menu::StudentsEditLastname(School::iterator& iter)
{
    char newLastname[Student::MAX_NAME_LEN];

    
    cout << "Новая фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(newLastname, Student::MAX_NAME_LEN);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;

    strncpy((*iter).lastname, newLastname, Student::MAX_NAME_LEN);
}

// ================================================================================= //

void menu::StudentsEditGroup(School::iterator& iter)
{
    cout << "Новая группа: ";
    cin >> (*iter).groupID;
}

// ================================================================================= //

// редактиррование, сортировка, добавление
void menu::inStudentsList()
{
    enum point {back, sortLastname, sortVisits, add, pop};
    short inputValue = -1;
    School::iterator iter;

    while(inputValue)
    {
        cout << "1. Сортировка по имени" << endl;
        cout << "2. Сортировка по посещениям " << endl;
        cout << "3. Новый студент " << endl;
        cout << "4. Исключить студента " << endl;
        cout << "0. Назад " << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(sortLastname):
            school->sort(School::ByLastname()); // не работает со значением по умолчанию??
            StudentsFormatShow();
            break;
        case(sortVisits):
            school->sort(School::ByVisits());
            StudentsFormatShow();
            break;
        case(add):
            StudentsAdd();
            break;
        case(pop):
            iter = school->begin();
            if(StudentsSearch(iter))
                StudentsExclude(iter);
            else
                cout << "Студент не найден" << endl;
        

        }
    }
}

// ================================================================================= //

void menu::StudentsExclude(School::iterator& iter)
{
    school->pop(*iter);
}

// ================================================================================= //
        // IN_VISITS
// ================================================================================= //

void menu::inVisits()
{
    enum point {back, add, addToGroup, showDay, showPeriod};
}