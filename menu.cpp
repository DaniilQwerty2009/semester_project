#include "menu.h"
#include <iomanip>

// cin.tie(cout&);????


void menu::init(School* school)
{
    this->school = school;

    // пункты меню
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

        // Проверка валидности ввода, ошибок потока после ввода.
        // По умолчанию при ошибке повтор ввода
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;        // означает возврат в while(inputValue)
        }

        switch(inputValue)
        {
        case(point::exit):
            school->save();
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
    // пункты меню
    enum point {back, list, search, add, addSorted, pop};
    short inputValue = -1;      // прльзовательский ввод
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

        // Проверка валидности ввода, ошибок потока после ввода.
        // По умолчанию при ошибке повтор ввода
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            inputValue = -1;        // означает повтор ввода
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
                
                // Вывод всей информации о студенте, если найден в Student_search()
                if(sIter)
                {
                    std::cout << "\033[2J\033[H";

                    // Шапка списка студентов: ID, имя, группа, кол-во посещений
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                    cout << "ID";
                    cout << std::setw(6) << std::setfill(' ') << ' ';
                    cout << "Имя";
                    cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
                    cout << "Группа";
                    cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
                    cout << "Посещений" << endl;

                    // Информация о студенте: ID, имя, группа, кол-во посещений
                    Student_format_print(sIter);
                    cout << endl;
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    // Вывод посешений студента
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

                    // Опции
                    cout << "1. Редактировать студента" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Ввод: ";
                    cin >> inputValue;

                    // Проверка валидности ввода, ошибок потока после ввода.
                    // По умолчанию при ошибке повтор ввода
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

                // Если не найден, возврат в предыдущий раздел
                else
                {
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Совпадений не найдено" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    // Ожидание ввода
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
                // Если студент не найден, возврат в предыдущий раздел
                else
                {
                    std::cout << "\033[2J\033[H";
                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    cout << "Студент не найден" << endl;
                    cout << "0. Назад" << endl;

                    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

                    // Ожидание ввода
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
    if(!studIter)
        return;

    const char* groupName = nullptr;    // в какой группе студент
    size_t fillLen;                     // заполнение остатка выделенного пространства по строку


    // Поиск имени группы по айди группы, если есть
    if((*studIter).groupID)
    {
        Groups::iterator gIter = school->groups_begin();
        while(gIter)
        {
            if((*gIter).ID == (*studIter).groupID)
            {
                groupName = (*gIter).name;
                break;
            }
            ++gIter;
        }
    }
    
    // Форматированный вывод информации о студенте в одну строку с заполнением между полями
    cout << (*studIter).ID;
    cout << std::setw(4) << std::setfill('.') << '.';

    fillLen = (Students::MAX_NAME_BYTES - strlen((*studIter).lastname)) / 2;
    cout  << (*studIter).lastname;
    cout << std::setw(fillLen) << std::setfill('.') << '.';

    fillLen = (Groups::MAX_NAME_BYTES - strlen((groupName ? groupName : "Нет группы"))) / 2;
    cout << (groupName ? groupName : "Нет группы");
    cout << std::setw(fillLen) << std::setfill('.') << '.';

    cout << std::left
        << std::setw(9) << std::setfill('.')
        << (*studIter).visits_arr_size();
    
}


// ================================================================================= //

unsigned menu::Student_add()
{
    short inputValue = -1;                      // пользовательский ввод
    unsigned groupID;                           // айди группы
    char lastname[Students::MAX_NAME_BYTES];    // буфер под имя

    bool correctNameFlag = false;               // проверка на отстутвие чисел в имени

    while(!correctNameFlag)
    {
        std::cout << "\033[2J\033[H";
        
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Добавление студента" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        // Ввод фамилии
        cout << "Фамилия: ";
        // Отчиска мусора в буфере
        cin.ignore(1000, '\n');
        cin.getline(lastname, Students::MAX_NAME_BYTES);

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Проверка на наличие чисел в имени - посимвольная проверка
        size_t i = 0;
        for(; i < strlen(lastname) && i < Students::MAX_NAME_BYTES-1; ++i)
        {
            if(isdigit(lastname[i]))
            {
                enum {cancel, repeat};

                std::cout << "\033[2J\033[H";
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                cout << "Не верный формат имени" << endl;
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
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
                // Выход из фкнуции добавления студента
                case(cancel):
                    return 0;

                // Повтор ввода
                case(repeat):
                    break;
                default:
                    break;
                }
                break;
            }
        }
        if(i == strlen(lastname) || i == Students::MAX_NAME_BYTES-1)    // если прошли все слово, значит имя корректное
                correctNameFlag = true;
    }

    // Прикрепление к группе

    // Вывод групп в терминал
    Groups::iterator gIter = school->groups_begin();

    std::cout << "\033[2J\033[H";
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    
    // Шапка списка групп: айди, название
    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Группа" << endl;

    // Информация о группах: айди, название 
    while(gIter)
    {
        Group_format_print(gIter);
        cout << endl;
        gIter++;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    // Выбор группы. Нулевой айди означает, что не прикреплен к группе
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
    cout << "Группа" << endl;

    
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
    

    // Поиск по числовому айди или фамилии
    if(isdigit(*identificator))
    {
        unsigned studentID = atoi(identificator);
        findIter = SchoolAlg::search(first, last, Students::idComparator(), studentID);
        
        return findIter;        
        
    }
    else
    {
        size_t counter = 0;                 // счетчик совпадений по фамилии
        Students::iterator findedArr[100];  // массив итераторов совпадающих фамилий
        findIter = first;

        while(findIter)
        {
            // Поиск по всем студентам. Если есть совпадение по фамилии, хапоминаем итератор в массив
            findIter = SchoolAlg::search(findIter, last, Students::lastnameComparator(), identificator);
            if(findIter)
            {
                findedArr[counter] = findIter;
                counter++;
                findIter++;
            }
            
        }

        // Если нет с одинаковой фамилией, возвращаем единственного
        if(counter == 1)
        {
            return findedArr[0];
        }

        // Иначе, уточняем по афди у подьзователя
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

            // При неверном вводе, выход с нулевым итератором
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                studentID = 0;
            }

            // Устонавливаем итератор как пустой
            findIter = Students::iterator();

            for(size_t i = 0; i < counter; ++i)
            {
                if((*findedArr[i]).ID == studentID)
                {
                    // Присваивем итератору найденный
                    findIter = findedArr[i];
                    break;
                }
            }

            // Если был неверный ввод, выход с пустым итератором
            return findIter;
        }

        // Если не найдено ни одного совпадения по фамилии
        else
        {
            return findIter;
        }

    }
}

// ================================================================================= //

void menu::Student_edit(Students::iterator& sIter)
{  
    if(!sIter)
        return;

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
    
                // Список доступных групп
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
            return;
        default:
            break;
        }
    }
}

