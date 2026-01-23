#include "School.h"


void School::iterator::operator=(iterator iterator)
{
    pointer = iterator.pointer;
}

bool School::iterator::operator!=(iterator iterator)
{
    return pointer != iterator.pointer;
}

bool School::iterator::operator==(iterator iterator)
{
    return pointer == iterator.pointer;
}

void School::iterator::operator=(Student* ptr)
{
    pointer = ptr;
}

bool School::iterator::operator!=(Student* ptr)
{
    return pointer != ptr;
}

bool School::iterator::operator==(Student* ptr)
{
    return pointer == ptr;
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


const School::Student& School::iterator::operator*() const
{
    return *pointer;
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
