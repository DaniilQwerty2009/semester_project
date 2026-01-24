#include "School.h"

void School::push_back(unsigned studentID, const char* lastname, unsigned groupID)
    {
        if(!head)
        {
            head = new Student(studentID, lastname, groupID);
            tail = head;
        }
        else
        {
            tail->next = new Student(studentID, lastname, groupID);
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
        }
    }

void School::pop(Student* student)
{
    pop(student->ID);

}

bool School::pop(unsigned studentID)
{  
    Student* ptr = head;

    if(ptr->ID == head->ID)
    {
        head = head->next;
        head->prev = nullptr;
        delete ptr;
        return true;
    } 



    while(ptr->ID != studentID && ptr)
        ptr = ptr->next;

    if(!ptr)
        return false;

    if(ptr == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete ptr;
        return true;
    }
    else
    {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        return true;
    }  
}

void School::addVisit(const Student* ptr, unsigned day)
{
    School::addVisit(ptr->ID, day);
}

bool School::addVisit(unsigned studentID, unsigned day)
{
    Student* ptr = head;

    if(!ptr)
        return false;

    while(ptr)
    {
        if(ptr->ID == studentID)
        {
            ptr->dates.push(day);
            ptr->visits++;
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

void School::printStudentInfo(unsigned studentID) const
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




