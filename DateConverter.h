// Класс конвертирует дата:месяц в день с начала года

#ifndef DATE_CONVERTER_H
#define DATE_CONVERTER_H


class DateConverter
{
public:
    const unsigned mounthLen[12] = {31, 28 ,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const char* monthName[12] = {"Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентября", "Октября", "Ноября", "Декабря"};
public:
    explicit DateConverter()
        {   }

    // Возвращает день с начала года по дате.
    // Генерирует WrongNumber при неверном дне или месяце
    unsigned date_to_day(const unsigned& day, const unsigned& mounth) const
    {
        if(day > mounthLen[mounth] || day <= 0)
            throw WrongNumber();

        if(mounth > 12 || mounth <= 0)
            throw WrongNumber();

        // результат = кол-во дней в целых месяцах + остаток дней
        unsigned result = 0;
        for(unsigned i = 0; i < mounth - 1; ++i)
            result += mounthLen[i];

        result += day;
        return result;        
    }

    // записывает в dayOfMounth, mounth день и месяц по дню(day) с начала года
    void day_to_date(unsigned day, unsigned& dayOfMounth, unsigned& mounth) const
    {
        if(day > 365)
            day = day - 365;
        mounth = 1;
        while(day > mounthLen[mounth-1])
        {
            mounth++;
            day -= mounthLen[mounth-1];
        }   
        
        dayOfMounth = day;
    }
};


#endif