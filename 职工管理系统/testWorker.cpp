#include "testWorker.h"

void testAllWorker()
{
    cout << "�������е�worker�ࣺ" << endl;
    Worker* worker = nullptr;
    worker = new Employee(1, "����", 1);
    worker->showInfo();
    delete worker;

    worker = new Manager(2, "����", 2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3, "����", 3);
    worker->showInfo();
    delete worker;
}