// ================================================================================= //

void menu::Student_edit_lastname(Students::iterator& sIter)
{
    if(!sIter)
        return;

    char newLastname[Students::MAX_NAME_BYTES];
    short inputValue = -1;

    std::cout << "\033[2J\033[H";
    
    bool correctNameFlag = false;               // проверка на отстутвие чисел в имени

    while(!correctNameFlag)
    {
        std::cout << "\033[2J\033[H";
        
        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        cout << "Добавление студента" << endl;

        cout << std::setfill('=') <<std::setw(60) << '=' << endl;

        // Ввод фамилии
        cout << "Фамилия: ";
        // Отчиска мусора в буфере
        cin.ignore(1000, '\n');
        cin.getline(newLastname, Students::MAX_NAME_BYTES);

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Проверка на наличие чисел в имени - посимвольная проверка
        size_t i = 0;
        for(; i < strlen(newLastname) && i < Students::MAX_NAME_BYTES-1; ++i)
        {
            if(isdigit(newLastname[i]))
            {
                enum {cancel, repeat};

                std::cout << "\033[2J\033[H";
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
                cout << "Не верный формат имени" << endl;
                cout << std::setfill('=') <<std::setw(60) << '=' << endl;
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
                // Выход из фкнуции редактирования фамилии
                case(cancel):
                    return;

                // Повтор ввода
                case(repeat):
                    break;
                default:
                    break;
                }
                break;
            }
        }
        if(i == strlen(newLastname) || i == Students::MAX_NAME_BYTES-1)    // если прошли все слово, значит имя корректное
                correctNameFlag = true;
    }

    // Формирование корректной строки и перезапись фамилии студента
    size_t sLen = strlen(newLastname) + 1;  // длинна новой фамилии
    char* lastname;                         // указатель на новую фамилию
    if(sLen <= Students::MAX_NAME_BYTES)
    {
        // Выделяем память, копируем
        lastname = new char[sLen];
        strcpy(lastname, newLastname);

        // слкдующтй за последним символом - символ конца строки
        lastname[sLen - 1] = '\0';
    }
    else
    {
        lastname = new char[Students::MAX_NAME_BYTES];
        strncpy(lastname, newLastname, Students::MAX_NAME_BYTES);
        
        // Исключаем возможность обрезки киррилического символа (может быть больше 1-шл байта).
        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix((*sIter).lastname, sLen);
        lastname[safePrefix] = '\0';
    }        

    // Удаляем старый указатель, прикрепляем новый
    delete (*sIter).lastname;
    (*sIter).lastname = lastname;
}

