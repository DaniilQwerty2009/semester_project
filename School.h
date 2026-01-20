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

    // методы для сортировки
    Student* split(Student* head);
    template <typename Compare> Student* merge(Student* a, Student* b, Compare cmp)
        {
            if(!a) return b;
            if(!b) return b;

            if(cmp(a, b) || (!cmp(a, b) && !cmp(b, a)))
            {
                a->next = merge(a->next, b, cmp);
                
                if(a->next)
                    a->next->prev = a;

                a->prev = nullptr;

                return a;
            }

            else
            {
                b->next = merge(a, b->next, cmp);

                if(b->next)
                    b->next->prev = b;

                b->prev = nullptr;

                return b;
            }
        }
    template <typename Compare> Student* mergeSort(Student* head, Compare cmp)
    {
        if(!head || !head->next)
            return head;

        Student* right = split(head);

        mergeSort(head, cmp);
        mergeSort(right, cmp);

        return merge(head, right, cmp);
    }

public:
    // валидность итераторов. когда??
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
            
            iterator operator --();
            iterator operator --(int);
            iterator operator++();
            iterator operator++(int);

            const unsigned&       operator*() const;

            const char*           getLastname() const; 

            const unsigned&       getID() const; 

            const size_t&         getVisits() const; 

            const unsigned*       getDates() const; 

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

    // add groups tree!!!
    bool addGroupVisit(unsigned groupID, unsigned day);

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

    inline Student* last() const
    {
        return tail;
    }


    // компрораторы
    class ByVisits
    {
    public:
        // ПОЧЕМУ ВИДИМ STUDENT??
        bool operator()(Student& a,  Student& b) const
        {
            return a.visits < b.visits;
        }
    };

    class ByLastname
    {
    public:
        bool operator()(Student& a, Student& b)
        {
            static int index = 0; 

            if(  !(a.lastname[index] < b.lastname[index])  &&  !(b.lastname[index] < a.lastname[index])  )
            {
                index++;
                operator()(a, b);
            }    

            return (a.lastname[index] < b.lastname[index]);
        }
    };

    // сортировка
    template <typename Compare> void sort(Compare cmp)
    {
        head = mergeSort(head, cmp);
    }
};








#endif