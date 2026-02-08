#ifndef GROUP_H
#define GROUP_H

#include <cstring>
#include "Algorithm.h"

class Groups
{
private:
    struct Group
    {
    private:
        Group* next = nullptr;

        friend class Groups;
    public:
        unsigned ID;
        char* name = nullptr;

        explicit Group(const unsigned& ID, const char* name)
        {
            this->ID = ID;

            size_t sLen = strlen(name) + 1;

            if(sLen <= MAX_NAME_BYTES)
            {
                this->name = new char[sLen];
                strcpy(this->name, name);

                size_t safePrefix = SchoolAlg::safeStrPrefix(this->name, MAX_NAME_BYTES);
                this->name[safePrefix] = '\0';
            }
            else
            {
                this->name = new char[MAX_NAME_BYTES];
                strncpy(this->name, name, MAX_NAME_BYTES);

                size_t safePrefix = SchoolAlg::safeStrPrefix(this->name, MAX_NAME_BYTES);
                this->name[safePrefix] = '\0';
            }     
        }

        ~Group()
        {
            delete[] name;
        }

        Group(Group& other)            = delete;
        Group& operator=(Group& other) = delete;

    };

    Groups::Group* head = nullptr;

    friend class School;
    
public:
    enum {MAX_NAME_BYTES = 40};

    Groups()
        {   }

    ~Groups()
    {
        Group* ptr = head;

        while(ptr)
        {
            head = head->next;
            delete ptr;
            ptr = head;
        }
    }

    Groups(Groups& other) = delete;
    Groups& operator=(Groups& other) = delete;
    
    class iterator
    {
    private:
        Group* pointer = nullptr;

        explicit iterator(Group* ptr): pointer(ptr)
            {   }

        friend class Groups;

    public:

    explicit iterator():pointer(nullptr)
            {   }

        iterator(const iterator&) = default;
        iterator(iterator&) = default;

        
        void     operator= (iterator iterator);
        bool     operator!=(iterator& iterator);
        bool     operator==(iterator& iterator);

        iterator operator++();
        iterator operator++(int);
 
        operator bool() const;
        Group& operator*() const;        
    };

    inline iterator begin()
    { 
        return iterator(head); 
    }

    inline iterator end()
    { 
        return iterator(nullptr); 
    }


    void push(const unsigned& ID, const char* name)
    {
        if(!head)
        {
            head = new Group(ID, name);
            head->next = nullptr; 
        }
        else
        {
            Group* ptr = head;

            while(ptr->next != nullptr)
            {
                if(strcmp(ptr->name, name) == 0)
                    return;                    //exeption!!!!!

                ptr = ptr->next;
            }
            if(strcmp(ptr->name, name) == 0)
                    return;                      //exeption!!!!!
            
            ptr->next = new Group(ID, name);
            ptr->next->next = nullptr;
        }
    }

    void pop(Group* ptr)
    {
        if(!ptr || !head)
            return;

        if(ptr == head)
        {
            delete head;
            head = nullptr;
        }

        Group* prevPtr = head;

        while(prevPtr->next != ptr)
            prevPtr = prevPtr->next;

        prevPtr->next = ptr->next;
        delete ptr;
    }
};


#endif