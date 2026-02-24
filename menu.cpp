#include "menu.h"
#include <iomanip>

// cin.tie(cout&);????


void menu::init(School* school)
{
    this->school = school;

    enum point {exit, students, groups, visits, save};
    unsigned inputValue = -1;

    while(inputValue != 0)
    {   
        std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Учет посещаемости индивидуальных и коллективных занятий" << endl;

        cout << "Общее колличество студентов: " << school->get_students_ammount() << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "1. Cтуденты" << endl;

        cout << "2. Группы " << endl;

        cout << "3. Посещения" << endl;

        cout << "4. Сохранить" << endl;

        cout << "0. Сохранить и выйти" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        
        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

        switch(inputValue)
        {
        case(point::exit):
            cout << "Завершение работы" << endl;
            break;

        case(point::groups):
            in_Groups();
            break;
        case(point::students):
            in_Students();
            break;

        case(point::visits):
            in_Visits();
            break;

        case(point::save):
            school->save();
            break;

        default:
            break;            
        }


    }
}

// ================================================================================= //
        // IN_STUDENTS
// ================================================================================= //

void menu::in_Students()
{
    enum point {back, list, search, add, addSorted, pop};
    short inputValue = -1;
    Students::iterator sIter;

    while(inputValue != 0)
    {
        std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "1. Список студентов" << endl;
        cout << "2. Поиск студента" << endl;
        cout << "3. Новый студент " << endl;
        cout << "4. Новый студент (с сохранением сортировки)" << endl;
        cout << "5. Исключить студента " << endl;
        cout << "0. Назад " << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

        switch(inputValue)
        {
            case(back):
                break;
            case(list):
                in_Students_list();
                break;
            case(search):
                sIter = Student_search(school->students_begin(), school->students_end());
                if(sIter)
                {
                    std::cout << "\033[2J\033[H";

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                    cout << "ID";
                    cout << std::setw(6) << std::setfill(' ') << ' ';
                    cout << "Имя";
                    cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
                    cout << "Группа";
                    cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
                    cout << "Посещений" << endl;
                    Student_format_print(sIter);
                    cout << endl;
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    if((*sIter).visits_arr_size())
                    {
                        unsigned dayOfMounth, mounth;
                        const unsigned* visits = (*sIter).get_visits_arr();
                        cout << "Даты посещений:" << endl;
                        
                        for(size_t i = 0; i < (*sIter).visits_arr_size(); ++i)
                        {
                            dateConventer.day_to_date(visits[i], dayOfMounth, mounth);
                            cout << dayOfMounth << ' ' << dateConventer.monthName[mounth-1] << endl;
                        }

                        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                    }

                    cout << "1. Редактировать студента" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Ввод: ";
                    cin >> inputValue;

                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        inputValue = -1;
                    }

                    switch(inputValue)
                    {
                    case(1):
                        Student_edit(sIter);
                        break;
                    case(0):
                        inputValue = -1;
                        break;
                    }
                }
                else
                {
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Совпадений не найдено" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Ввод: ";
                    cin >> inputValue;
                    inputValue = -1;
                }
                break;
            case(add):
                Student_add();
                break;
            case(addSorted):
                Student_add_sorted();
                break;
            case(pop):
                sIter = Student_search(school->students_begin(), school->students_end());
                if(sIter)
                    Students_exclude(sIter);
                else
                {
                    std::cout << "\033[2J\033[H";
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Студент не найден" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Ввод: ";
                    cin >> inputValue;
                    inputValue = -1;
                }
                break;
            default:
                break;
        }
    }
}

// ================================================================================= //

void menu::Student_format_print(Students::iterator& studIter) const
{
    Groups::iterator gIter = school->groups_begin();
    const char* groupName = nullptr;
    size_t fillLen;

    while(gIter)
    {
        if((*gIter).ID == (*studIter).groupID)
        {
            groupName = (*gIter).name;
            break;
        }
        ++gIter;
    }



    cout << (*studIter).ID;
    cout << std::setw(4) << std::setfill('.') << '.';

    fillLen = (Students::MAX_NAME_BYTES - strlen((*studIter).lastname)) / 2;
    cout  << (*studIter).lastname;
    cout << std::setw(fillLen) << std::setfill('.') << '.';

    fillLen = (Groups::MAX_NAME_BYTES - strlen((groupName ? groupName : "Нет группы"))) / 2;
    cout << (groupName ? groupName : "Нет группы");
    cout << std::setw(fillLen) << std::setfill('.') << '.';

    cout << (*studIter).visits_arr_size();
}



