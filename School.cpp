#include "School.h"

// Убрать нехарактеные контейнеру методы: printVisits, printStudentInfo и тд

unsigned School::push_back(const char* lastname, unsigned groupID)
    {
        // исключение - нет такой группы
        // обработка - присваивание группе 0
        Group* ptr = groupsMap;
        while(ptr)
        {
            if(ptr->key == groupID)
                break;

            ptr = ptr->next;
        }

        if(!ptr)
        {    
            std::cout << "Исключение push_back /group/" << std::endl;
            groupID = 0;
        }

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

// void School::pop(Student& student)
// {
//     pop(&student);
// }

bool School::pop(const unsigned studentID)
{  
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->ID == studentID)
        {
            pop(ptr);
            return true;
        }

        ptr = ptr->next;
    }  
    return false;
}

unsigned School::createGroup(const char* name)
{
    if(!groupsMap)
        {
            groupsMap = new Group(getGroupID(), name);
            return groupsMap->key;
        }
        else
        {
            Group* ptr = groupsMap;

            while(ptr->next != nullptr)
                ptr = ptr->next;
            
            ptr->next = new Group(getGroupID(), name);
            ptr->next->prev = ptr;

            return ptr->next->key;
        }
}

bool School::deleteGroup(Group* group) // ошибка на непустую группу
{
    Student* ptr = head;
    while(ptr)
    {
        if(ptr->groupID == group->key)
            return false;                   // исключение - не пустая группа
    }

    if(group == groupsMap)
    {
        if(!groupsMap->next)
        {
            delete group;
            groupsMap = nullptr;
            return true;
        }
        else
        {
            groupsMap = groupsMap->next;
            groupsMap->prev = nullptr;
            delete group;
            return true;
        }
    }
    else
    {
        if(group->next)
        {
            group->prev->next = group->next;
            group->next->prev = group->prev;
            delete group;
            return true;
        }
        else
        {
            group->prev->next = nullptr;
            delete group;
            return true;
        }

    }


}

void School::addVisit(Student* ptr, unsigned day)
{
    // Проверка на одинаковую дату!
    if(!ptr)
        return;

    ptr->days.push(day);

    ptr->visits++;
}

bool School::addVisit(unsigned studentID, unsigned day)
{

    // Проверка на одинаковую дату!
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->ID == studentID)
        {
            addVisit(ptr, day);
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

void School::addGroupVisit(const unsigned& groupID, unsigned day)
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->groupID == groupID)
            School::addVisit(ptr, day);

        ptr = ptr->next;
    }
}

void School::printStudentInfo(Student* ptr) const
{
    printStudentInfo(ptr->ID);
}

void School::printStudentInfo(const unsigned& studentID) const
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->ID == studentID)
        {
            std::cout << ptr->ID       << '/';
            std::cout << ptr->lastname << '/';
            std::cout << ptr->groupID  << '/';
            std::cout << ptr->visits   << '/';
            return;
        }
        
        ptr = ptr->next;
    }    
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

void School::excludeFromGroup(const unsigned& studentID)
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->ID == studentID)
        {
            ptr->groupID = 0;
            return;
        }

        ptr = ptr->next;
    }
}

void School::disband(const unsigned& groupID)
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->groupID == groupID)
            ptr->groupID = 0;

        ptr = ptr->next;
    }
}

void School::disbandAndPop(const unsigned& groupID)
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->groupID == groupID)
        {
            pop(ptr);
        }
    }
}


void School::printVisitsInDate(const unsigned& day, const unsigned& mounth) const
{
    unsigned convertedDay = dateConverter.DateToDay(day, mounth);

    School::printVisitsInDate(convertedDay);
}

void School::printVisitsInDate(const unsigned& day) const
{
    for(Student* ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        for(size_t i = 0; i < ptr->days.elementsQty; ++i)
        {
            if(ptr->days.datesArray[i] == day)
                std::cout << ptr->lastname << std::endl;
        }
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

