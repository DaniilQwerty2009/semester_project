#include "menu.h"

// cin.tie(cout&);????


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
    enum point {back, list, search, add, addSorted, pop};
    unsigned inputValue = -1;
    School::iterator iter;

    while(inputValue != 0)
    {
        cout << "1. Список студентов" << endl;
        cout << "2. Поиск студента" << endl;
        cout << "3. Новый студент " << endl;
        cout << "4. Новый студент (с сохранением сортировки)" << endl;
        cout << "5. Исключить студента " << endl;
        cout << "0. Назад " << endl;

        cin >> inputValue;

        switch(inputValue)
        {
            case(back):
                break;
            case(list):
                iter = school->begin();

                while(iter)
                {
                    StudentFormatPrint(iter);
                    ++iter;
                }
                inStudentsList();
                break;
            case(search):
                iter = school->begin();

                if(StudentsSearch(iter))
                    StudentsEdit(iter);
                else
                    cout << "Совпадений не найдено" << endl;
                break;
            case(add):
                StudentsAdd();
                break;
            case(addSorted):
                SudentAddSorted();
                break;
            case(pop):
                iter = school->begin();
                if(StudentsSearch(iter))
                    StudentsExclude(iter);
                else
                    cout << "Студент не найден" << endl;
                break;
        }
    }
}

// ================================================================================= //

void menu::StudentFormatPrint(School::iterator& studIter) const
{
    Groups::iterator gIter = school->groups_begin();
    const char* groupName = nullptr;

    while(gIter)
    {
        if((*gIter).ID == (*studIter).groupID)
        {
            groupName = (*gIter).name;
            break;
        }

        gIter++;
    }

    cout << (*studIter).ID << " - ";
    cout << (*studIter).lastname << " - ";
    cout << ((groupName)? groupName: "Нет группы") << " - ";
    cout << (*studIter).visits << endl;

}



// ================================================================================= //

unsigned menu::StudentsAdd()
{
    unsigned groupID;
    char lastname[Student::MAX_NAME_BYTES];

    
    cout << "Фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(lastname, Student::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

   GroupFormatPrint();

    cout << "Введите номер группы или 0 для пропуска: ";
    cin >> groupID;

    unsigned ID = school->push_back(lastname, groupID);
    return ID;
}

// ================================================================================= 

unsigned menu::SudentAddSorted()
{
    unsigned groupID;
    char lastname[Student::MAX_NAME_BYTES];

    cout << "Фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(lastname, Student::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    
    GroupFormatPrint();
    cout << "Введите номер группы или 0 для пропуска: ";
    cin >> groupID;

    enum points {back, byVisits, byLastname};
    unsigned inputValue = -1;

    while(inputValue)
    {
        cout << "выберите признак вставки" << endl;
        cout << "1. По посещениям" << endl;
        cout << "2. По фамилии" << endl;
        cout << "3. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(byVisits):
            School::ByVisits cmpV;
            groupID = school->push_sorted(cmpV, lastname, groupID);
            return groupID;
        case(byLastname):
            School::ByLastname cmpN;
            groupID = school->push_sorted(cmpN, lastname, groupID);
            return groupID;
        }
    }
    return groupID;
}


// ================================================================================= //

