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

void School::pop(iterator iterator)
{
    if(iterator.pointer)
    {
        if(iterator.pointer == head && head->next == nullptr)
        {
            delete iterator.pointer;
            iterator.pointer = nullptr;

            head = nullptr;

            return;
        }

        if(iterator.pointer == head)
        {
            head = head->next;
            head->prev = nullptr;

            delete iterator.pointer;
            iterator.pointer = nullptr;

            return;
        }
        if(iterator.pointer == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;

            delete iterator.pointer;
            iterator.pointer = nullptr;

            return;
        }
        else
        {
        iterator.pointer->prev->next = iterator.pointer->next;
        iterator.pointer->next->prev = iterator.pointer->prev;

        delete iterator.pointer;
        iterator.pointer = nullptr;

        return;
        }
    }

}

bool School::pop(unsigned studentID)
{  
    School::iterator iterator(begin());   
    
    while(iterator != end())
    {
        if(iterator.getID() == studentID)
            break;
        ++iterator;
    }
    if(iterator == end())
        return false;


    if(iterator.pointer == head && head->next == nullptr)
    {
        delete iterator.pointer;
        iterator.pointer = nullptr;

        head = nullptr;

        return true;
    }

    if(iterator.pointer == head)
    {
        head = head->next;
        head->prev = nullptr;

        delete iterator.pointer;
        iterator.pointer = nullptr;

        return true;
    }
    if(iterator.pointer == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;

        delete iterator.pointer;
        iterator.pointer = nullptr;

        return true;
    }
    else
    {
    iterator.pointer->prev->next = iterator.pointer->next;
    iterator.pointer->next->prev = iterator.pointer->prev;

    delete iterator.pointer;
    iterator.pointer = nullptr;

    return true;
    }
    
}

void School::addVisit(const School::iterator& iterator, unsigned day)
{
    if(iterator.pointer)
    {    
        iterator.pointer->dates.push(day);
        ++iterator.pointer->visits;
    }
}

bool School::addVisit(unsigned studentID, unsigned day)
{
    School::iterator iterator(begin());

    if(!iterator)
        return false;

    while(iterator != end())
    {
        if(iterator.pointer->ID == studentID)
        {
            School::addVisit(iterator, day);
            ++iterator.pointer->visits;
            return true;
        }

        iterator++;
    }

    return false;
}

bool School::addGroupVisit(unsigned groupID, unsigned day)
{
    School::iterator iterator = School::begin();

    for(; iterator != School::end(); ++iterator)
    {
        if(iterator.getGroup() == groupID)
            School::addVisit(iterator, day);
    }

    return true; // !!!!
}

void School::printStudentInfo(iterator iterator) const
{
    std::cout << iterator.getID()       << '/';
    std::cout << iterator.getLastname() << '/';
    std::cout << iterator.getGroup()    << '/';
    std::cout << iterator.getVisits()   << '/';
}

void School::printStudentInfo(unsigned studentID) const
{
    School::iterator iterator(begin());

    while(iterator != end())
    {
        if(iterator.getID() == studentID)
        {
            std::cout << iterator.getID()       << '/';
            std::cout << iterator.getLastname() << '/';
            std::cout << iterator.getGroup()    << '/';
            std::cout << iterator.getVisits()   << '/';
            return;
        }
        
        ++iterator;
    }    
}






