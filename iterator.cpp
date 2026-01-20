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

bool School::iterator::operator!()
{
    return pointer == nullptr;
}

School::iterator School::iterator::operator++()
{
    if(pointer)
        pointer = pointer->next;

    return *this;
}

School::iterator School::iterator::operator++(int)
{
    School::iterator temp = *this;

    if(pointer)
        pointer = pointer->next;

    return temp;
}

School::iterator School::iterator::operator--()
{
    if(pointer)
        pointer = pointer->prev;
    return *this;
}

School::iterator School::iterator::operator--(int)
{
    School::iterator temp = *this;

    if(pointer)
        pointer = pointer->prev;

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

const unsigned* School::iterator::getDates() const
{
    return pointer->dates.dates;
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
