#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <cstring>

class School
{
private:
    struct Student
    {
        const unsigned ID;

        char* lastname = nullptr;
        unsigned groupID;

        size_t visits = 0;
        unsigned short* visitsDates = nullptr;

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
            delete[] visitsDates;
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

            Student* operator++();
            Student* operator++(int);

            const unsigned&       operator*() const;

            const char*           getLastname() const; 

            const unsigned&       getID() const; 

            const size_t&       getVisits() const; 

            unsigned short*       getVisitsDates() const; 

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
 

    void push_back(unsigned studentID, const char* lastname, unsigned groupID = 0)
    {
        if(!head)
        {
            head = new Student(studentID, lastname, groupID);
            tail = head;
        }
        else
        {
            tail->next = new Student(studentID, lastname, groupID);
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
        }

    }

    void pop(iterator iterator)
    {
        if(iterator.pointer)
        {
            if(iterator.pointer == head && head->next == nullptr)
            {
                delete iterator.pointer;
                iterator.pointer = nullptr;

                head = nullptr;

                return;
            }

            if(iterator.pointer == head)
            {
                head = head->next;
                head->prev = nullptr;

                delete iterator.pointer;
                iterator.pointer = nullptr;

                return;
            }
            if(iterator.pointer == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;

                delete iterator.pointer;
                iterator.pointer = nullptr;

                return;
            }
            else
            {
            iterator.pointer->prev->next = iterator.pointer->next;
            iterator.pointer->next->prev = iterator.pointer->prev;

            delete iterator.pointer;
            iterator.pointer = nullptr;

            return;
            }
        }

    }

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