// ================================================================================= //

unsigned menu::Student_add()
{
    short inputValue = -1;
    unsigned groupID;
    char lastname[Students::MAX_NAME_BYTES];

    bool correctNameFlag = false;
    while(!correctNameFlag)
    {
        std::cout << "\033[2J\033[H";
        
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Добавление студента" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Фамилия: ";
        cin.ignore(1000, '\n');
        cin.getline(lastname, Students::MAX_NAME_BYTES);

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        size_t i = 0;
        for(; i < strlen(lastname) && i < Students::MAX_NAME_BYTES-1; ++i)
        {
            if(isdigit(lastname[i]))
            {
                enum {cancel, repeat};

                std::cout << "\033[2J\033[H";
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Не верный формат имени" << endl;
                cout << "1. Повторить ввод" << endl;
                cout << "0. Отменить" << endl;

                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Ввод: ";
                cin >> inputValue;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    inputValue = 0;
                }

                switch(inputValue)
                {
                case(cancel):
                    return 0;
                case(repeat):
                    break;
                default:
                    break;
                }
                break;
            }
        }
        if(i == strlen(lastname) || i == Students::MAX_NAME_BYTES-1)    // прошли все слово
                correctNameFlag = true;
    }

    Groups::iterator   gIter = school->groups_begin();

    std::cout << "\033[2J\033[H";
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    
    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Группа" << endl;

    while(gIter)
    {
        Group_format_print(gIter);
        cout << endl;
        gIter++;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Номер группы (для пропуска введите 0): ";
    cin >> groupID;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        groupID = 0;
    }


    unsigned ID = school->push_student(lastname, groupID);
    return ID;
}

// ================================================================================= 

unsigned menu::Student_add_sorted()
{
    unsigned groupID;
    short inputValue = -1;
    char lastname[Students::MAX_NAME_BYTES];

    
    bool correctNameFlag = false;
    while(!correctNameFlag)
    {
        std::cout << "\033[2J\033[H";
        
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Добавление студента" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Фамилия: ";
        cin.ignore(1000, '\n');
        cin.getline(lastname, Students::MAX_NAME_BYTES);

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        size_t i = 0;
        for(; i < strlen(lastname) && i < Students::MAX_NAME_BYTES-1; ++i)
        {
            if(isdigit(lastname[i]))
            {
                enum {cancel, repeat};

                std::cout << "\033[2J\033[H";
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Не верный формат имени" << endl;
                cout << "1. Повторить ввод" << endl;
                cout << "0. Отменить" << endl;

                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Ввод: ";
                cin >> inputValue;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    inputValue = 0;
                }

                switch(inputValue)
                {
                case(cancel):
                    return 0;
                case(repeat):
                    break;
                default:
                    break;
                }
                break;
            }
        }
        if(i == strlen(lastname) || i == Students::MAX_NAME_BYTES-1)    // прошли все слово
                correctNameFlag = true;
    }
    
    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    
    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Группа";
    cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';

    
    Groups::iterator   gIter = school->groups_begin();
    while(gIter)
    {
        Group_format_print(gIter);
        cout << endl;
        gIter++;
    }
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Введите номер группы или 0 для пропуска: ";
    cin >> groupID;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        groupID = 0;
    }

    enum points {back, visitComparator, lastnameComparator};
    unsigned ID;

    while(inputValue)
    {
        std::cout << "\033[2J\033[H";
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        
        cout << "1. С сортировкой по посещениям" << endl;
        cout << "2. С сортировкой по фамилии" << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

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
        default:
            break;
        }
    }
    return ID;
}


// ================================================================================= //

