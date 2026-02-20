// Класс-контейнер студентов - двусвязный список
// поля узлов: уникальный ID, имя, номер группы, объект класса списока дней посещений

#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

#include "VisitDays.h"
#include "SchoolExeptions.h"
#include "Algorithm.h"


class Students
{
private:
            // Узел-студент
            struct Student
            {
            private:

                Student* prev = nullptr;
                Student* next = nullptr;

                // Список дней посещений
                VisitDays days;

                friend class Students;

            public:
                const unsigned ID;
                char* lastname = nullptr;
                unsigned groupID;
                
                explicit Student(unsigned studentID, const char* lastname, const unsigned& groupID = 0)
                :ID(studentID), groupID(groupID)
                {
                    size_t sLen = strlen(lastname) + 1;

                    if(sLen <= MAX_NAME_BYTES)
                    {
                        this->lastname = new char[sLen];
                        strcpy(this->lastname, lastname);

                        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix(this->lastname, MAX_NAME_BYTES);
                        this->lastname[safePrefix] = '\0';
                    }
                    else
                    {
                        this->lastname = new char[MAX_NAME_BYTES];
                        strncpy(this->lastname, lastname, MAX_NAME_BYTES);
                        
                        size_t safePrefix = SchoolAlg::safe_cyrillic_prefix(this->lastname, MAX_NAME_BYTES);
                        this->lastname[safePrefix] = '\0';
                    }        
                }


                ~Student()
                {
                    delete[] lastname;
                }

                Student(Student& other)             = delete;
                Student& operator =(Student& other) = delete;

                bool operator!=(Student* ptr)
                {
                    return this->ID != ptr->ID;
                }

                bool operator==(Student* ptr)
                {
                    return this->ID == ptr->ID;
                }
                
                // Указатель на список дней посещений
                const unsigned* get_visits_arr() const
                {
                    return days.datesArray;
                }

                // Колличество дней посещений
                unsigned visits_arr_size() const
                {
                    return days.size();
                }

                void push_day(const unsigned& visitDay) noexcept
                {
                    if(!has_day(visitDay))
                        days.push(visitDay);
                }

                // Проверка на посещение в конкретный день
                bool has_day(const unsigned& day) noexcept
                {
                    unsigned* ptr = days.datesArray;

                    for(size_t i = 0; i < days.size(); ++i)
                    {
                        if(ptr[i] == day)
                            return true;
                    }

                    return false;
                } 
            };

            
    unsigned capacity = 0;
    Student* head = nullptr;
    Student* tail = nullptr;

    // Перестановка элемента перед узлом destination
    void replace(Student* destination, Student* element) noexcept
    {
        if(!destination || !element)
            return; 

        // Корректно извлекаем элемент из последовательности
        if(element->next)
        {
            if(element->prev)                       // есть след и пред - в центре
            {
                element->prev->next = element->next;
                element->next->prev = element->prev;
            }
            else                                    // есть след, нет пред - в начале
            {
                element->next->prev = nullptr;
                head = element->next;
            }
        }
        else                                        
        {
            if(element->prev)                       // нет след, есть пред - в конце
            {
                element->prev->next = nullptr;
                tail = element->prev;
            }
            else                                    // нет след, нет пред - единственный элемент
            {
                return;
            }
        }

        // Корректно вставляем элемент в последовательность
        if(destination->next)
        {
            if(destination->prev)                   // в центр
            {
                destination->prev->next = element;
                element->prev = destination->prev;
                destination->prev = element;
                element->next = destination;
            }
            else                                    // перед началом
            {
                destination->prev = element;
                element->next = destination;
                head = element;
            }
        }
        else
        {
            if(destination->prev)                   // перед концом
            {
                destination->prev->next = element;
                element->prev = destination->prev;
                destination->prev = element;
                element->next = destination;
            }  
            else                                    // перед единственным элементом
            {
                destination->prev = element;
                element->next = destination;
                head = element;
            }
        }
        
    }

public:

    enum {MAX_NAME_BYTES = 40};     // Колличество байт под имя

    Students()
        {   }

    ~Students()
    {
        while(head)
        {
            Student* temp = head;
            head = head->next;
            delete temp;
        }
    }

// -----------------------------------------------------------------------------------------

    // Класс-итератор контейнера Students
    class iterator
        {
        private:
            Student* pointer;
        
            // Инициализированный бъект итератора создается только методами Students: begin, end...
            explicit iterator(Student* ptr):pointer(ptr)
                {   }

            friend class Students;
        public:

            explicit iterator():pointer(nullptr)
                {   }

            iterator(const iterator&) = default;
            iterator(iterator&)       = default;

            void     operator= (iterator iterator);
            bool     operator!=(iterator& iterator);
            bool     operator==(iterator& iterator);

            iterator operator--();
            iterator operator--(int);
            iterator operator++();
            iterator operator++(int);

            
            operator bool() const;

            // Оператор разыменования возвращает ссылку на узел Student
            // синтаксис разыменования: (*node).имя_поля/метода
            Student& operator*() const;

        };

