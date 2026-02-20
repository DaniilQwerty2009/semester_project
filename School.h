// Основной класс, поля: список студентов, групп, объект-конвертер дат, счетчики ID

#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <fstream>
#include <cstdint>

#include "Students.h"
#include "Groups.h"
#include "SchoolExeptions.h"
#include "DateConverter.h"


class School
{
private:
    Students students;              // список студентов
     
Groups groups;                      // список групп 

    unsigned gIDcounter = 100;      // счтечик ID для групп
    unsigned sIDcounter = 1000;     // счтечик ID для групп

    DateConverter dateConverter;    // конвертер дат: день с начала года <-> число:месяц
    
    // Перегруженый push_student для save_load. В других случаях задавать ID вручную запрещенно
    void push_student(const unsigned& studentID, const char* lastname, const unsigned& groupID = 0);
    // Перегруженый push_group для save_load. Нет проверки на уникальность имени
    void push_group(const unsigned& ID, const char* name);

public:
    explicit School()
        {    }

    ~School()
        {    }

    // Итератор на первый элемент Students 
    inline Students::iterator students_begin()
    {
        return students.begin();
    }

    // Итератор на следующий за последним элемент Students 
    inline Students::iterator students_end()
    {
        return students.end();
    }

    // Итератор на первый элемент Groups 
    inline Groups::iterator groups_begin()
    {
        return groups.begin();
    }

    // Итератор на следующий за последним элемент Groups 
    inline Groups::iterator groups_end()
    {
        return groups.end();
    }

    // Общее колличество студентов
    inline size_t getStudentsAmmount()
    {
        return students.size();
    }

    unsigned push_student(const char* lastname, unsigned groupID = 0);

    // Добавление студента про признаку сортировки cmp - компаратор в области Students
    template <typename Comparator>
        unsigned push_sudent_sorted(Comparator cmp, char* lastname, unsigned groupID = 0)
        {
            if(lastname == nullptr)
                throw EmptyPtr();

            // исключение - нет такой группы
            // обработка - присваивание группе 0
            Groups::iterator gIter(groups.begin());

            while(gIter)
            {
                if((*gIter).ID == groupID)
                    break;

                gIter++;
            }

            if(!gIter)
                groupID = 0;

            students.push_sorted(cmp, sIDcounter, lastname, groupID);
            sIDcounter++;
            return (sIDcounter - 1);
        }

    void pop_student(Students::iterator& sIter) noexcept;

    unsigned push_group(const char* name);

    void pop_group(Groups::iterator& gIter);

    void push_visit(Students::iterator& sIter, const unsigned& day) noexcept;

    // Сортировка списка студентов по признаку cmp - компаратор в области Students
    template <typename Comparator>
        void sort_students(Comparator cmp) noexcept
    {
        students.sort(cmp);
    } 

    bool save(const char* filename = "Save.bin") const noexcept;

    void saveLoad(const char* filename = "Save.bin") noexcept;

   


    


};




#endif