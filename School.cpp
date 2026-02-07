#include "School.h"


unsigned School::push_back(const char* lastname, unsigned groupID)
    {
        // исключение - нет такой группы
        // обработка - присваивание группе 0
        Group* ptr = groups;
        while(ptr)
        {
            if(ptr->ID == groupID)
                break;

            ptr = ptr->next;
        }

        if(!ptr)
            groupID = 0;

        if(!head)
        {
            head = new Student(getStudentID(), lastname, groupID);
            capacity++;
            tail = head;
        }
        else
        {
            tail->next = new Student(getStudentID(), lastname, groupID);
            capacity++;
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
            
        }

        return tail->ID;
    }

void School::push_back(const unsigned& studentID, const char* lastname, unsigned groupID)
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

void School::pop(Student* student)
{
    if(!student)
        return;

    

    if(student == head)
    {
        if(!student->next)
        {
            head = nullptr;
            delete student;
            capacity--;
            return;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
            delete student;
            capacity--;
            return;
        }
        
    } 

    if(student == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete student;
        capacity--;
        return;
    }
    else
    {
        student->prev->next = student->next;
        student->next->prev = student->prev;
        delete student;
        capacity--;
        return;
    }  

}

//exeption
unsigned School::createGroup(const char* name)
{
    if(!groups)
        {
            groups = new Group(getGroupID(), name);
            groupsCapacity++;
            return groups->ID;
        }
    else
    {
        Group* ptr = groups;

        while(ptr->next != nullptr)
        {
            if(strcmp(ptr->name, name) == 0)
                return 0;                    //exeption

            ptr = ptr->next;
        }
        if(strcmp(ptr->name, name) == 0)
                return 0;
        
        ptr->next = new Group(getGroupID(), name);
        ptr->next->prev = ptr;
        groupsCapacity++;
        return ptr->next->ID;
    }
}

void School::createGroup(const unsigned& ID, const char* name)
{
    if(!groups)
        {
            groups = new Group(ID, name);
            groupsCapacity++;
            return;
        }
    else
        {
            Group* ptr = groups;

            while(ptr->next != nullptr)
                ptr = ptr->next;
            
            ptr->next = new Group(ID, name);
            ptr->next->prev = ptr;
            groupsCapacity++;
        }
}

bool School::deleteGroup(const unsigned& ID) // ошибка на непустую группу
{
    Student* Sptr = head;
    while(Sptr)
    {
        if(Sptr->groupID == ID)
            return false;                   // исключение - не пустая группа
        Sptr = Sptr->next;
    }

    Group* Gptr = groups;
    while(Gptr)
    {
        if(Gptr->ID == ID)
            break;

        Gptr = Gptr->next;
    }
    if(!Gptr)
        return false; //exeption has not group


    if(Gptr == groups)
    {
        if(!groups->next)
        {
            delete Gptr;
            groups = nullptr;
            groupsCapacity--;
            return true;
        }
        else
        {
            groups = groups->next;
            groups->prev = nullptr;
            delete Gptr;
            groupsCapacity--;
            return true;
        }
    }
    else
    {
        if(Gptr->next)
        {
            Gptr->prev->next = Gptr->next;
            Gptr->next->prev = Gptr->prev;
            delete Gptr;
            groupsCapacity--;
            return true;
        }
        else
        {
            Gptr->prev->next = nullptr;
            delete Gptr;
            groupsCapacity--;
            return true;
        }

    }

    return false;
}

const char* School::getGroupName(const unsigned& ID) const
{
    Group* ptr = groups;
    while(ptr)
    {
        if(ptr->ID == ID)
            return ptr->name;

        ptr = ptr->next;
    }

    return nullptr;
}

const Group* School::hasGroup(const unsigned& ID) const
{
    const Group* Gptr = groups;

    while(Gptr)
    {
        if(Gptr->ID == ID)
            return Gptr;

        Gptr = Gptr->next;
    }

    return nullptr;
}

// exeption
const Group* School::getGroup() const
{
    return groups;
}

void School::addVisit(Student* ptr, const unsigned& day)
{
    // Проверка на одинаковую дату!
    if(ptr->hasDay(day))
        return;

    if(!ptr)
        return;

    ptr->days.push(day);

    ptr->visits++;
}

// void School::addGroupVisit(const Group* Gptr, const unsigned& day)
// {
//     Student* ptr = head;

//     while(ptr)
//     {
//         if(ptr->groupID == Gptr->ID)
//             School::addVisit(ptr, day);

//         ptr = ptr->next;
//     }
// }

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

void School::moveToGroup(Student* Sptr, Group* Gptr)
{
    if(Gptr)
        Sptr->groupID = Gptr->ID;
    else
        Sptr->groupID = 0;
}

void School::disband(Group* ptr)
{
    Student* STptr = head;

    while(STptr)
    {
        if(ptr->ID == STptr->groupID)
            STptr->groupID = 0;

        STptr = STptr->next;
    }
}

bool School::save(const char* filename) const
{
    std::ofstream fout(filename, std::ios::binary);

    Student* Sptr = head;
    
    fout.write((char*)&capacity, sizeof(uint64_t));

    while(Sptr)
    {
        
        fout.write((char*)&Sptr->ID, sizeof(uint32_t));
        fout.write(Sptr->lastname, Student::MAX_NAME_LEN);
        fout.write((char*)&Sptr->groupID, sizeof(uint32_t));
        fout.write((char*)&Sptr->visits, sizeof(uint32_t));
        
        fout.write((char*)Sptr->days.datesArray, sizeof(uint32_t) * Sptr->days.elementsQty);

        Sptr = Sptr->next;
    }

    Group* Gptr = groups;

    fout.write((char*)&groupsCapacity, sizeof(uint64_t));

    for(size_t i = 0; i < groupsCapacity; ++i)
    {
        fout.write((char*)&Gptr->ID, sizeof(uint32_t));
        fout.write(Gptr->name, Group::MAX_NAME_LEN);

        Gptr = Gptr->next;
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
    char name[Student::MAX_NAME_LEN];

    fin.read((char*)&blockLen, sizeof(uint64_t));

    for(size_t i = 0; i < blockLen; ++i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(name, Student::MAX_NAME_LEN);

        fin.read((char*)&groupid, sizeof(uint32_t));

        fin.read((char*)&visits, sizeof(uint32_t));

        push_back(id, name, groupid);

        for(size_t i = 0; i < visits; ++i)
        {
            fin.read((char*)&visitDay, sizeof(uint32_t));
            addVisit(tail, visitDay);
        }

        // if( !fin.peek()) //ошибка чтения? Хотя, если !groups, он сработает 
        //     break;
    }


    char groupName[Group::MAX_NAME_LEN];
    fin.read((char*)&blockLen, sizeof(uint64_t));
    
    for(size_t i = 0; i < blockLen; ++ i)
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(groupName, Group::MAX_NAME_LEN);

        createGroup(id, groupName);
    }

}

