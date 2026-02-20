// Класс конвертирует дата:месяц в день с начала года

#ifndef DATE_CONVERTER_H
#define DATE_CONVERTER_H


class DateConverter
{
private:
    const unsigned mounthLen[12] = {31, 28 ,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // const char* monthName[12] = {"Янв", "Фев", "Март", "Апр", "Май", "Июнь", "Июль", "Авг", "Сент", "Окт", "Нояб", "Дек"};
public:
    explicit DateConverter()
        {   }

    // Возвращает день с начала года по дате.
    // Генерирует WrongDate при неверном дне или месяце
    unsigned date_to_day(const unsigned& day, const unsigned& mounth) const
    {
        if(day > mounthLen[mounth] || day <= 0)
            throw WrongDate();

        if(mounth > 12 || mounth <= 0)
            throw WrongDate();

        // результат = кол-во дней в целых месяцах + остаток дней
        unsigned result = 0;
        for(unsigned i = 0; i < mounth - 1; ++i)
            result += mounthLen[i];

        result += day;
        return result;        
    }
};


#endif