    // Инициализация итератора первым членом списка
    inline iterator begin() const
    {
        return iterator(head);
    }

    // Инициализация итератора следующим за последним членом списка
    inline iterator end() const
    {
        return iterator(nullptr);
    }

    // Инициализация итератора последним членом списка
    inline iterator last() const
    {
        return iterator(tail);
    }

    // Классы-компараторы:
    
    // Сранение по посещениям. True, если a < b
    class visitComparator
    {
    public:
        bool operator()(const Students::Student& a, const Students::Student& b) const
        {
            return a.visits_arr_size() < b.visits_arr_size();
        }

        bool operator()(const Students::Student& a, const unsigned& b) const
        {
            return a.visits_arr_size() < b;
        }

        bool operator()(const unsigned& a, const Students::Student& b) const
        {
            return a < b.visits_arr_size();
        }
    };

    // Сранение по имени. True, если a < b
    class lastnameComparator
    {
    public:
        bool operator()(const Students::Student& a, const Students::Student& b) const
        {
            return std::strcmp(a.lastname, b.lastname) < 0;
        }

        bool operator()(const Students::Student& a, const char* b) const
        {
            return std::strcmp(a.lastname, b) < 0;
        }

        bool operator()(const char* a, const Students::Student& b) const
        {
            return std::strcmp(a, b.lastname) < 0;
        }
    };

    // Сранение по ID. True, если a < b
    class idComparator
    {
    public:
        bool operator()(const Students::Student& a, const Students::Student& b) const
        {
            return a.ID < b.ID;
        }

        bool operator()(const Students::Student& a, const unsigned& b) const
        {
            return a.ID < b;
        }

        bool operator()(const unsigned& a, const Students::Student& b) const
        {
            return a < b.ID;
        }
    };

    // Генерирует исклбчение EmptyPtr по парамаметру lastname
    void push(const unsigned& ID, const char* lastname, const unsigned& groupID) 
    {
        if(lastname == nullptr)
            throw EmptyPtr();

        if(!head)
        {
            head = new Student(ID, lastname, groupID);
            ++capacity;
            tail = head;
        }
        else
        {
            tail->next = new Student(ID, lastname, groupID);
            capacity++;
            Student* oldTail = tail;
            tail = tail->next;
            tail->prev = oldTail;
            
        }
    }

    // Вставка с сохранением порядка.
    // параметр cmp (признак сравнения) - объект класса-компаратора в области класса Students
    template <typename Comparator>
        void push_sorted(Comparator cmp, const unsigned& studentID, const char* lastname, const unsigned& groupID)
        {
            if(!head)
            {
                
               push(studentID, lastname, groupID);
            }
            else
            {
                push(studentID, lastname, groupID);
                Student* destination = head;
                Student* newElement = tail;

                while(destination != newElement)
                {
                    if(cmp(*destination, *newElement))
                        destination = destination->next;
                    else
                    {
                        replace(destination, newElement);
                        return;
                    }
                        
                }

            }
        }

    void pop(Student* node) noexcept
    {
        if(!node)
            return;
        
        // Корректно извлекаем элемент из последовательности
        if(node->next)
        {
            if(node->prev)                       // есть след и пред - в центре
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                delete node;
                capacity--;
            }
            else                                    // есть след, нет пред - в начале
            {
                node->next->prev = nullptr;
                head = node->next;
                delete node;
                capacity--;
            }
        }
        else                                        
        {
            if(node->prev)                       // нет след, есть пред - в конце
            {
                node->prev->next = nullptr;
                tail = node->prev;
                delete node;
                capacity--;
            }
            else                                    // нет след, нет пред - единственный элемент
            {
                delete node;
                head = nullptr;
                capacity--;
            }
        }

    }

    // Колличество элементов
    unsigned size() const
    {
        return capacity;
    }

    // Сортировка по признаку cmp - компаратор в области Students
    template <typename Compare> 
        void sort(Compare cmp) noexcept
    {
        // Сортировка вставками:

        if(!head || !head->next)
            return;

        Student* sotrBorder = head;         // отсортированнная часть
        Student* iter = sotrBorder->next;   // вставляемый элемент
        Student* inSortedPart;              // для прохода по отстортированной части

        while(iter)
        {
            // идем по списку пока элемент больше предыдущего
            if(cmp(*sotrBorder, *iter) || (!cmp(*sotrBorder, *iter) && !cmp(*iter, *sotrBorder)))   
            {
                sotrBorder = sotrBorder->next;
                iter = iter->next;
                continue;
            }

            
            else
            {
                inSortedPart = sotrBorder;

                // ищем место втсавки в отстртированной части
                while( inSortedPart->prev != nullptr && cmp(*iter, *inSortedPart->prev))
                    inSortedPart = inSortedPart->prev;
                
                // пересещаем элемент в отсортированную часть
                replace(inSortedPart, iter);

                iter = sotrBorder->next;
            }
        }
    }
};

#endif