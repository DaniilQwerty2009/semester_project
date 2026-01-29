#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

class IDGenerator
{
private:
    unsigned IDcounter = 100;
public:
    explicit IDGenerator(unsigned startValue): IDcounter(startValue)
        {   }


    unsigned operator()()
    { return IDcounter++; }
};


#endif