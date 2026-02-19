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

        cout << "Общее колличество студентов: " << school->getStudentsAmmount() << endl;

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
    Students::iterator sIter;

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
                sIter = school->students_begin();

                while(sIter)
                {
                    StudentFormatPrint(sIter);
                    ++sIter;
                }
                inStudentsList();
                break;
            case(search):
                sIter = school->students_begin();

                if(StudentsSearch(sIter, school->students_end()))
                    StudentsEdit(sIter);
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
                sIter = school->students_begin();
                sIter = StudentsSearch(sIter, school->students_end());
                if(sIter)
                    StudentsExclude(sIter);
                else
                    cout << "Студент не найден" << endl;
                break;
        }
    }
}

// ================================================================================= //

void menu::StudentFormatPrint(Students::iterator& studIter) const
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
    cout << (*studIter).visits_arr_size() << endl;

}



// ================================================================================= //

unsigned menu::StudentsAdd()
{
    unsigned groupID;
    char lastname[Students::MAX_NAME_BYTES];

    
    cout << "Фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(lastname, Students::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

   GroupFormatPrint();

    cout << "Введите номер группы или 0 для пропуска: ";
    cin >> groupID;

    unsigned ID = school->push_student(lastname, groupID);
    return ID;
}

// ================================================================================= 

unsigned menu::SudentAddSorted()
{
    unsigned groupID;
    char lastname[Students::MAX_NAME_BYTES];

    cout << "Фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(lastname, Students::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    
    GroupFormatPrint();
    cout << "Введите номер группы или 0 для пропуска: ";
    cin >> groupID;

    enum points {back, visitComparator, lastnameComparator};
    unsigned inputValue = -1;
    unsigned ID;

    while(inputValue)
    {
        cout << "1. С сортировкой по посещениям" << endl;
        cout << "2. С сортировкой по фамилии" << endl;
        cout << "3. Назад" << endl;

        cin >> inputValue;

        switch(inputValue)
        {
        case(back):
            break;
        case(visitComparator):
            Students::visitComparator vCmp;
            ID = school->push_sudent_sorted(vCmp, lastname, groupID);
            inputValue = 0;
            break;
        case(lastnameComparator):
            Students::lastnameComparator lnCmp;
            ID = school->push_sudent_sorted(lnCmp, lastname, groupID);
            inputValue = 0;
            break;
        }
    }
    return ID;
}


// ================================================================================= //

Students::iterator menu::StudentsSearch(const Students::iterator& first, const Students::iterator& last)
{
    char identificator[Students::MAX_NAME_BYTES];
    const char* groupName = nullptr;
    Students::iterator findIter;

    cout << "Введите фамилию или ID студента: ";

    cin.ignore(1000, '\n');
    cin.getline(identificator, Students::MAX_NAME_BYTES);
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;

    

    if(isdigit(*identificator))
    {
        unsigned studentID = atoi(identificator);
        findIter = SchoolAlg::search(first, last, Students::idComparator(), studentID);
        if(findIter)
        {
            Groups::iterator gIter = SchoolAlg::search
                (school->groups_begin(), school->groups_end(), Groups::idComparator(), (*findIter).groupID);

            if(gIter)
                groupName = (*gIter).name;

            cout << (*findIter).ID << " - ";
            cout << (*findIter).lastname << " - ";
            cout << ((groupName)? groupName: "Нет группы") << " - ";
            cout << (*findIter).visits_arr_size() << endl; 

            return findIter;        
        }
        else
        {
            return findIter;
        }
        
    }
    else
    {
        int counter = 0;
        findIter = first;        
        Students::iterator singleFindIter;

        while(findIter)
        {
            findIter = SchoolAlg::search(findIter, last, Students::lastnameComparator(), identificator);
            if(findIter)
            {
                if(counter == 0)
                    singleFindIter = findIter;

                Groups::iterator gIter = 
                    SchoolAlg::search(school->groups_begin(), school->groups_end(),
                                      Groups::idComparator(), (*findIter).groupID);
                
                if(gIter)
                    groupName = (*gIter).name;

                cout << (*findIter).ID << " - ";
                cout << (*findIter).lastname << " - ";
                cout << ((groupName)? groupName: "Нет группы") << " - ";
                cout << (*findIter).visits_arr_size() << endl;
                counter++;
                findIter++;
            }
            
        }

        if(counter == 1)
        {
            return singleFindIter;
        }
        else if(counter > 1)
        {
            unsigned studentID;
            cout << "Найдено несколько совпадений." << endl;
            cout << "Введите ID: ";
            cin >> studentID;

            findIter = SchoolAlg::search(first, last, Students::idComparator(), studentID);
            
            return findIter;
        }
        else
        {
            return findIter;
        }

    }
}

// ================================================================================= //

void menu::StudentsEdit(Students::iterator& sIter)
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
            StudentsEditGroup(sIter);
            break;
        case(changeLastname):
            StudentsEditLastname(sIter);
            break;
        case(exclude):
            StudentsExclude(sIter);
            break;
        }
    }
}

