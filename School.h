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
            bool operator!();

            void operator=(Student* iterator);
            bool operator!=(Student* iterator);
            bool operator==(Student* iterator);
            
            iterator operator --();
            iterator operator --(int);
            iterator operator++();
            iterator operator++(int);

            const Student& operator*() const;

            const char*         getLastname() const; 

            const unsigned&     getID() const; 

            const size_t&       getVisits() const; 

            const unsigned*     getDates() const; 

            const unsigned&     getGroup() const; 

            void                printInfo() const;

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

    void addVisit(const iterator& iterator, unsigned day);

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

    void replace(iterator destination, iterator element)
    {
        if(!element)
            return;

        if(destination == element)
            return;

        if(destination == end())
        {
            if(element == tail)
                return;

            if(element == head)
            {
                Student* newHead = element.pointer->next;

                tail->next = element.pointer;
                element.pointer->prev = tail;
                tail = element.pointer;

                head = newHead;
                head->prev = nullptr;

                return;
            }
            else
            {
                element.pointer->next->prev = element.pointer->prev;
                element.pointer->prev->next = element.pointer->next;

                tail->next = element.pointer;
                element.pointer->prev = tail;
                
                tail = element.pointer;
                tail->next = nullptr;

                return;
            }
        }

        if(destination == head)
        {
            if(element == tail)
            {
                Student* newTail = element.pointer->prev;

                head->prev = element.pointer;
                element.pointer->next = head;

                tail = newTail;
                tail->next = nullptr;

                head = element.pointer;
                head->prev = nullptr;

                return;
            }
            else
            {
                element.pointer->next->prev = element.pointer->prev;
                element.pointer->prev->next = element.pointer->next;

                head->prev = element.pointer;
                
                head = element.pointer;
                head->prev = nullptr;

                return;
            }
        }

        else
        {  
            if(element != head)
                {
                element.pointer->prev->next = element.pointer->next;
                }
            else
                head = element.pointer->next;

            if(element != tail)
                element.pointer->next->prev = element.pointer->prev;
            else
                tail = element.pointer->prev;

            element.pointer->prev = destination.pointer->prev;
            destination.pointer->prev->next = element.pointer;

            element.pointer->next = destination.pointer;
            destination.pointer->prev = element.pointer;

        }
        
    }

    // сортировка
    // template <typename Compare> void sort(Compare cmp)
    // {
    //     iterator sotrBorder = begin();
    //     sotrBorder++;

    //     while(sotrBorder)
    //     {
    //         iterator sortPart = --sotrBorder;

    //         while( !cmp(*sotrPart, *sortBorder))
    //         {
    //             if(sortPart == begin())
    //             {

    //             }
    //         }


    //         sotrBorder++;
    //     }
    // }
};








#endif