Students::iterator menu::Student_search(const Students::iterator& first, const Students::iterator& last)
{
    char identificator[Students::MAX_NAME_BYTES];
    Students::iterator findIter;

    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Введите фамилию или ID студента: ";

    cin.ignore(1000, '\n');
    cin.getline(identificator, Students::MAX_NAME_BYTES);
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
    

    if(isdigit(*identificator))
    {
        unsigned studentID = atoi(identificator);
        findIter = SchoolAlg::search(first, last, Students::idComparator(), studentID);
        
        return findIter;        
        
    }
    else
    {
        size_t counter = 0;
        Students::iterator findedArr[school->get_students_ammount()];
        findIter = first;

        while(findIter)
        {
            findIter = SchoolAlg::search(findIter, last, Students::lastnameComparator(), identificator);
            if(findIter)
            {
                findedArr[counter] = findIter;
                counter++;
                findIter++;
            }
            
        }

        if(counter == 1)
        {
            return findedArr[0];
        }
        else if(counter > 1)
        {
            unsigned studentID;

            std::cout << "\033[2J\033[H";

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Найдено несколько совпадений" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "ID";
            cout << std::setw(6) << std::setfill(' ') << ' ';
            cout << "Имя";
            cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
            cout << "Группа";
            cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
            cout << "Посещений" << endl;
            
            for(size_t i = 0; i < counter; ++i)
            {
                Student_format_print(findedArr[i]);
                cout << endl;
            }

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Введите ID: ";
            cin >> studentID;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                studentID = 0;
            }

            for(size_t i = 0; i < counter; ++i)
            {
                if((*findedArr[i]).ID == studentID)
                {
                    findIter = findedArr[i];
                    break;
                }
            }
            
            return findIter;
        }
        else
        {
            return findIter;
        }

    }
}

// ================================================================================= //

void menu::Student_edit(Students::iterator& sIter)
{  
    enum point {back, changeGroup, changeLastname, exclude};
    short inputValue = -1;
    Groups::iterator gIter;

    while(inputValue)
    {   
          std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "Редактирование студента" << endl;
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "1. Изменить группу" << endl;
        cout << "2. Изменить фамилию" << endl;
        cout << "3. Исключить" << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                inputValue = -1;
            }

        switch(inputValue)
        {
        case(back):
            break;
        case(changeGroup):
            gIter = school->groups_begin();

            if(gIter)
            {
                std::cout << "\033[2J\033[H";

                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    
                cout << "ID";
                cout << std::setw(6) << std::setfill(' ') << ' ';
                cout << "Группа" << endl;
                while(gIter)
                {
                    Group_format_print(gIter);
                    cout << endl;
                    gIter++;
                }
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            }

            Student_edit_group(sIter);
            break;
        case(changeLastname):
            Student_edit_lastname(sIter);
            break;
        case(exclude):
            Students_exclude(sIter);
            break;
        default:
            break;
        }
    }
}

// ================================================================================= //

void menu::Student_edit_lastname(Students::iterator& sIter)
{
    char newLastname[Students::MAX_NAME_BYTES];

    std::cout << "\033[2J\033[H";
    
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
bool menu::Student_edit_group(Students::iterator& sIter)
{
    unsigned groupID;

    cout << "Введите номер группы или 0 для исключения из группы: ";
    cin >> groupID;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        groupID = 0;
    }

    if(groupID == 0)
    {
        (*sIter).groupID = groupID;
        return true;
    }


    Groups::iterator gIter = 
        SchoolAlg::search(school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);

    if(!gIter)
    {
        return false;
    }

    (*sIter).groupID = groupID;
    return true;
}

// ================================================================================= //


void menu::in_Students_list()
{
    enum point {back, sortLastname, sortVisits, add, pop};
    short inputValue = -1;
    Students::iterator sIter;

    while(inputValue)
    {
        sIter = school->students_begin();

        std::cout << "\033[2J\033[H";

        if(!sIter)
        {
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Нет студентов" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "0. Назад" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Ввод: " << endl;

            cin >> inputValue;
            return;
        }


        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "Список студентов" << endl;
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "ID";
        cout << std::setw(6) << std::setfill(' ') << ' ';
        cout << "Имя";
        cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
        cout << "Группа";
        cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
        cout << "Посещений" << endl;

        while(sIter)
        {
            Student_format_print(sIter);
            cout << endl;
            ++sIter;
        }
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "1. Сортировка по имени" << endl;
        cout << "2. Сортировка по посещениям " << endl;
        cout << "0. Назад " << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

        switch(inputValue)
        {
        case(back):
            break;
        case(sortLastname):
            school->sort_students(Students::lastnameComparator()); // не работает со значением по умолчанию??

            break;
        case(sortVisits):
            school->sort_students(Students::visitComparator()); // не работает со значением по умолчанию??

            break;
        default:
            break;
        }
    }
}

