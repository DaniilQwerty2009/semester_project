#include "School.h"


// void School::iterator::         operator=(iterator& iterator)
// {
//     pointer = iterator.pointer;
// }

void School::iterator::         operator=(iterator iterator)
{
    pointer = iterator.pointer;
}

bool School::iterator::         operator!=(iterator& iterator)
{
    return pointer != iterator.pointer;
}

bool School::iterator::         operator==(iterator& iterator)
{
    return pointer == iterator.pointer;
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
    // ошибка при nullptr!!
    
    
    if(pointer)
        pointer = pointer->prev;
    return *this;
}

School::iterator School::iterator::operator--(int)
{
    // ошибка при nullptr!!

    School::iterator temp = *this;

    if(pointer)
        pointer = pointer->prev;

    return temp;

}


Student& School::iterator::operator*() const
{
    return *pointer;
}

School::iterator::operator bool() const
{
    return pointer != nullptr;
}

