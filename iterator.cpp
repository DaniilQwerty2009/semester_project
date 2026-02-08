#include "School.h"


void School::iterator::
    operator=(School::iterator iterator)
{
    pointer = iterator.pointer;
}

bool School::iterator::
    operator!=(School::iterator& iterator)
{
    return pointer != iterator.pointer;
}

bool School::iterator::
    operator==(School::iterator& iterator)
{
    return pointer == iterator.pointer;
}

School::iterator School::iterator::
    operator++()
{
    if(pointer)
        pointer = pointer->next;

    return *this;
}

School::iterator School::iterator::
    operator++(int)
{
    School::iterator temp = *this;

    if(pointer)
        pointer = pointer->next;

    return temp;
}

School::iterator School::iterator::
    operator--()
{
    // ошибка при nullptr!!
    
    
    if(pointer)
        pointer = pointer->prev;
    return *this;
}

School::iterator School::iterator::
    operator--(int)
{
    // ошибка при nullptr!!

    School::iterator temp = *this;

    if(pointer)
        pointer = pointer->prev;

    return temp;

}


Student& School::iterator::
    operator*() const
{
    return *pointer;
}

School::iterator::operator bool() const
{
    return pointer != nullptr;
}

// ============================================================================

void Groups::iterator::
    operator= (Groups::iterator iterator)
{
    pointer = iterator.pointer;
}

bool Groups::iterator::
    operator!=(Groups::iterator& iterator)
{
    return pointer != iterator.pointer;
}

bool Groups::iterator::
    operator==(Groups::iterator& iterator)
{
    return pointer == iterator.pointer;
}

Groups::iterator Groups::iterator::
    operator++()
{
    if(this->pointer)
        pointer = pointer->next;
        
    return *this;
}

Groups::iterator Groups::iterator::
    operator++(int)
{
    Groups::iterator temp = *this;
    
    if(this->pointer)
        pointer = pointer->next;

    return temp;
}

Groups::iterator::operator bool() const
{
    return this->pointer;
}

Groups::Group& Groups::iterator::
    operator*() const
{
    return *pointer;
}