// ================================================================================= //

void menu::StudentsEditLastname(Students::iterator& sIter)
{
    char newLastname[Students::MAX_NAME_BYTES];

    
    cout << "Новая фамилия: ";
    cin.ignore(1000, '\n');
    cin.getline(newLastname, Students::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;

    size_t sLen = strlen(newLastname) + 1;
    char* lastname; 
    if(sLen <= Students::MAX_NAME_BYTES)
    {
        lastname = new char[sLen];
        strcpy(lastname, newLastname);

        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix((*sIter).lastname, Students::MAX_NAME_BYTES);
        lastname[safePrefix] = '\0';
    }
    else
    {
        lastname = new char[Students::MAX_NAME_BYTES];
        strncpy(lastname, newLastname, Students::MAX_NAME_BYTES);
        
        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix((*sIter).lastname, Students::MAX_NAME_BYTES);
        lastname[safePrefix] = '\0';
    }        

    delete (*sIter).lastname;
    (*sIter).lastname = lastname;
}

// ================================================================================= //
// Добавить проверку на группу
bool menu::StudentsEditGroup(Students::iterator& sIter)
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
    Students::iterator sIter;

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
            school->sort_students(Students::lastnameComparator()); // не работает со значением по умолчанию??
            sIter = school->students_begin();

            cout << "ID - lastname - group - visits" << endl;
            while(sIter)
            {
                StudentFormatPrint(sIter);
                sIter++;
            }
            break;
        case(sortVisits):
            school->sort_students(Students::visitComparator()); // не работает со значением по умолчанию??
            sIter = school->students_begin();

            cout << "ID - lastname - group - visits" << endl;
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

void menu::StudentsExclude(Students::iterator& sIter)
{
    school->pop_student(sIter);
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
    char name[Groups::MAX_NAME_BYTES];
    
    cout << "Название группы: ";
    cin.ignore(1000, '\n');
    cin.getline(name, Groups::MAX_NAME_BYTES);
    // Отчистка буфера!
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    unsigned groupID;
    try
    {
        groupID = school->push_group(name);
        return groupID;
    }
    catch(SchoolExeptions& err)
    {
        cout << err.what() << endl;

        enum points{back};
        unsigned inputValue = -1;

        while(inputValue)
        {
            cout << "0. Назад" << endl;

            cin >> inputValue;
            
            switch(inputValue)
            {
            case(back):
                return 0;
            }
        }
    

    return groupID;
    }
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
        try
        {
            school->pop_group(gIter);
            return true;
        }
        catch(NotEmpty&)
        {
            cout << "Группа не пустая." << endl;           

            enum points{back, disband};
            unsigned inputValue = -1;

            while(inputValue)
            {
                cout << "0. Назад" << endl;
                cout << "1. Распустить группу" << endl;

                switch(inputValue)
                {
                case(back):
                    inputValue = 0;
                    break;
                case(disband):
                    Students::iterator sIter = school->students_begin();
                    while(sIter)
                    {
                        if((*sIter).groupID == groupID)
                            (*sIter).groupID = 0;

                        sIter++;
                    }

                    school->pop_group(gIter);
                    return true;
                }
            }
        
        
        }
    
    return false;
    }
}

void menu::GroupFormatPrint() const
{
    Groups::iterator gIter = school->groups_begin();
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
    Students::iterator sIter; 
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
            sIter = school->students_begin();

            while(sIter)
            {
                if((*sIter).has_day(visitDay))
                {
                    cout << (*sIter).ID << " - ";
                    cout << (*sIter).lastname << " - ";
                    cout << (*sIter).groupID << endl;
                    cout << (*sIter).visits_arr_size() << endl;
                }

                ++sIter;
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
    Students::iterator sIter;

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
            sIter = school->students_begin();
            while(sIter)
            {
                StudentFormatPrint(sIter);       
                ++sIter;
            }
            
            break;
        case(add):
            sIter = school->students_begin();

            if(StudentsSearch(sIter, school->students_end()))
            {

                // цикл пока не true, в InputVisits обработка исключения - валидация ввода
                VisitsInputDate(day, mounth);
                visitDay = dateConventer.DateToDay(day, mounth);
                school->push_visit(sIter, visitDay);
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
    Students::iterator sIter = school->students_begin();

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

    while(sIter)
    {
        if((*sIter).groupID == groupID)
            school->push_visit(sIter, visitDay);

        ++sIter;
    }

    return true;
}

void menu::VisitsFormatShow(const unsigned& day) const
{
    Students::iterator sIter = school->students_begin();
    while(sIter)
    {
        for(unsigned i = 0; i < (*sIter).visits_arr_size(); ++i)
        {
            if((*sIter).has_day(day))
            {
                cout << (*sIter).ID << ". " << (*sIter).lastname << endl;
                return;
            }
        }

        ++sIter;
    }
}