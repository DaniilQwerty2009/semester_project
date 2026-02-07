#ifndef GROUP_H
#define GROUP_H

#include <cstring>
#include "Algorithm.h"

struct Group
{
    enum {MAX_NAME_LEN = 40};

    unsigned ID;
    char* name = nullptr;

    Group* next = nullptr;
    Group* prev = nullptr;

    Group(const unsigned& ID, const char* name)
    {
        this->ID = ID;

        size_t sLen = strlen(name) + 1;

        if(sLen <= MAX_NAME_LEN)
        {
            this->name = new char[sLen];
            strcpy(this->name, name);
        }
        else
        {
            this->name = new char[MAX_NAME_LEN];
            strncpy(this->name, name, MAX_NAME_LEN);

            size_t safePrefix = SchoolAlg::safeStrPrefix(this->name, MAX_NAME_LEN);
            this->name[safePrefix] = '\0';
        }     
    }

    ~Group()
    {
        delete[] name;
    }

    Group(Group& other)            = delete;
    Group& operator=(Group& other) = delete;

    bool operator==(Group* other)
    {
        return ID == other->ID;
    }

    bool operator!=(Group* other)
    {
        return ID != other->ID;
    }

    // char& operator[](const unsigned& ID)
    // {
    //     Group* ptr = this;

    //     while(ptr)
    //     {
    //         if(this->ID == ID)
    //             return *name;
    //     }
    // }

    // char& operator=(const char* val)
    // {
    //     if(strlen(val) >= MAX_NAME_LEN)
    //     {
    //         delete[] name;
    //         char* name = new char[MAX_NAME_LEN];
    //         strncpy(name, val, MAX_NAME_LEN);
    //         this->name[MAX_NAME_LEN - 1] = '\0';

    //         return *name;
    //     }
    //     else if(strlen(val) > strlen(name))
    //     {
    //         delete[] name;
    //         name = new char[strlen(val) + 1];
    //         strcpy(name, val);

    //         return *name;
    //     }
    //     else
    //     {
    //         strcpy(name, val);

    //         return *name;
    //     }
    // }

};




#endif