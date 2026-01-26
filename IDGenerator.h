#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

class IDGenerator
{
private:
    unsigned IDcounter = 100;
public:
    IDGenerator()
        {   }


    unsigned operator()()
    { return IDcounter++; }
};


#endif