// ================================================================================= //

bool menu::Student_edit_group(Students::iterator& sIter)
{
    if(!sIter)
        return false;

    unsigned groupID;

    cout << "Введите номер группы или 0 для исключения из группы: ";
    cin >> groupID;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        groupID = 0;
    }

    // 0 означает открепление от своей группы
    if(groupID == 0)
    {
        (*sIter).groupID = groupID;
        return true;
    }


    Groups::iterator gIter = 
        SchoolAlg::search(school->groups_begin(), school->groups_end(), Groups::idComparator(), groupID);

    // Если не нашли группу, не меняем
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

            // Ожидание ввода
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
            school->sort_students(Students::lastnameComparator()); 

            break;
        case(sortVisits):
            school->sort_students(Students::visitComparator());

            break;
        default:
            break;
        }
    }
}

// ================================================================================= //

void menu::Students_exclude(Students::iterator& sIter)
{
    if(!sIter)
        return;
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
                // Шапка списка
                cout << "ID";
                cout << std::setw(6) << std::setfill(' ') << ' ';
                cout << "Название" << endl;

                // Список
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
    // Отчистка буфера
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
    // Генерирует AlreadyExist и EmptyStr
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
    
        // Шапка списка групп
        cout << "ID";
        cout << std::setw(6) << std::setfill(' ') << ' ';
        cout << "Группа" << endl;

        // Список групп
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
            // Если группа не пустая, исключить из нее студентов или отмена
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
        // Если группа не найдена, повтор ввода или назад в меню
        else
        {
            enum {back, repeat};

            std::cout << "\033[2J\033[H";
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;
            cout << "Не удалось найти группу" << endl;
            cout << std::setfill('=') <<std::setw(60) << '=' << endl;

            cout << "1. Повторить ввод" << endl;
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
            case(repeat):
                continue;
            }
        }
    }
}

void menu::Group_format_print(Groups::iterator& gIter) const
{
    if(!gIter)
        return;

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
        // Если некорректно введен день или месяц (выход за допкстимые границы)
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
        
        // Поиск студента
        sIter = Student_search(school->students_begin(), school->students_end());
        if(sIter)
        {   
            // Ввод дня посещения
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
    unsigned groupID,   // Номер группы
             visitDay;  // День посещения
    Students::iterator sIter = school->students_begin();
    Groups::iterator   gIter = school->groups_begin();

    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    // Шапка списка групп
    cout << "ID";
    cout << std::setw(6) << std::setfill(' ') << ' ';
    cout << "Группа" << endl;
    // Список групп
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

    // Всем студентам с группой groupID добавить день посещения 
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
    unsigned dayOfMounth = 0;   // Число
    unsigned mounth = 0;        // Месяц

    // Запись в число и месяц даты посещения
    dateConventer.day_to_date(day, dayOfMounth, mounth);
    
    std::cout << "\033[2J\033[H";

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Посещения "  << dayOfMounth << ' ' << dateConventer.monthName[mounth -1 ] << endl;
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    bool hasVisit = false; //Есть ли такие студенты (для вывода сообщения, если нет)

    while(sIter)
    {
        // Вывод информации о студенте, если есть посещение
        if((*sIter).has_day(day))
        {
            if(!hasVisit)
            {
                // Шапка списка студентов
                cout << "ID";
                cout << std::setw(6) << std::setfill(' ') << ' ';
                cout << "Имя";
                cout << std::setw((Students::MAX_NAME_BYTES - strlen("Имя"))/2) << std::setfill(' ' ) << ' ';
                cout << "Группа";
                cout << std::setw((Groups::MAX_NAME_BYTES - strlen("Группа"))/2) << std::setfill(' ') << ' ';
                cout << "Посещений" << endl;
            }

            Student_format_print(sIter);
            cout << endl;
            hasVisit = true;
        }

        ++sIter;
    }
    // Если ни одного посещения нет
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