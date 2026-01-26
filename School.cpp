#include "School.h"

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
        head = head->next;
        head->prev = nullptr;
        delete student;
        capacity--;
        return;
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

void School::addVisit(Student* ptr, unsigned day)
{
    if(!ptr)
        return;

    ptr->dates.push(day);

    ptr->visits++;
}

bool School::addVisit(unsigned studentID, unsigned day)
{
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

void School::addGroupVisit(unsigned groupID, unsigned day)
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

        if(destination == end())
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

void School::excludeFromGroup(unsigned studentID)
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

void School::disband(unsigned groupID)
{
    Student* ptr = head;

    while(ptr)
    {
        if(ptr->groupID == groupID)
            ptr->groupID = 0;

        ptr = ptr->next;
    }
}

void School::disbandAndPop(unsigned groupID)
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
    unsigned convertedDay = converter.DateToDay(day, mounth);

    School::printVisitsInDate(convertedDay);
}

void School::printVisitsInDate(const unsigned& day) const
{
    for(Student* ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        for(size_t i = 0; i < ptr->dates.elementsQty; ++i)
        {
            if(ptr->dates.datesArray[i] == day)
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
        
        // fout.write((char*)&ptr->ID, sizeof(ptr->ID));
        fout.write((char*)&ptr->lastname, MAX_NAME_LEN);
        fout.write((char*)&ptr->groupID, sizeof(uint16_t));
        fout.write((char*)&ptr->visits, sizeof(uint16_t));
        
        fout.write((char*)ptr->dates.datesArray, sizeof(uint16_t) * ptr->dates.elementsQty);

        ptr = ptr->next;
    }

    fout.close();
    return true;
}

// void School::readFromBIn(const char* filename)
// {
//     std::ifstream fin(filename, std::ios::binary);
 
//     // fout.read((char*)capacity, sizeof(capacity));


//     unsigned groupid, visits, date;
//     char* name;
//     while(! fin.eof())
//     {
//         // fin.read((char*)id, sizeof(Student::ID));

//         fin.getline(name, MAX_NAME_LEN, '\0');

//         fin.read((char*)groupid, sizeof(Student::groupID));
//         fin.read((char*)visits, sizeof(Student::visits));

//         push_back(id, name, groupid);

//         for(size_t i = 0; i < visits; ++i)
//         {
//             fin.read((char*)date, sizeof(Student::dates.datesArray));
//             tail->dates.push(date);
//         }

        
        
//     }

// }

