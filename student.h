#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

#include "VisitDays.h"

#define MAX_NAME_LEN 20

struct Student
{

    const unsigned ID;
    char* lastname = nullptr;
    unsigned groupID;
    size_t visits = 0;

    VisitDays dates;

    Student* prev = nullptr;
    Student* next = nullptr;

    // Student(unsigned studentID)
    // :ID(studentID), groupID(0)
    // {   }

    Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
    :ID(studentID), groupID(groupID)
    {
        if(strlen(lastname) < MAX_NAME_LEN)
        {
            this->lastname = new char[std::strlen(lastname) + 1];
            std::strcpy(this->lastname, lastname);
            std::strcat(this->lastname, "\0");
        }
        else
        {
            this->lastname = new char[MAX_NAME_LEN];
            std::strncpy(this->lastname, lastname, MAX_NAME_LEN - 1);
            std::strcat(this->lastname, "\0");
        }
        
    }

    ~Student()
    {
        delete[] lastname;
    }

    bool operator!=(Student* ptr)
    {
        return this->ID != ptr->ID;
    }

    bool operator==(Student* ptr)
    {
        return this->ID == ptr->ID;
    }

};


#endif