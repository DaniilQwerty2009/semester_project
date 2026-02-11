#include "School.h"


unsigned School::push_back(const char* lastname, unsigned groupID)
    {
        // исключение - нет такой группы
        // обработка - присваивание группе 0
        Groups::iterator gIter(groups.begin());

        while(gIter)
        {
            if((*gIter).ID == groupID)
                break;

            gIter++;
        }

        if(!gIter)
            groupID = 0;

        if(!head)
        {
            head = new Student(sIDcounter, lastname, groupID);
            sIDcounter++;
            capacity++;
            tail = head;
        }
        else
        {
            tail->next = new Student(sIDcounter, lastname, groupID);
            sIDcounter++;
            capacity++;
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
            
        }

        return tail->ID;
    }

void School::push_back(const unsigned& studentID, const char* lastname, const unsigned& groupID)
    {
        if(!head)
        {
            head = new Student(studentID, lastname, groupID);
            capacity++;
            tail = head;
        }
        else
        {
            tail->next = new Student(studentID, lastname, groupID);
            capacity++;
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
            
        }
    }

void School::pop(Student* sPtr)
{
    if(!sPtr)
        return;

    if(sPtr == head)
    {
        if(!sPtr->next)
        {
            head = nullptr;
            delete sPtr;
            capacity--;
            return;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
            delete sPtr;
            capacity--;
            return;
        }
        
    } 

    if(sPtr == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete sPtr;
        capacity--;
        return;
    }
    else
    {
        sPtr->prev->next = sPtr->next;
        sPtr->next->prev = sPtr->prev;
        delete sPtr;
        capacity--;
        return;
    }  

}

//exeption
unsigned School::push_group(const char* name)
{
    groups.push(gIDcounter, name);
    gIDcounter++;
    groupsCapacity++;
    return (gIDcounter - 1);
}

void School::push_group(const unsigned& ID, const char* name)
{
    groups.push(ID, name);
    groupsCapacity++;
}

bool School::pop_group(Groups::Group& gRef) // ошибка на непустую группу
{
    School::iterator iter(begin());

    while(iter)
    {
        if((*iter).groupID == gRef.ID)
            return false;                       //Тут будет исключение
    }

    groups.pop(&gRef);
    groupsCapacity--;
    return true;
}


void School::push_visit(Student* sPtr, const unsigned& day)
{
    // Проверка на одинаковую дату!
    if(sPtr->hasDay(day))
        return;

    sPtr->days.push(day);

    sPtr->visits++;
}


void School::replace(Student* destination, Student* element)
    {
        if(!element)
            return;

        if(destination == element)
            return;

        if(destination == nullptr)
        {
            if(element == tail)
                return;

            if(element == head)
            {
                Student* newHead = element->next;

                tail->next = element;
                element->prev = tail;
                tail = element;

                head = newHead;
                head->prev = nullptr;

                return;
            }
            else
            {
                element->next->prev = element->prev;
                element->prev->next = element->next;

                tail->next = element;
                element->prev = tail;
                
                tail = element;
                tail->next = nullptr;

                return;
            }
        }

        if(destination == head)
        {
            if(element == tail)
            {
                Student* newTail = element->prev;

                head->prev = element;
                element->next = head;

                tail = newTail;
                tail->next = nullptr;

                head = element;
                head->prev = nullptr;

                return;
            }
            else
            {
                element->next->prev = element->prev;
                element->prev->next = element->next;

                head->prev = element;
                element->next = head;

                head = element;
                head->prev = nullptr;

                return;
            }
        }

        else
        {  
            if(element != head)
            {
                element->prev->next = element->next;
            }
            else
                head = element->next;

            if(element != tail)
                element->next->prev = element->prev;
            else
                tail = element->prev;

            element->prev = destination->prev;
            destination->prev->next = element;

            element->next = destination;
            destination->prev = element;

        }
        
    }


// почему, если добавить const, не дает достуа к методам и полям (кроме head??)
bool School::save(const char* filename)
{
    std::ofstream fout(filename, std::ios::binary);
    //проверка на ошибку потока - std::exeption

    Student* Sptr = head;
    
    fout.write((char*)&capacity, sizeof(uint64_t));

    while(Sptr)
    {
        
        fout.write((char*)&Sptr->ID, sizeof(uint32_t));
        fout.write(Sptr->lastname, Student::MAX_NAME_BYTES);
        fout.write((char*)&Sptr->groupID, sizeof(uint32_t));
        fout.write((char*)&Sptr->visits, sizeof(uint32_t));
        
        fout.write((char*)Sptr->days.datesArray, sizeof(uint32_t) * Sptr->days.elementsQty);

        Sptr = Sptr->next;
    }

    fout.write((char*)&groupsCapacity, sizeof(uint64_t));

    Groups::iterator gIter = groups.begin();

    for(size_t i = 0; i < groupsCapacity; ++i)
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
    char name[Student::MAX_NAME_BYTES];

    unsigned maxID = 0;

    fin.read((char*)&blockLen, sizeof(uint64_t));

    for(size_t i = 0; i < blockLen; ++i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(name, Student::MAX_NAME_BYTES);

        fin.read((char*)&groupid, sizeof(uint32_t));

        fin.read((char*)&visits, sizeof(uint32_t));

        if(maxID < id)
            maxID = id;

        push_back(id, name, groupid);

        for(size_t i = 0; i < visits; ++i)
        {
            fin.read((char*)&visitDay, sizeof(uint32_t));
            push_visit(tail, visitDay);
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

