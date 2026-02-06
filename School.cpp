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

void School::push_back(unsigned studentID, const char* lastname, unsigned groupID)
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
            
            ptr->next = new Group(getGroupID(), name);
            ptr->next->prev = ptr;

            return ptr->next->ID;
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

    if(Gptr == groups)
    {
        if(!groups->next)
        {
            delete Gptr;
            groups = nullptr;
            return true;
        }
        else
        {
            groups = groups->next;
            groups->prev = nullptr;
            delete Gptr;
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
            return true;
        }
        else
        {
            Gptr->prev->next = nullptr;
            delete Gptr;
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

bool School::writeToBin(const char* filename) const
{
    std::ofstream fout(filename, std::ios::binary);

    Student* ptr = head;
    // fout.write((char*)&capacity, sizeof(capacity));

    while(ptr)
    {
        
        fout.write((char*)&ptr->ID, sizeof(uint32_t));
        fout.write(ptr->lastname, Student::MAX_NAME_LEN);
        fout.write((char*)&ptr->groupID, sizeof(uint32_t));
        fout.write((char*)&ptr->visits, sizeof(uint32_t));
        
        fout.write((char*)ptr->days.datesArray, sizeof(uint32_t) * ptr->days.elementsQty);

        ptr = ptr->next;
    }

    fout.close();
    return true;
}

void School::copySchoolFromBin(const char* filename)
{
    std::ifstream fin(filename, std::ios::binary);
    
        
    unsigned id, groupid, visits, date;
    char name[Student::MAX_NAME_LEN];
    while(! fin.eof())
    {
        fin.read((char*)&id, sizeof(uint32_t));
        fin.read(name, Student::MAX_NAME_LEN);

        fin.read((char*)&groupid, sizeof(uint32_t));

        fin.read((char*)&visits, sizeof(uint32_t));

        push_back(id, name, groupid);

        for(size_t i = 0; i < visits; ++i)
        {
            fin.read((char*)&date, sizeof(uint32_t));
            tail->days.push(date);
        }

        if( !fin.peek())
            break;
        
    }

    // проверка на уникальность ID, иначе ручное слияние
}