// ================================================================================= //

void menu::Students_exclude(Students::iterator& sIter)
{
    school->pop_student(sIter);
}

// ================================================================================= //
        // IN_GROUPS
// ================================================================================= //

void menu::in_Groups()
{
    enum point {back, list, create, pop};
    unsigned inputValue = -1;
    Groups::iterator gIter;


    while(inputValue)
    {
        std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "Группы" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "1. Список груп" << endl;
        cout << "2. Создать группу" << endl;
        cout << "3. Удалить группу" << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

        switch(inputValue)
        {
        case(list):
            gIter = school->groups_begin();

            std::cout << "\033[2J\033[H";
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            if(!gIter)
            {
                cout << "Нет групп" << endl;
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "0. Назад" << endl;

                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Ввод: ";

                short inputWait;
                cin >> inputWait;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
            else
            {
                cout << "ID";
                cout << std::setw(6) << std::setfill(' ') << ' ';
                cout << "Название" << endl;

                while(gIter)
                {
                    Group_format_print(gIter);
                    cout << endl;
                    gIter++;
                }
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "0. Назад" << endl;

                cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                cout << "Ввод: ";

                short inputWait;
                cin >> inputWait;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            break;
        case(create):
            create_Group();
            break;
        case(pop):
            delete_Group();
            break;
        case(back):
            break;
        default:
            break;                
        }
    }
} 

// ================================================================================= //

unsigned menu::create_Group()
{
    char name[Groups::MAX_NAME_BYTES];

    std::cout << "\033[2J\033[H";
    
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
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "0. Назад" << endl;

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "Ввод: ";
            cin >> inputValue;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                inputValue = 0;
            }
            
            switch(inputValue)
            {
            case(back):
                return 0;
            }
        }
    return 0;
    }
}

void menu::delete_Group()
{
    unsigned groupID, inputValue = -1;
    Groups::iterator gIter;


    while(inputValue)
    {
        std::cout << "\033[2J\033[H";
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    
        cout << "ID";
        cout << std::setw(6) << std::setfill(' ') << ' ';
        cout << "Группа" << endl;

        gIter = school->groups_begin();
        while(gIter)
        {
            Group_format_print(gIter);
            cout << endl; 
            gIter++;
        }
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Введите номер группы: ";
        cin >> groupID;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            groupID = 0;
        }

        Groups::iterator gIter = 
            SchoolAlg::search(school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);

        if(gIter)
        {
            try
            {
                school->pop_group(gIter);
                return;
            }
            catch(NotEmpty&)
            {
                std::cout << "\033[2J\033[H";
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                cout << "Группа не пустая" << endl;
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;           

                enum {back, disband};
                inputValue = -1;

                while(inputValue)
                {
                    cout << "1. Распустить группу" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Ввод: ";
                    cin >> inputValue;

                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        inputValue = 0;
                    }

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
                        inputValue = 0;
                    }
                }
            
            
            }
        }
        else
        {
            enum {back, repeat};

            std::cout << "\033[2J\033[H";
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Не удалось найти группу" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "0. Назад" << endl;
            cout << "1. Повторить ввод" << endl;

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "Ввод: ";
            cin >> inputValue;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                inputValue = 0;
            }

            switch(inputValue)
            {
            case(back):
                inputValue = 0;
                break;
            case(repeat):
                continue;
            }
        }
    }
}

void menu::Group_format_print(Groups::iterator& gIter) const
{

    cout << (*gIter).ID;
    cout << std::setw(5) << std::setfill('.') << '.';

    cout  << (*gIter).name;

}


// ================================================================================= //
        // IN_VISITS
// ================================================================================= //

void menu::in_Visits()
{
    enum point {back, add, addToGroup, showByDay};
    short inputValue = -1;
    Students::iterator sIter; 
    unsigned visitDay;


    while(inputValue)
    {
        std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "Посещения"  << endl;
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "1. Отметить студента" << endl;
        cout << "2. Отметить группу" << endl;
        cout << "3. Посещения по дате" << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;
        }

        switch(inputValue)
        {
        case(back):
            break;
        case(add):
            in_personal_visit_add();
            break;
        case(addToGroup):
            group_visit_add();
            break;
        case(showByDay):
            visitDay = input_visit_day();
            
            Visits_format_print(visitDay);

            break;
        default:
            break;
        }
    }
}

