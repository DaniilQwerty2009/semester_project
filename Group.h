#ifndef GROUP_H
#define GROUP_H

#include <cstring>

struct Group
{
private:
    Group* next = nullptr;
    Group* prev = nullptr;

    friend class School;

public:
    enum {MAX_NAME_LEN = 40}; 

    unsigned key;
    char* value = nullptr; // mutable?

    Group(unsigned key, const char* value)
    {
        this->key = key;

        size_t strLen = sizeof(value) + 1;

        if(strLen <= MAX_NAME_LEN)
        {
            this->value = new char[strLen];
            strncpy(this->value, value, strLen);
        }
        else
        {
            this->value = new char[MAX_NAME_LEN];
            strncpy(this->value, value, MAX_NAME_LEN);
            this->value[MAX_NAME_LEN - 1] = '\0'; 
        }     
    }

    ~Group()
    {
        delete value;
    }

    bool operator==(Group* other)
    {
        return key == other->key;
    }

    bool operator!=(Group* other)
    {
        return key != other->key;
    }

};




#endif