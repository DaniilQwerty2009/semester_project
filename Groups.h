// Класс-контейнер групп - двусвязный список "номер-название" группы

#ifndef GROUPS_H
#define GROUPS_H

#include <cstring>
#include "SchoolExeptions.h"
#include "Algorithm.h"

class Groups
{
private:
            // Узел-группа
            struct Group
            {
            private:
                Group* next = nullptr;
                Group* prev = nullptr;

                explicit Group(const unsigned& ID, const char* name)
                : ID(ID)
                {
                    size_t sLen = strlen(name) + 1;

                    // Корректная обрезка строки с учетом UTF-8 (несколько байт на символ)
                    if(sLen <= MAX_NAME_BYTES)
                    {
                        this->name = new char[sLen];
                        strcpy(this->name, name);

                        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix(this->name, MAX_NAME_BYTES);
                        this->name[safePrefix] = '\0';
                    }
                    else
                    {
                        this->name = new char[MAX_NAME_BYTES];
                        strncpy(this->name, name, MAX_NAME_BYTES);

                        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix(this->name, MAX_NAME_BYTES);
                        this->name[safePrefix] = '\0';
                    }     
                }

                friend class Groups;
            public:
                const unsigned ID;      // уникальный номер
                char* name = nullptr;   // название

                

                ~Group()
                {
                    delete[] name;
                }

                Group(Group& other)            = delete;
                Group& operator=(Group& other) = delete;

            };

    unsigned capacity = 0;          // размер списка
    Groups::Group* head = nullptr;
    Groups::Group* tail = nullptr;
    
public:
    enum {MAX_NAME_BYTES = 40};     // максимальное кол-во байт под имя

    Groups()
        {   }

    ~Groups()
    {
        Group* ptr = head;

        while(ptr)
        {
            head = head->next;
            delete ptr;
            ptr = head;
        }
    }

    Groups(Groups& other) = delete;
    Groups& operator=(Groups& other) = delete;
 
    // Генерирует исключение EmptyPtr по параметру name, AlreadyExist
    void push(const unsigned& ID, const char* name)
    {
        if(name == nullptr)
            throw EmptyStr();

        if(!head)
        {
            head = new Group(ID, name);
            capacity++;
            tail = head;
        }
        else
        {
            Group* ptr = head;

            do
            {
                if(strcmp(ptr->name, name) == 0)
                    throw AlreadyExist();
                
                ptr = ptr->next;
            }while(ptr);
            
            tail->next = new Group(ID, name);
            tail->next->prev = tail;
            tail = tail->next;

            capacity++;
        }
    }

    void pop(Group* ptr) noexcept
    {
        if(!ptr || !head || capacity == 0)
            return;

        if(ptr == head)
        {
            delete head;
            head = nullptr;
            capacity--;
            return;
        }
        else if(ptr == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
            capacity--;
            delete ptr;
        }
        else
        {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            capacity--;
            delete ptr;
        }
    }

    size_t size() const
    {
        return capacity;
    }

// ------------------------------------------------------------------------------------------

    // Класс-итератор для контейнера Groups
    class iterator
    {
    private:
        Group* pointer = nullptr;

        // Инициализированный бъект итератора создается только методами Groups: begin, end...
        explicit iterator(Group* ptr): pointer(ptr)
            {   }

        friend class Groups;

    public:

        explicit iterator():pointer(nullptr)
            {   }

        iterator(const iterator&) = default;
        iterator(iterator&) = default;

        
        void     operator= (iterator iterator);
        bool     operator!=(iterator& iterator);
        bool     operator==(iterator& iterator);

        iterator operator++();
        iterator operator++(int);
 
        operator bool() const;

        // Оператор разыменования возвращает ссылку на узел Group.
        // Cинтаксис разыменования: (*node).имя_поля/метода
        Group& operator*() const;        
    };

    // Инициализация итератора методами:

    // Инициализация итератора первым членом списка
    inline iterator begin()
    { 
        return iterator(head); 
    }

    inline iterator begin() const
    { 
        return iterator(head); 
    }

    // Инициализация итератора следующим за последним членом списка
    inline iterator end()
    { 
        return iterator(nullptr); 
    }

    // Инициализация итератора последним членом списка
    inline iterator last()
    {
        return iterator(tail);
    }


// ------------------------------------------------------------------------------------------

    // Классы-компараторы:

    // Сравнение по полю name. True, если a < b
    class nameComparator
    {
    public:
        bool operator()(const Group& a, const Group& b) const
        {
            return std::strcmp(a.name, b.name) < 0;
        }

        bool operator()(const Group& a, const char* b) const
        {
            return std::strcmp(a.name, b) < 0;
        }

        bool operator()(const char* a, const Group& b) const
        {
            return std::strcmp(a, b.name) < 0;
        }
    };

    // Сравнение по полю ID. True, если a < b
    class idComparator
    {
    public:
        bool operator()(const Group& a, const Group& b) const
        {
            return a.ID < b.ID;
        }

        bool operator()(const Group& a, const unsigned& b) const
        {
            return a.ID < b;
        }

        bool operator()(const unsigned& a, const Group& b) const
        {
            return a < b.ID;
        }
    };

};


#endif