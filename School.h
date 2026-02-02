#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <cstdint>

#include "Student.h"
#include "Group.h"
#include "DateConverter.h"
#include "IDGenerator.h"

class School
{
private:

    size_t   capacity = 0;
    Student* head = nullptr;
    Student* tail = nullptr;


    DateConverter dateConverter;

    // передавать как парматеры в шаблон??
    IDGenerator   getStudentID;
    IDGenerator   getGroupID;


    // нельзя вручную установить id и группу. Исп. при копировании из файла
    void push_back(unsigned studentID, const char* lastname, unsigned groupID = 0);
    // Добавить группы в чтение и запись в файл - два режима: резервное копирование и перенос данных студентов???
public: 
    // полностью public! но ок в рамках задания
    Group* groupsMap = nullptr;

public:
    explicit School(unsigned startIDStudent = 100, unsigned startIDgroup = 10)
    :getStudentID(startIDStudent),
     getGroupID(startIDgroup)
        {    }

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
        
            explicit iterator(Student* ptr):pointer(ptr)
                {   }

            friend class School;
        public:

            explicit iterator():pointer(nullptr)
                {   }

            iterator(const iterator&) = default;
            iterator(iterator&) = default;

            
            // void     operator= (iterator& iterator);
            void     operator= (iterator iterator);
            bool     operator!=(iterator& iterator);
            bool     operator==(iterator& iterator);

            iterator operator--();
            iterator operator--(int);
            iterator operator++();
            iterator operator++(int);

            
            operator bool() const;
            Student& operator*() const;

        };

        inline iterator begin() const
        {
            return iterator(head);
        }

        inline iterator end() const
        {
            return iterator(nullptr);
        }

        inline iterator last() const
        {
            return iterator(tail);
        }

 
    inline size_t getCapacity() const
        { return capacity; }

    unsigned push_back(const char* lastname, unsigned groupID = 0);

    template <typename Compare> unsigned push_sorted(Compare comporator, const char* lastname, unsigned groupID = 0)
    {
        unsigned ID = push_back(getStudentID(), lastname, groupID);

        if(tail->prev)
        {
            if(comporator(tail->prev, tail))
                return ID;
        }

        Student* element = tail;
        Student* ptr = head;

        while(ptr != element)
        {
            if(comporator(element, ptr))
            {
                replace(ptr, element);
                return ID;
            }

            ptr = ptr->next;
        }

        return ID;
    }

    void pop(Student* studentPtr);

    // void pop(Student& studentRef);

    bool pop(const unsigned studentID);

    unsigned createGroup(const char* name);

    bool deleteGroup(Group* group); // ошибка на непустую группу

    void addVisit(Student* ptr, unsigned day);

    bool addVisit(unsigned studentID, unsigned day);

    // add groups tree!!!
    void addGroupVisit(const unsigned& groupID, unsigned day);

    void excludeFromGroup(const unsigned& studentID);

    void disband(const unsigned& groupID);

    void disbandAndPop(const unsigned& groupID);

    void printStudentInfo(Student* ptr) const;

    void printStudentInfo(const unsigned& studentID) const;

    void printVisitsInDate(const unsigned& day, const unsigned& mounth) const;

    void printVisitsInDate(const unsigned& day) const;

    bool writeToBin(const char* filename) const;

    template <typename IDGenerator>void readFromBIn(const char* filename)
    {
        std::ifstream fin(filename, std::ios::binary);
    
        
        unsigned groupid, visits, date;
        char name[Student::MAX_NAME_LEN];
        while(! fin.eof())
        {
            fin.ignore(sizeof(uint32_t));
            fin.read(name, Student::MAX_NAME_LEN);

            fin.read((char*)&groupid, sizeof(uint32_t));

            fin.read((char*)&visits, sizeof(uint32_t));

            push_back(getStudentID(), name, groupid);

            for(size_t i = 0; i < visits; ++i)
            {
                fin.read((char*)&date, sizeof(uint32_t));
                tail->days.push(date);
            }

            if(! fin.eof())
                break;
            
        }

}

    void copySchoolFromBin(const char* filename);


    // компрораторы
    class ByVisits
    {
    public:
        bool operator()(const Student* a, const Student* b) const
        {
            return a->visits < b->visits;
        }
        bool operator()(const Student* a, const unsigned& b) const
        {
            return a->visits < b;
        }
        bool operator()(const unsigned& a, const Student* b) const
        {
            return a < b->visits;
        }
    };

    class ByLastname
    {
    public:
        bool operator()(const Student* a, const Student* b) const
        {
            return std::strcmp(a->lastname, b->lastname) < 0;
        }
        bool operator()(const Student* a, const char* b)
        {
            return std::strcmp(a->lastname, b) < 0;
        }
        bool operator()(const char* a, const Student* b)
        {
            return std::strcmp(a, b->lastname) < 0;
        }
    };

    class ByStudentID
    {
    public:
        bool operator()(const Student* a, const Student* b) const
        {
            return a->ID < b->ID;
        }
        bool operator()(const Student* a, const unsigned& b)
        {
            return a->ID < b;
        }
        bool operator()(const unsigned& a, const Student* b)
        {
            return a < b->ID;
        }
    };


    void replace(Student* destination, Student* element);


    // сортировка
    template <typename Compare> 
        void sort(Compare cmp = School::ByLastname()) //????
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