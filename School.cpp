#include "School.h"

void School::push_back(unsigned studentID, const char* lastname, unsigned groupID = 0)
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

bool School::pop(unsigned ID)
{
    School::iterator iterator(begin());   
    
    while(iterator != end())
    {
        if(iterator.getID() == ID)
            break;
        ++iterator;
    }
    if(iterator == end())
        return false;

    if(iterator.pointer)
    {
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
    return false;
}