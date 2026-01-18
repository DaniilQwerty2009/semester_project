#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <cstring>

#include "VisitDays.h"

class School
{
private:
    struct Student
    {
        const unsigned ID;
        char* lastname = nullptr;
        unsigned groupID;
        size_t visits = 0;

        VisitDays dates;

        Student* prev = nullptr;
        Student* next = nullptr;

        Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
        :ID(studentID), groupID(groupID)
        {
            this->lastname = new char[std::strlen(lastname) + 1];
            std::strcpy(this->lastname, lastname);
        }

        ~Student()
        {
            delete[] lastname;
        }
    };


    Student* head = nullptr;
    Student* tail = nullptr;

public:

    class iterator
        {
        private:
            Student* pointer;
        public:
            iterator():pointer(nullptr)
                {   }   
            iterator(School::Student* ptr):pointer(ptr)
                {   }
            
            void operator=(Student* nodePtr);
            bool operator!=(Student* nodePtr);
            bool operator==(Student* nodePtr);
            bool operator!();

            Student* operator++();
            Student* operator++(int);

            const unsigned&       operator*() const;

            const char*           getLastname() const; 

            const unsigned&       getID() const; 

            const size_t&         getVisits() const; 

            const unsigned*      getDates() const; 

            const unsigned&       getGroup() const; 

            void                  printInfo() const;

            friend class School;
        };

    School()
        {   }

    ~School()
    {
        iterator iter(begin());

        while(iter != end())
        {
            iterator temp = iter;
            ++iter;
            delete temp.pointer;
        }
    }
 

    void push_back(unsigned studentID, const char* lastname, unsigned groupID = 0);

    void pop(iterator iterator);

    bool pop(unsigned studentID);

    void addVisit(iterator iterator, unsigned day);

    bool addVisit(unsigned studentID, unsigned day);

    void printStudentInfo(iterator iterator) const;

    void printStudentInfo(unsigned studentID) const;

    inline Student* begin() const
    {
        return head;
    }

    inline Student* end() const
    {
        return nullptr;
    }

};








#endif