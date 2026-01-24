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

        friend class ByLastname;
    };


    Student* head = nullptr;
    Student* tail = nullptr;

   
public:
    // валидность итераторов. когда??
    class iterator
        {
        private:
            Student* pointer;
        public:
            iterator(School::Student* ptr = nullptr):pointer(ptr)
                {   }
            iterator(iterator& iterator) = default;

            // поменять на ссылки
            void operator=(iterator iterator);
            bool operator!=(iterator iterator);
            bool operator==(iterator iterator);
            explicit operator bool() const;

            void operator=(Student* iterator);
            bool operator!=(Student* iterator);
            bool operator==(Student* iterator);
          
            iterator operator --();
            iterator operator --(int);
            iterator operator++();
            iterator operator++(int);

            const Student& operator*() const;

        //     // убрать
        //     const char*         getLastname() const; 

        //     const unsigned&     getID() const; 

        //     const size_t&       getVisits() const; 

        //     const unsigned*     getDates() const; 

        //     const unsigned&     getGroup() const; 

        //     void                printInfo() const;

        //     friend class School;
        };

    School()
        {   }

    ~School()
    {
        Student* ptr;

        while(ptr)
        {
            Student* temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
 

    void push_back(unsigned studentID, const char* lastname, unsigned groupID = 0);

    void pop(Student* studentPtr);

    bool pop(unsigned studentID);

    void addVisit(const Student* ptr, unsigned day);

    bool addVisit(unsigned studentID, unsigned day);

    // add groups tree!!!
    void addGroupVisit(unsigned groupID, unsigned day);

    void printStudentInfo(Student* ptr) const;

    void printStudentInfo(unsigned studentID) const;

    inline Student* begin() const
    {
        return head;
    }

    inline Student* end() const
    {
        return nullptr;
    }

    inline Student* last() const
    {
        return tail;
    }


    // компрораторы
    class ByVisits
    {
    public:
        // ПОЧЕМУ ВИДИМ STUDENT??
        bool operator()(Student* a,  Student* b) const
        {
            return a->visits < b->visits;
        }
    };

    class ByLastname
    {
    public:
        bool operator()(Student* a, Student* b)
        {
            return std::strcmp(a->lastname, b->lastname) < 0;
        };
    };

    void replace(Student* destination, Student* element);


    // сортировка
    template <typename Compare> void sort(Compare cmp)
    {
        if(!head || !head->next)
            return;

        Student* sotrBorder = head;
        Student* iter = sotrBorder->next;
        Student* inSortedPart;

        while(iter)
        {
            if(cmp(sotrBorder, iter))   
            {
                sotrBorder = sotrBorder->next;
                iter = iter->next;
                continue;
            }


            else
            {
                inSortedPart = sotrBorder;

                while( inSortedPart->prev != nullptr && cmp(iter, inSortedPart->prev))
                    inSortedPart = inSortedPart->prev;
                
                replace(inSortedPart, iter);

                iter = sotrBorder->next;
            }
        }
    }


};








#endif