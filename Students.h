#ifndef STUDENT_H
#define STUDENT_H

#include <cstring>

#include "VisitDays.h"
#include "SchoolExeptions.h"
#include "Algorithm.h"


class Students
{
private:
    unsigned capacity = 0;

            struct Student
            {
            private:

                Student* prev = nullptr;
                Student* next = nullptr;

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
                
                const unsigned* getVisitsArr() const
                {
                    return days.datesArray;
                }

                unsigned visits_arr_size() const
                {
                    return days.size();
                }

                void push_day(const unsigned& visitDay)
                {
                    if(!has_day(visitDay))
                        days.push(visitDay);
                }

                bool has_day(const unsigned& day)
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

    Student* head = nullptr;
    Student* tail = nullptr;

    // не опнятно capacity++?
    // void insert(Student* destination, Student* element)
    // {
    //     if(!destination || !element)
    //         return;             //exeption???

    //     // Корректно вставляем элемент в последовательность
    //     if(destination->next)
    //     {
    //         if(destination->prev)                   // в центр
    //         {
    //             destination->prev->next = element;
    //             element->prev = destination->prev;
    //             destination->prev = element;
    //             element->next = destination;
    //         }
    //         else                                    // перед началом
    //         {
    //             destination->prev = element;
    //             element->next = destination;
    //             head = element;
    //         }
    //     }
    //     else
    //     {
    //         if(destination->prev)                   // перед концом
    //         {
    //             destination->prev->next = element;
    //             element->prev = destination->prev;
    //             destination->prev = element;
    //             element->next = destination;
    //         }  
    //         else                                    // перед единственным элементом
    //         {
    //             destination->prev = element;
    //             element->next = destination;
    //             head = element;
    //         }
    //     }
    // }
    
    void replace(Student* destination, Student* element)
    {
        if(!destination || !element)
            return;             //exeption???   

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
    // friend class School;
public:

    enum {MAX_NAME_BYTES = 40};

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

    class iterator
        {
        private:
            Student* pointer;
        
            explicit iterator(Student* ptr):pointer(ptr)
                {   }

            friend class Students;
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

     // компрораторы
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

    
    void push(const unsigned& ID, const char* lastname, const unsigned& groupID)
    {
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

    void pop(Student* node)
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

    unsigned size()
    {
        return capacity;
    }

    // сортировка
    template <typename Compare> 
        void sort(Compare cmp) //????
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