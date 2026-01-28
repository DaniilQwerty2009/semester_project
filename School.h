#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <cstdint>

#include "Student.h"
#include "DateConverter.h"

class School
{
private:

    size_t capacity = 0;
    Student* head = nullptr;
    Student* tail = nullptr;

    DateConverter converter;

   
public:
    explicit School()
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
            explicit iterator(Student* ptr = nullptr):pointer(ptr)
                {   }
            iterator(iterator& iterator) = default;

            // поменять на ссылки?
            void     operator= (iterator iterator);
            bool     operator!=(iterator iterator);
            bool     operator==(iterator iterator);

            iterator operator--();
            iterator operator--(int);
            iterator operator++();
            iterator operator++(int);

            
            operator bool() const;
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

    void disband(unsigned groupID);

    void disbandAndPop(unsigned groupID);

    void printStudentInfo(Student* ptr) const;

    void printStudentInfo(const unsigned& studentID) const;

    void printVisitsInDate(const unsigned& day, const unsigned& mounth) const;

    void printVisitsInDate(const unsigned& day) const;

    bool writeToBin(const char* filename) const;

    template <typename IDGenerator>void readFromBIn(const char* filename, IDGenerator getID)
    {
        std::ifstream fin(filename, std::ios::binary);
    
        
        unsigned groupid, visits, date;
        char name[MAX_NAME_LEN];
        while(! fin.eof())
        {
            fin.ignore(sizeof(uint32_t));
            fin.read(name, MAX_NAME_LEN);

            fin.read((char*)&groupid, sizeof(uint32_t));

            fin.read((char*)&visits, sizeof(uint32_t));

            push_back(getID(), name, groupid);

            for(size_t i = 0; i < visits; ++i)
            {
                fin.read((char*)&date, sizeof(uint32_t));
                tail->dates.push(date);
            }

            if(! fin.eof())
                break;
            
        }

}

    void readFromBin(const char* filename);

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

    class EqualByID
    {
        bool opeartor(iterator iter, const unsigned& studentID)
        {
            return (*iter).ID == studentID;
        }
    };

    class EqualByName
    {
        bool opeartor(iterator iter, const char* name)
        {
            return std::strcmp((*iter).lastname, name);
        }
    };


    void replace(Student* destination, Student* element);


    // сортировка
    template <typename Compare> 
        void sort(Compare cmp = School::ByLastname())
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