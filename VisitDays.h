#ifndef VISIT_DAYS_H
#define VISIT_DAYS_H

#include <iostream>
#include <exception>

 struct VisitDays
    {
    public:
        enum averageStudyDays {studyDays = 165};

        size_t elementsQty = 0;
        unsigned* dates = nullptr;

        VisitDays(size_t length = studyDays): len(length)
        {

            dates = new unsigned[len];
        }

        ~VisitDays()
        {
            delete[] dates;
        }

        // exeption!!
        const unsigned& operator[](unsigned index)
        {
            // if(index >= elementsQty)
            //     return 0;

            return dates[index];
        }

    
        void push(unsigned day)
        {
            if(elementsQty == len)
                expand();

            dates[elementsQty++] = day;
        }



    private:
        size_t len;

        void expand()
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
            
            for(size_t i = 0; i < elementsQty; ++i)
                newVisitsDates[i] = dates[i];

            delete[] dates;

            dates = newVisitsDates;
        }
    };


    


#endif