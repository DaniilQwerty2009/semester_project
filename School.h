#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <cstdint>

#include "Student.h"
#include "Groups.h"
#include "DateConverter.h"
// #include "IDGenerator.h"

class School
{
private:

    size_t   capacity = 0;
    Student* head = nullptr;
    Student* tail = nullptr;

    unsigned gIDcounter = 100;
    unsigned sIDcounter = 1000;

    DateConverter dateConverter;

    size_t groupsCapacity = 0;
    Groups groups; 
    
    // нельзя вручную установить id. Исп. при копировании из файла
    void push_back(const unsigned& studentID, const char* lastname, const unsigned& groupID = 0);
    // для загрузки сейва - нет проверки на уникальность имени группы
    void push_group(const unsigned& ID, const char* name);

public:
    explicit School()
        {    }

    ~School()
    {
        while(head)
        {
            Student* temp = head;
            head = head->next;
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

    inline Groups::iterator groups_begin()
    {
        return groups.begin();
    }

    inline Groups::iterator groups_end()
{
    return groups.end();
}

    inline size_t getCapacity() const
        { return capacity; }

    unsigned push_back(const char* lastname, unsigned groupID = 0);

    template <typename Compare> unsigned push_sorted(Compare comporator, const char* lastname, const unsigned& groupID = 0)
    {
        unsigned ID = push_back(lastname, groupID);

        if(tail->prev)
        {
            if(comporator(*tail->prev, *tail))
                return ID;
        }

        Student* element = tail;
        Student* ptr = head;

        while(ptr != element)
        {
            if(comporator(*element, *ptr))
            {
                replace(ptr, element);
                return ID;
            }

            ptr = ptr->next;
        }

        return ID;
    }

    void pop(Student* sPtr);

    unsigned push_group(const char* name);

    bool pop_group(Groups::Group& gRef); // ошибка на непустую группу

    void push_visit(Student* sPtr, const unsigned& day);

    bool save(const char* filename = "Save.bin");

    void saveLoad(const char* filename = "Save.bin");

    // компрораторы
    class ByVisits
    {
    public:
        bool operator()(const Student& a, const Student& b) const
        {
            return a.visits < b.visits;
        }

        bool operator()(const Student& a, const unsigned& b) const
        {
            return a.visits < b;
        }

        bool operator()(const unsigned& a, const Student& b) const
        {
            return a < b.visits;
        }
    };

    class ByLastname
    {
    public:
        bool operator()(const Student& a, const Student& b) const
        {
            return std::strcmp(a.lastname, b.lastname) < 0;
        }

        bool operator()(const Student& a, const char* b) const
        {
            return std::strcmp(a.lastname, b) < 0;
        }

        bool operator()(const char* a, const Student& b) const
        {
            return std::strcmp(a, b.lastname) < 0;
        }
    };

    class ByStudentID
    {
    public:
        bool operator()(const Student& a, const Student& b) const
        {
            return a.ID < b.ID;
        }

        bool operator()(const Student& a, const unsigned& b) const
        {
            return a.ID < b;
        }

        bool operator()(const unsigned& a, const Student& b) const
        {
            return a < b.ID;
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
            if(cmp(*sotrBorder, *iter) || (!cmp(*sotrBorder, *iter) && !cmp(*iter, *sotrBorder)))   
            {
                sotrBorder = sotrBorder->next;
                iter = iter->next;
                continue;
            }


            else
            {
                inSortedPart = sotrBorder;

                while( inSortedPart->prev != nullptr && cmp(*iter, *inSortedPart->prev))
                    inSortedPart = inSortedPart->prev;
                
                replace(inSortedPart, iter);

                iter = sotrBorder->next;
            }
        }
    }


};




#endif