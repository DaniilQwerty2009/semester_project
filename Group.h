#ifndef GROUP_H
#define GROUP_H

#include <cstring>

struct Group
{
    Group* next = nullptr;
    Group* prev = nullptr;

    enum {MAX_NAME_LEN = 40}; 

    unsigned key;
    char* value = nullptr; // mutable?
    // unsigned capacity = 0;

    Group(unsigned key, const char* value)
    {
        this->key = key;

        size_t strLen = sizeof(value) + 1;

        if(strLen <= MAX_NAME_LEN)
        {
            this->value = new char[strLen];
            strcpy(this->value, value);
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
        delete[] value;
    }

    bool operator==(Group* other)
    {
        return key == other->key;
    }

    bool operator!=(Group* other)
    {
        return key != other->key;
    }

    // добавить проверку на выход за передлы
    const char operator[](const unsigned& key)
    {
        Group* ptr = this;

        while(ptr)
        {
            if(this->key == key)
                return *value;
        }
    }

    char& operator=(const char* val)
    {
        if(strlen(val) >= MAX_NAME_LEN)
        {
            delete[] value;
            char* value = new char[MAX_NAME_LEN];
            strncpy(value, val, MAX_NAME_LEN);
            this->value[MAX_NAME_LEN - 1] = '\0';

            return *value;
        }
        else if(strlen(val) > strlen(value))
        {
            delete[] value;
            value = new char[strlen(val) + 1];
            strcpy(value, val);

            return *value;
        }
        else
        {
            strcpy(value, val);

            return *value;
        }
    }

};




#endif