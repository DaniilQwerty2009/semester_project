#include "School.h"


void School::iterator::operator=(Student* nodePtr)
{
    pointer = nodePtr;
}

bool School::iterator::operator!=(Student* nodePtr)
{
    return pointer != nodePtr;
}

bool School::iterator::operator==(Student* nodePtr)
{
    return pointer == nodePtr;
}

School::Student* School::iterator::operator++()
{
    if(pointer)
        pointer = pointer->next;

    return pointer;
}

School::Student* School::iterator::operator++(int)
{
    School::Student* temp = pointer;

    if(pointer)
        pointer = pointer->next;

    return temp;
}

const unsigned& School::iterator::operator*() const
{
    return pointer->ID;
}

const char* School::iterator::getLastname() const
{
    return pointer->lastname;
}

const unsigned& School::iterator::getID() const
{
    return pointer->ID;
} 

const size_t& School::iterator::getVisits() const
{
    return pointer->visits;
}

unsigned short* School::iterator::getVisitsDates() const
{
    return pointer->visitsDates;
}

const unsigned& School::iterator::getGroup() const
{
    return pointer->groupID;
}

void School::iterator::printInfo() const
    {
        std::cout << pointer->ID << '/' << pointer->lastname << '/';
        std::cout << pointer->groupID << '/' << pointer->visits << std::endl;
    }
