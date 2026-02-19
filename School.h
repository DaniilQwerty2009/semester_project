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
    Students students;
     
    Groups groups; 

    unsigned gIDcounter = 100;
    unsigned sIDcounter = 1000;

    DateConverter dateConverter;
    
    // нельзя вручную установить id. Исп. при копировании из файла
    void push_student(const unsigned& studentID, const char* lastname, const unsigned& groupID = 0);
    // для загрузки сейва - нет проверки на уникальность имени группы
    void push_group(const unsigned& ID, const char* name);

public:
    explicit School()
        {    }

    ~School()
        {    }

    inline Students::iterator students_begin()
    {
        return students.begin();
    }

    inline Students::iterator students_end()
    {
        return students.end();
    }

    inline Groups::iterator groups_begin()
    {
        return groups.begin();
    }

    inline Groups::iterator groups_end()
    {
        return groups.end();
    }

    inline size_t getStudentsAmmount()
    {
        return students.size();
    }

    unsigned push_student(const char* lastname, unsigned groupID = 0);

    template <typename Comparator>
        unsigned push_sudent_sorted(Comparator cmp, char* lastname, unsigned groupID = 0)
        {
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

    void pop_student(Students::iterator& sIter);

    unsigned push_group(const char* name);

    bool pop_group(Groups::iterator& gRef); // ошибка на непустую группу

    void push_visit(Students::iterator& sIter, const unsigned& day);

    template <typename Comparator>
        void sort_students(Comparator cmp)
    {
        students.sort(cmp);
    } 

    bool save(const char* filename = "Save.bin");

    void saveLoad(const char* filename = "Save.bin");

   


    


};




#endif