#ifndef GROUP_H
#define GROUP_H

#include <cstring>

struct Group
{
    Group* next = nullptr;
    Group* prev = nullptr;

    enum {MAX_NAME_LEN = 40}; 

    unsigned ID;
    char* name = nullptr; // mutable?
    // unsigned capacity = 0;

    Group(unsigned ID, const char* name)
    {
        this->ID = ID;

        size_t strLen = sizeof(name) + 1;

        if(strLen <= MAX_NAME_LEN)
        {
            this->name = new char[strLen];
            strcpy(this->name, name);
        }
        else
        {
            this->name = new char[MAX_NAME_LEN];
            strncpy(this->name, name, MAX_NAME_LEN);
            this->name[MAX_NAME_LEN - 1] = '\0'; 
        }     
    }

    ~Group()
    {
        delete[] name;
    }

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

    char& operator=(const char* val)
    {
        if(strlen(val) >= MAX_NAME_LEN)
        {
            delete[] name;
            char* name = new char[MAX_NAME_LEN];
            strncpy(name, val, MAX_NAME_LEN);
            this->name[MAX_NAME_LEN - 1] = '\0';

            return *name;
        }
        else if(strlen(val) > strlen(name))
        {
            delete[] name;
            name = new char[strlen(val) + 1];
            strcpy(name, val);

            return *name;
        }
        else
        {
            strcpy(name, val);

            return *name;
        }
    }

};




#endif