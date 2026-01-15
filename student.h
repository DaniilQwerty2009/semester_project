#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

struct Student
{
private:
    
    const unsigned ID;

    char* lastname = nullptr;
    unsigned groupID;

    unsigned visits = 0;
    unsigned* dates = nullptr;

public:
    Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
        :ID(studentID),
        groupID(groupID)
        { 
            size_t len = std::strlen(lastname) + 1;
            this->lastname = new char[len]; 
            std::strcpy(this->lastname, lastname); 
        }

    ~Student()
    {
        delete[] lastname;
        delete[] dates;
    }

    const unsigned getID()
        { return ID; }

    const char* getLastname()
        { return lastname; }

    unsigned getGroup()
        { return groupID; }

    unsigned getVisits()
        { return visits; }

    inline void increaseVisits()
        { ++visits; }

    inline void changeVisits(int unsigned visits)
        { this->visits = visits; }

    void printInfo()
    {
        std::cout << ID << '/' << lastname << '/';
        std::cout << groupID << '/' << visits << std::endl;
    }

};




#endif