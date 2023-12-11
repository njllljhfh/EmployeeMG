#include <iostream>
#include "workerManager.h"
using namespace std;


int main()
{
    WorkManager wm;

    int choice = 0;
    while (true) 
    {
        wm.showMenu();

        cin >> choice;
        switch (choice)
        {
        case 0:
            wm.exitSystem();
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            system("cls"); //Çå¿ÕÆÁÄ»
            break;
        }
    }

    system("pause");
    //cin.get();
    return 0;
}