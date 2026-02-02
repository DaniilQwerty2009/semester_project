#include "menu.h"

// cin.tie(cout&);????

// Пункты отдельно в enum?
void menu::init(School* school)
{
    this->school = school;

    enum point {exit, students, groups, visits};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {
        cout << "Учет посещаемости индивидуальных и коллективных занятий" << endl;

        cout << "Общее колличество студентов: " << school->getCapacity() << endl;

        cout << "1. Cтуденты" << endl;

        cout << "2. Группы " << endl;

        cout << "3. Посещения" << endl;

        cout << "0. Выход" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(point::exit):
            cout << "Завершение работы" << endl;
            break;

        case(point::groups):
            inGroup();
            break;
        case(point::students):
            inStudents();
            break;

        case(point::visits):
            inVisits();
            break;
            
            
        }


    }
}

// ================================================================================= //
        // IN_STUDENTS
// ================================================================================= //

void menu::inStudents()
{
    enum point {back, list, search};
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
            case(list):
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

void menu::StudentsFormatShow() const
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
    enum point {back, changeGroup, changeLastname, exclude};
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
        case(exclude):
            StudentsExclude(iter);
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
// Добавить проверку на группу
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
    school->pop(&(*iter));
}

// ================================================================================= //
        // IN_GROUPS
// ================================================================================= //

void menu::inGroup()
{
    enum point {back, list, create, pop};
    unsigned inputValue = -1;


    while(inputValue)
    {
        cout << "1. Список груп" << endl;
        cout << "2. Создать группу" << endl;
        cout << "3. Удалить группу" << endl;
        cout << "0. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(list):
            GroupFormatShow();
            break;
        case(create):
            createGroup();
            break;
        case(pop):
            deleteGroup();
            break;
        case(back):
            break;                
        }
    }
}

// ================================================================================= //

unsigned menu::createGroup()
{
    char name[Student::MAX_NAME_LEN];

    
    cout << "Название группы: ";
    cin.ignore(1000, '\n');
    cin.getline(name, Student::MAX_NAME_LEN);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // pushSorted???
    unsigned ID = school->createGroup(name);

    return ID;
}

bool menu::deleteGroup()
{
    char name[Student::MAX_NAME_LEN];

    
    cout << "Название группы: ";
    cin.ignore(1000, '\n');
    cin.getline(name, Student::MAX_NAME_LEN);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    Group* ptr = school->groupsMap;

    while(ptr)
    {
        if( !strcmp(ptr->value, name))
            break;

        ptr = ptr->next;
    }

    if(ptr)
    {
        school->deleteGroup(ptr);
        return true;
    }
    else
        return false;

}

void menu::GroupFormatShow() const
{
    Group* ptr = school->groupsMap;
    cout << "ID - name" << endl;
    while(ptr)
    {
        cout << ptr->key << " - " << ptr->value << endl;
        ptr = ptr->next;
    }
}

// ================================================================================= //
        // IN_VISITS
// ================================================================================= //

void menu::inVisits()
{
    enum point {back, add, addToGroup, showByDay};
    short inputValue = -1;
    // School::iterator iter = school->begin(); 

    while(inputValue)
    {
        cout << "1. Отметить студента" << endl;
        cout << "2. Отметить группу" << endl;
        cout << "3. Посещения по дате" << endl;
        cout << "0. Назад" << endl;


        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(add):
            InPersonalVisitAdd();
            break;
        case(addToGroup):
            break;
        case(showByDay):
            break;
        }
    }
}

bool menu::VisitsInputDate(unsigned& day, unsigned& mounth)
{
    enum point {back};
    short inputValue = -1;




    cout << "Введите день и месяц в числовом формате" << endl;
    cout << "Для выхода введите 0" << endl;


    cout << "День: ";
    cin >> inputValue;
    // проверка на влдиность - dateConverter генерирует exeption

    if(inputValue == 0)
        return false;

    day = inputValue;

    cout << "Месяц: ";
    cin >> inputValue;
    // проверка на влдиность - dateConverter генерирует exeption

    if(inputValue == 0)
        return false;

    mounth = inputValue;

    return true;

    
}

void menu::InPersonalVisitAdd()
{
    enum point {back, list, add};
    short inputValue = -1;
    unsigned day, mounth, visitDay;
    School::iterator iter = school->begin();


    while(inputValue)
    {
        cout << "1. Список студентов" << endl;
        cout << "2. Отметить студента" << endl;
        cout << "0. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(list):
            StudentsFormatShow();
            break;
        case(add):
            if(StudentsSearch(iter))
            {

                // цикл пока не true, в InputVisits обработка исключения - валидация ввода
                VisitsInputDate(day, mounth);
                visitDay = dateConventer.DateToDay(day, mounth);
                school->addVisit(&(*iter), visitDay);
                break;
            }
            else
            {
                cout << "Совпадений не найдено" << endl;
                break;
            }
        }
    }
}

void menu::VisitsFormatShow(const unsigned& day) const
{
    School::iterator iter = school->begin();
    while(iter)
    {
        for(unsigned i = 0; i < (*iter).visits; ++i)
        {
            if((*iter).hasDay(day))
            {
                cout << (*iter).ID << ". " << (*iter).lastname << endl;
                return;
            }
        }

        ++iter;
    }
}