unsigned menu::input_visit_day()
{
    unsigned day, mounth, visitDay;
    enum point {back};
    short inputValue = -1;


    while(inputValue)
    {
        std::cout << "\033[2J\033[H";

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "Введите день и месяц в числовом формате" << endl;
        cout << "Для выхода введите 0" << endl;

        cout << std::setfill('-') <<std::setw(60) << '-' << endl;
        cout << "День: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = 0;
        }
        
        switch(inputValue)
        {
        case(back):
            return 0;
        default:
            day = inputValue;
        }

        cout << std::setfill('-') <<std::setw(60) << '-' << endl;
        cout << "Месяц: ";
        cin >> inputValue;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = 0;
        }

        switch(inputValue)
        {
        case(back):
            return 0;
        default:
            mounth = inputValue;
        }

        try
        {
            visitDay = dateConventer.date_to_day(day, mounth); 
            return visitDay;
        }
        catch(WrongNumber&)
        {
            enum points {back, repeat};

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Неверная дата" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "0. Отменить" << endl;
            cout << "1. Повторить ввод" << endl;

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "Ввод: ";
            cin >> inputValue;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                inputValue = -1;
            }

            switch(inputValue)
            {
            case(back):
                return 0;
            case(repeat):
                inputValue = -1;
                break;
            default:
                break;;
            }
        }

    }
    return 0;
}

void menu::in_personal_visit_add()
{
    enum point {back, add};
    short inputValue = -1;
    unsigned visitDay;
    Students::iterator sIter;

    while(inputValue)
    {
        std::cout << "\033[2J\033[H";
        
        sIter = Student_search(school->students_begin(), school->students_end());
        if(sIter)
        {
            visitDay = input_visit_day();
            if(visitDay)
            {
                school->push_visit(sIter, visitDay);
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            std::cout << "\033[2J\033[H";

            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Совпадений не найдено" << endl;
            cout << "1. Пвоторить ввод" << endl;
            cout << "0. Назад" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "Ввод: " << endl;

            cin >> inputValue;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                inputValue = 0;
            }
        }
    }
}

bool menu::group_visit_add()
{
    unsigned groupID, visitDay;
    Students::iterator sIter = school->students_begin();
    Groups::iterator   gIter = school->groups_begin();

    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Группа" << endl;

    if(gIter)
    {
        while(gIter)
        {
            Group_format_print(gIter);
            cout << endl;
            gIter++;
        }
    }
    else
    {
        cout << "Нет групп" << endl;
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> groupID;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        return false;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Ведите номер группы: ";
    cin >> groupID;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        groupID = 0;
    }

    gIter = SchoolAlg::search
        (school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);
    
    if(!gIter)
    {
        std::cout << "\033[2J\033[H";

        cout << "Группа не найдена." << endl;
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;
        cout << "0. Назад" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Ввод: ";
        cin >> groupID;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        return false;
    }

    visitDay = input_visit_day();

    while(sIter)
    {
        if((*sIter).groupID == groupID)
            school->push_visit(sIter, visitDay);

        ++sIter;
    }

    return true;
}

void menu::Visits_format_print(const unsigned& day) const
{
    Students::iterator sIter = school->students_begin();
    unsigned dayOfMounth = 0;
    unsigned mounth = 0;

    dateConventer.day_to_date(day, dayOfMounth, mounth);
    
    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Посещений "  << dayOfMounth << ' ' << dateConventer.monthName[mounth -1 ] << endl;
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Имя";
    cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
    cout << "Группа";
    cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
    cout << "Посещений" << endl;

    bool hasVisit = false;
    while(sIter)
    {
        if((*sIter).has_day(day))
        {
            Student_format_print(sIter);
            cout << endl;
            hasVisit = true;
        }

        ++sIter;
    }

    if(!hasVisit)
        cout << "Нет посещений в этот день" << endl;

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "0. Назад" << endl;
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Ввод: ";
    short inputWait;
    cin >> inputWait;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
}