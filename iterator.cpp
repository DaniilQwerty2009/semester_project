#include "Students.h"
#include "Groups.h"



void Students::iterator::
    operator=(Students::iterator iterator)
{
    pointer = iterator.pointer;
}

bool Students::iterator::
    operator!=(Students::iterator& iterator)
{
    return pointer != iterator.pointer;
}

bool Students::iterator::
    operator==(Students::iterator& iterator)
{
    return pointer == iterator.pointer;
}

Students::iterator 
    Students::iterator::operator++()
{
    if(pointer)
        pointer = pointer->next;

    return *this;
}

Students::iterator 
    Students::iterator::operator++(int)
{
    Students::iterator temp = *this;

    if(pointer)
        pointer = pointer->next;

    return temp;
}

Students::iterator 
    Students::iterator::operator--()
{
    // ошибка при nullptr!!
    
    
    if(pointer)
        pointer = pointer->prev;
    return *this;
}

Students::iterator 
    Students::iterator::operator--(int)
{
    // ошибка при nullptr!!

    Students::iterator temp = *this;

    if(pointer)
        pointer = pointer->prev;

    return temp;

}


Students::Student& 
    Students::iterator::operator*() const
{
    return *pointer;
}

Students::iterator::operator bool() const
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