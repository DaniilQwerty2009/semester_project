#include "School.h"


void School::iterator::operator=(Node* nodePtr)
            {
                pointer = nodePtr;
            }

Student* School::iterator::operator*()
{
    return &(pointer->studentInfo);
}

const char* School::iterator::getLastname() const
{
    return pointer->studentInfo.lastname;
}

const unsigned& School::iterator::getID() const
{
    return pointer->studentInfo.ID;
} 

const unsigned& School::iterator::getVisits() const
{
    return pointer->studentInfo.visits;
}

const unsigned short* School::iterator::getVisitsDates() const
{
    return pointer->studentInfo.dates;
}

const unsigned& School::iterator::getGroup() const
{
    return pointer->studentInfo.groupID;
}

void School::iterator::printInfo() const
    {
        std::cout << pointer->studentInfo.ID << '/' << pointer->studentInfo.lastname << '/';
        std::cout << pointer->studentInfo.groupID << '/' << pointer->studentInfo.visits << std::endl;
    }
