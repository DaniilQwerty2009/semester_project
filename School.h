#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "VisitDays.h"
#include "DateConverter.h"

#define MAX_NAME_LEN 20

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

        Student(unsigned studentID)
        :ID(studentID), groupID(0)
        {   }

        Student(unsigned studentID, const char* lastname, unsigned groupID = 0)
        :ID(studentID), groupID(groupID)
        {
            if(strlen(lastname) < MAX_NAME_LEN)
            {
                this->lastname = new char[std::strlen(lastname) + 1];
                std::strcpy(this->lastname, lastname);
                std::strcat(this->lastname, "\0");
            }
            else
            {
                this->lastname = new char[MAX_NAME_LEN];
                std::strncpy(this->lastname, lastname, MAX_NAME_LEN - 1);
                std::strcat(this->lastname, "\0");
            }
            
        }

        ~Student()
        {
            delete[] lastname;
        }

    };


    size_t capacity = 0;
    Student* head = nullptr;
    Student* tail = nullptr;

    DateConverter converter;

   
public:
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
            void     operator=(iterator iterator);
            bool     operator!=(iterator iterator);
            bool     operator==(iterator iterator);

            void     operator=(Student* iterator);
            bool     operator!=(Student* iterator);
            bool     operator==(Student* iterator);
          
            iterator operator --();
            iterator operator --(int);
            iterator operator++();
            iterator operator++(int);

            explicit       operator bool() const;
            const Student& operator*() const;

        };

 
    inline size_t getCapacity() const
        { return capacity; }

    void push_back(unsigned studentID, const char* lastname, unsigned groupID = 0);

    template <typename Compare> void push_sorted(Compare comporator, unsigned studentID, const char* lastname, unsigned groupID = 0)
    {
        push_back(studentID, lastname, groupID);

        if(tail->prev)
        {
            if(comporator(tail->prev, tail))
                return;
        }

        Student* element = tail;
        Student* ptr = head;

        while(ptr != element)
        {
            if(comporator(element, ptr))
            {
                replace(ptr, element);
                return;
            }

            ptr = ptr->next;
        }
    }

    void pop(Student* studentPtr);

    bool pop(const unsigned studentID);

    void addVisit(Student* ptr, unsigned day);

    bool addVisit(unsigned studentID, unsigned day);

    // add groups tree!!!
    void addGroupVisit(unsigned groupID, unsigned day);

    void excludeFromGroup(unsigned studentID);

    void disbandGroup(unsigned groupID);

    void disbandAndPop(unsigned groupID);

    void printStudentInfo(Student* ptr) const;

    void printStudentInfo(const unsigned& studentID) const;

    void printVisitsInDate(const unsigned& day, const unsigned& mounth) const;

    void printVisitsInDate(const unsigned& day) const;

    bool writeToBin(const char* filename) const;

    template <typename IDGenerator>void readFromBIn(const char* filename, IDGenerator getID)
    {
        std::ifstream fin(filename, std::ios::binary);
    
        // fout.read((char*)capacity, sizeof(capacity));


        unsigned groupid, visits, date;
        char* name;
        while(! fin.eof())
        {
            // fin.read((char*)id, sizeof(Student::ID));
            fin.getline(name, MAX_NAME_LEN,'\0');

            fin.read((char*)groupid, sizeof(Student::groupID));
            fin.read((char*)visits, sizeof(Student::visits));

            push_back(getID(), name, groupid);

            for(size_t i = 0; i < visits; ++i)
            {
                fin.read((char*)date, sizeof(Student::dates.datesArray));
                tail->dates.push(date);
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

    inline Student* last() const
    {
        return tail;
    }


    // компрораторы
    class ByVisits
    {
    public:
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