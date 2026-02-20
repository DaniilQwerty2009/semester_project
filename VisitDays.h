// Динамический массив дат в формате дня с начала года.
// Поля: алрес массива, размер, число элементов

#ifndef VISIT_DAYS_H
#define VISIT_DAYS_H

#include <iostream>
#include <exception>

struct VisitDays
    {
    public:
        enum averageStudyDays {studyDays = 165}; // Среднее кол-во учебных дней в году - размер массива по умолчанию

        unsigned* datesArray = nullptr;

        VisitDays(size_t length = studyDays): len(length)
        {

            datesArray = new unsigned[len];
        }

        ~VisitDays()
        {
            delete[] datesArray;
        }

        VisitDays(VisitDays& other) = delete;
        VisitDays& operator=(VisitDays& other) = delete;

        void push(unsigned day) noexcept
        {
            if(capacity == len)
                memory_reallocation();

            datesArray[capacity++] = day;
        }

        // Колличество элементов массива
        size_t size() const
        {
            return capacity;
        }

    private:
        size_t capacity = 0;
        size_t len;

        // realloc
        void memory_reallocation()
        {
            len *= 2;

            unsigned* newVisitsDates;
            try
            {
                newVisitsDates = new unsigned[len];
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            for(size_t i = 0; i < capacity; ++i)
                newVisitsDates[i] = datesArray[i];

            delete[] datesArray;

            datesArray = newVisitsDates;
        }
    };


    


#endif