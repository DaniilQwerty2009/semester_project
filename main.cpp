#include <iostream>
#include <windows.h>

#include "School.h"
#include "menu.h"

using std::cout;
using std::endl;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
   
    School* ourSchool = new School;
    ourSchool->save_load();

    menu ourMenu;
    ourMenu.init(ourSchool);

    ourSchool->save();
    return 0;
}