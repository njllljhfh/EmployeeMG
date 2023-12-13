#include <iostream>
#include "workerManager.h"
using namespace std;
//#include "testWorker.h"


int main()
{
    //testAllWorker();
    //cout << "-------------------------------------------" << endl;

    WorkManager wm;

    int choice = 0;
    while (true)
    {
        wm.showMenu();

        cin >> choice;
        switch (choice)
        {
        case 0:  //退出管理程序
            wm.exitSystem();
            break;
        case 1:  //增加职工信息
            wm.addEmp();
            break;
        case 2:  //显示职工信息
            wm.shouEmp();
            break;
        case 3:  //删除职工信息。如果case下要执行的逻辑比较多，需要加大括号，否则编译器会报错。
        {
            wm.delEmp();
            break;
        }
        case 4:  //修改职工信息
            wm.modifyEmp();
            break;
        case 5:  //查找职工信息
            break;
        case 6:  //按照编号排序
            break;
        case 7:  //清空所有文档
            break;
        default:
            system("cls"); //清空屏幕
            break;
        }
    }

    system("pause");
    return 0;
}