bool menu::StudentsSearch(School::iterator& sIter)
{
    char identificator[Student::MAX_NAME_BYTES];
    const char* groupName = nullptr;

    cout << "Введите фамилию или ID студента: ";

    cin.ignore(1000, '\n');
    cin.getline(identificator, Student::MAX_NAME_BYTES);
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
    
    if(isdigit(*identificator))
    {
        unsigned studentID = atoi(identificator);
        if(SchoolAlg::search(sIter, school->end(), IDCompare, studentID))
        {
            Groups::iterator gIter = SchoolAlg::search
                (school->groups_begin(), school->groups_end(), Groups::idComparator(), (*sIter).groupID);
            
            if(gIter)
                groupName = (*gIter).name;

            cout << (*sIter).ID << " - ";
            cout << (*sIter).lastname << " - ";
            cout << ((groupName)? groupName: "Нет группы") << " - ";
            cout << (*sIter).visits << endl; 

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
        while(sIter)
        {
            if(SchoolAlg::search(sIter, school->end(), lastnameCompare, identificator))
            {
                if(counter == 0)
                    finded = sIter;

                Groups::iterator gIter = 
                    SchoolAlg::search(school->groups_begin(), school->groups_end(),
                                      Groups::idComparator(), (*sIter).groupID);
                
                if(gIter)
                    groupName = (*gIter).name;

                cout << (*sIter).ID << " - ";
                cout << (*sIter).lastname << " - ";
                cout << ((groupName)? groupName: "Нет группы") << " - ";
                cout << (*sIter).visits << endl;
                counter++;
                sIter++;
            }
            
        }
        sIter = finded;

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

            SchoolAlg::search(sIter, school->end(), IDCompare, studentID);
            
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
        cout << "3. Исключить" << endl;
        cout << "0. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(changeGroup):
            GroupFormatPrint();
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
    char newLastname[Student::MAX_NAME_BYTES];

    
    cout << "Новая фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(newLastname, Student::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;

    strncpy((*iter).lastname, newLastname, Student::MAX_NAME_BYTES);
}

// ================================================================================= //
// Добавить проверку на группу
bool menu::StudentsEditGroup(School::iterator& sIter)
{
    unsigned groupID;

    cout << "Введите номер группы или 0 для исключения из группы: ";
    cin >> groupID;

    if(groupID == 0)
    {
        (*sIter).groupID = groupID;
        return true;
    }


    Groups::iterator gIter = 
        SchoolAlg::search(school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);

    if(!gIter)
    {
        cout << "Группа не найдена." << endl;
        return false;
    }

    (*sIter).groupID = groupID;
    return true;
}

// ================================================================================= //

// редактиррование, сортировка, добавление
void menu::inStudentsList()
{
    enum point {back, sortLastname, sortVisits, add, pop};
    short inputValue = -1;
    School::iterator sIter;

    while(inputValue)
    {
        cout << "1. Сортировка по имени" << endl;
        cout << "2. Сортировка по посещениям " << endl;
        cout << "0. Назад " << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(sortLastname):
            school->sort(School::ByLastname()); // не работает со значением по умолчанию??
            sIter = school->begin();

            cout << "ID - lastname - group - visits" << endl;
            while(sIter)
            {
                StudentFormatPrint(sIter);
                sIter++;
            }
            break;
        case(sortVisits):
            school->sort(School::ByVisits());
            sIter = school->begin();
            while(sIter)
            {
                StudentFormatPrint(sIter);
                sIter++;
            }
            break;
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
            GroupFormatPrint();
            break;
        case(create):
            createGroup();
            break;
        case(pop):
            GroupFormatPrint();
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
    char name[Student::MAX_NAME_BYTES];
    
    cout << "Название группы: ";
    cin.ignore(1000, '\n');
    cin.getline(name, Student::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // pushSorted???
    unsigned groupID = school->push_group(name);

    return groupID;
}

bool menu::deleteGroup()
{
    unsigned groupID;

    cout << "Введите номер группы: ";
    cin >> groupID;

    Groups::iterator gIter = 
        SchoolAlg::search(school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);

    if(gIter)
    {
        school->pop_group(*gIter);
    }
        return true;
    
    return false;
}

void menu::GroupFormatPrint() const
{
     Groups::iterator gIter = school->groups_begin();
    cout << gIter << endl; //?????
    if(gIter)
        cout << "ID   Name" << endl;
    while(gIter)
    {
        cout << (*gIter).ID << " " << (*gIter).name << endl;
        gIter++; 
    }

}


// ================================================================================= //
        // IN_VISITS
// ================================================================================= //

void menu::inVisits()
{
    enum point {back, add, addToGroup, showByDay};
    short inputValue = -1;
    School::iterator iter; 
    unsigned day, mounth, visitDay;

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
            GroupVisitAdd();
            break;
        case(showByDay):
            VisitsInputDate(day, mounth);
            visitDay = dateConventer.DateToDay(day, mounth);
            iter = school->begin();

            while(iter)
            {
                if((*iter).hasDay(visitDay))
                {
                    cout << (*iter).ID << " - ";
                    cout << (*iter).lastname << " - ";
                    cout << (*iter).groupID << endl;
                    cout << (*iter).visits << endl;
                }

                ++iter;
            }

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
    School::iterator sIter;

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
            sIter = school->begin();
            while(sIter)
            {
                StudentFormatPrint(sIter);       
                ++sIter;
            }
            
            break;
        case(add):
            sIter = school->begin();

            if(StudentsSearch(sIter))
            {

                // цикл пока не true, в InputVisits обработка исключения - валидация ввода
                VisitsInputDate(day, mounth);
                visitDay = dateConventer.DateToDay(day, mounth);
                school->push_visit(&(*sIter), visitDay);
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

bool menu::GroupVisitAdd()
{
    unsigned groupID, day, mounth, visitDay;
    School::iterator iter = school->begin();

    GroupFormatPrint();

    cout << "Ведите номер группы: ";
    cin >> groupID;

    Groups::iterator gIter = SchoolAlg::search
        (school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);
    
    if(!gIter)
    {
        cout << "Группа не найдена." << endl;
        return false;
    }

    VisitsInputDate(day, mounth);
    visitDay = dateConventer.DateToDay(day, mounth);

    while(iter)
    {
        if((*iter).groupID == groupID)
            school->push_visit(&(*iter), visitDay);

        ++iter;
    }

    return true;
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