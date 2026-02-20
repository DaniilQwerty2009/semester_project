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

void School::push_student(const unsigned& studentID, const char* lastname, const unsigned& groupID)
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

void School::pop_student(Students::iterator& sIter)
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
    }
    catch(AlreadyExist&)        // такая гркппа уже существует
    {
        throw;
    }
    catch(EmptyPtr& err)        // пустое имя
    {
        err.what();
        return 0;
    }
    gIDcounter++;
    return (gIDcounter - 1);
}

void School::push_group(const unsigned& ID, const char* name)
{
    groups.push(ID, name);
}

void School::pop_group(Groups::iterator& gIter) // ошибка на непустую группу
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

void School::push_visit(Students::iterator& sIter, const unsigned& day)
{
    
    if((*sIter).has_day(day))   // проверка на повторное внесение даты
        return;

    (*sIter).push_day(day);
}

// почему, если добавить const, не дает достуа к методам и полям (кроме head??)
bool School::save(const char* filename) const
{
    std::ofstream fout(filename, std::ios::binary);
    //проверка на ошибку потока - std::exeption

    Students::iterator sIter = students.begin();
    
    unsigned studentsAmmount = students.size();
    unsigned visitsAmmount;
    fout.write((char*)&studentsAmmount, sizeof(uint64_t));

    for(size_t i = 0; i < studentsAmmount; ++i)
    {
        
        fout.write((char*)&(*sIter).ID, sizeof(uint32_t));
        fout.write((*sIter).lastname, Students::MAX_NAME_BYTES);
        fout.write((char*)&(*sIter).groupID, sizeof(uint32_t));

        visitsAmmount = (*sIter).visits_arr_size();
        fout.write((char*)&visitsAmmount, sizeof(uint32_t));
        
        fout.write((char*)(*sIter).get_visits_arr(), sizeof(uint32_t) * (*sIter).visits_arr_size());

        sIter++;
    }

    unsigned groupAmmount = groups.size();
    fout.write((char*)&groupAmmount, sizeof(uint64_t));

    Groups::iterator gIter = groups.begin();

    for(size_t i = 0; i < groupAmmount; ++i)
    {
        fout.write((char*)&(*gIter).ID, sizeof(uint32_t));
        fout.write((*gIter).name, Groups::MAX_NAME_BYTES);

        gIter++;
    }

    fout.close();
    return true;
}


void School::saveLoad(const char* filename)
{
    std::ifstream fin(filename, std::ios::binary);

    if( !fin )
        return; //exeption?
        
    unsigned id, groupid, visits, visitDay, blockLen;
    char name[Students::MAX_NAME_BYTES];
    Students::iterator sIter;

    unsigned maxID = 0;

    fin.read((char*)&blockLen, sizeof(uint64_t));

    for(size_t i = 0; i < blockLen; ++i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(name, Students::MAX_NAME_BYTES);

        fin.read((char*)&groupid, sizeof(uint32_t));

        fin.read((char*)&visits, sizeof(uint32_t));

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

    sIDcounter = maxID + 1;
    maxID = 0;

    char groupName[Groups::MAX_NAME_BYTES];
    fin.read((char*)&blockLen, sizeof(uint64_t));
    
    for(size_t i = 0; i < blockLen; ++ i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(groupName, Groups::MAX_NAME_BYTES);

        if(maxID < id)
            maxID = id;

        push_group(id, groupName);
    }

    gIDcounter = maxID + 1;

}

