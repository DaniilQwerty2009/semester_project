#include <iostream>

#include "School.h"
#include "menu.h"

using std::cout;
using std::endl;

int main()
{
   
    School* ourSchool = new School;

    menu ourMenu;
    ourMenu.init(ourSchool);

    return 0;
}