#ifndef DATE_CONVERTER_H
#define DATE_CONVERTER_H


class DateConverter
{
private:
    const unsigned mounthLen[12] = {31, 28 ,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // const char* monthName[12] = { "Сент", "Окт", "Нояб", "Дек", "Янв", "Фев", "Март", "Апр", "Май", "Июнь", "Июль", "Авг"};
public:
    explicit DateConverter()
        {   }

    const char* DayToString(unsigned& day) const;



    unsigned DateToDay(const unsigned& day, const unsigned& mounth) const
    {
        if(day > mounthLen[mounth])
            return 0; // Исключение

        if(mounth > 12)
            return 0; // Исключение

        unsigned result = 0;
        for(unsigned i = 0; i < mounth - 1; ++i)
            result += mounthLen[i];

        result += day;
        return result;        
    }
};


#endif