#include "School.h"


unsigned School::push_student(const char* lastname, unsigned groupID)
    {
        // Проверка на наличие группы по номеру, иначе присваиваем нулевой номер
        Groups::iterator gIter(groups.begin());

        while(gIter)
        {
            if((*gIter).ID == groupID)
                break;

            gIter++;
        }

        if(!gIter)
            groupID = 0;

        try
        {
            students.push(sIDcounter, lastname, groupID);
        }
        catch(SchoolExeptions& err)
        {
            err.what();
            return 0;
        }
        
        sIDcounter++;
        return (sIDcounter - 1);
    }

void     School::push_student(const unsigned& studentID, const char* lastname, const unsigned& groupID)
    {
        try
        {
            students.push(studentID, lastname, groupID);
        }
        catch(SchoolExeptions& err)
        {
            err.what();
            return;
        }
    }

void     School::pop_student(Students::iterator& sIter) noexcept
{
    if(!sIter)
        return;

    students.pop(&(*sIter)); 
}

unsigned School::push_group(const char* name)
{
    try
    {
        groups.push(gIDcounter, name);
        gIDcounter++;
        return (gIDcounter - 1);
    }
    catch(AlreadyExist&)        // такая группа уже существует
    {
        throw;
    }
    catch(EmptyStr& err)        // пустое имя
    {
        err.what();
        return 0;
    }
}

void     School::push_group(const unsigned& ID, const char* name)
{
    groups.push(ID, name);
}

void     School::pop_group(Groups::iterator& gIter)
{
    Students::iterator sIter(students.begin());

    while(sIter)
    {
        if((*sIter).groupID == (*gIter).ID)
            throw NotEmpty();                   // если в группе есть студенты
            
        sIter++;
    }

    groups.pop(&(*gIter));
}

void     School::push_visit(Students::iterator& sIter, const unsigned& day) noexcept
{
    
    if((*sIter).has_day(day))   // проверка на повторное внесение даты
        return;

    (*sIter).push_day(day);
}

bool     School::save(const char* filename) const noexcept
{
    std::ofstream fout(filename, std::ios::binary);
    
    if(!fout)
        return false;

    Students::iterator sIter = students.begin();
    
    uint64_t studentsAmmount = static_cast<uint64_t>(students.size()); // кол-во студентов
    uint32_t visitsAmmount;                                          // кол-во посещений у студента

    // Записываем основное состояние объекта - кол-во студентов
    fout.write((char*)&studentsAmmount, sizeof(uint64_t));

    // Поочередно записываем поля каждого студента.
    // Размер под каждое поле фиксированный
    for(size_t i = 0; i < studentsAmmount; ++i)
    {
        
        fout.write((char*)&(*sIter).ID, sizeof(uint32_t));
        fout.write((*sIter).lastname, Students::MAX_NAME_BYTES);
        fout.write((char*)&(*sIter).groupID, sizeof(uint32_t));

        visitsAmmount = (*sIter).visits_arr_size();
        fout.write((char*)&visitsAmmount, sizeof(uint32_t));
        
        fout.write((char*)(*sIter).get_visits_arr(), sizeof(uint32_t) * visitsAmmount);

        sIter++;
    }

    
    uint64_t groupAmmount = static_cast<uint64_t>(groups.size());              // кол-во групп
    
    // Записываем кол-во групп
    fout.write((char*)&groupAmmount, sizeof(uint64_t));

    Groups::iterator gIter = groups.begin();

    // Поочередно записываем поля каждой группы
    for(size_t i = 0; i < groupAmmount; ++i)
    {
        fout.write((char*)&(*gIter).ID, sizeof(uint32_t));
        fout.write((*gIter).name, Groups::MAX_NAME_BYTES);

        gIter++;
    }

    fout.close();
    return true;
}

void     School::save_load(const char* filename) noexcept
{
    std::ifstream fin(filename, std::ios::binary);

    if(!fin)
        return;
        
    // Переменные для промежуточной записи из файла
    unsigned id, groupid, visits, visitDay;
    size_t blockLen;                        // размер блока данных  
    char name[Students::MAX_NAME_BYTES];

    Students::iterator sIter;

    unsigned maxID = sIDcounter;         // для увеличения счетчика ID в новом объекте до актуального 

    // Записываем размер блока со студентами - первое число в файле
    fin.read((char*)&blockLen, sizeof(uint64_t));

    // Записываем каждое поле в промежуточные переменные,
    // вызываем push для студентов и их посещений
    for(size_t i = 0; i < blockLen; ++i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(name, Students::MAX_NAME_BYTES);

        fin.read((char*)&groupid, sizeof(uint32_t));

        fin.read((char*)&visits, sizeof(uint32_t));

        // Обновляем счетчик ID
        if(maxID < id)
            maxID = id;

        push_student(id, name, groupid);
        sIter = students.last();

        for(size_t i = 0; i < visits; ++i)
        {
            fin.read((char*)&visitDay, sizeof(uint32_t));
            push_visit(sIter, visitDay);
        }
    }

    // Обновляем счетчик ID студентов
    sIDcounter = maxID + 1;
    
    maxID = gIDcounter;

    char groupName[Groups::MAX_NAME_BYTES];
    fin.read((char*)&blockLen, sizeof(uint64_t));
    
    // Записываем каждое поле в промежуточные переменные,
    // вызываем push для групп
    for(size_t i = 0; i < blockLen; ++ i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(groupName, Groups::MAX_NAME_BYTES);

        // Обновляем счетчик ID
        if(maxID < id)
            maxID = id;

        push_group(id, groupName);
    }

    // Обновляем счетчик ID групп
    gIDcounter = maxID + 1;

}

