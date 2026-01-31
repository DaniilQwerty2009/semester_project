#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

#include "VisitDays.h"

// #define MAX_NAME_LEN 20

struct Student
{
private:
    Student* prev = nullptr;
    Student* next = nullptr;

    friend class School;

public:
    enum {MAX_NAME_LEN = 40};

    const unsigned ID;
    char* lastname = nullptr;
    unsigned groupID;
    size_t visits = 0;

    VisitDays dates;

    
    explicit Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
    :ID(studentID), groupID(groupID)
    {
        this->lastname = new char[MAX_NAME_LEN];
        strncpy(this->lastname, lastname, MAX_NAME_LEN);

        if(strlen(this->lastname) == MAX_NAME_LEN - 1)
            this->lastname[MAX_NAME_LEN - 1] = '.';
        
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