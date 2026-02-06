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

    VisitDays days;

    friend class School;

public:
    enum {MAX_NAME_LEN = 40};

    const unsigned ID;
    char* lastname = nullptr;
    unsigned groupID;
    size_t visits = 0;

   

    
    explicit Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
    :ID(studentID), groupID(groupID)
    {
        size_t strLen = sizeof(lastname) + 1;

        if(strLen <= MAX_NAME_LEN)
        {
            this->lastname = new char[strLen + 1];
            strcpy(this->lastname, lastname);
        }
        else
        {
            this->lastname = new char[MAX_NAME_LEN];
            strncpy(this->lastname, lastname, MAX_NAME_LEN);
            this->lastname[MAX_NAME_LEN - 1] = '\0'; 
        }        
    }


    ~Student()
    {
        delete[] lastname;
    }

    Student(Student& other)             = delete;
    Student& operator =(Student& other) = delete;

    bool operator!=(Student* ptr)
    {
        return this->ID != ptr->ID;
    }

    bool operator==(Student* ptr)
    {
        return this->ID == ptr->ID;
    }
    

    bool hasDay(const unsigned& day)
    {
        unsigned* ptr = days.datesArray;

        for(size_t i = 0; i < days.elementsQty; ++i)
        {
            if(ptr[i] == day)
                return true;
        }

        return false;
    }

};


#endif