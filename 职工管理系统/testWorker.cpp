#include "testWorker.h"

void testAllWorker()
{
    cout << "测试所有的worker类：" << endl;
    Worker* worker = nullptr;
    worker = new Employee(1, "张三", 1);
    worker->showInfo();
    delete worker;

    worker = new Manager(2, "李四", 2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3, "王五", 3);
    worker->showInfo();
    delete worker;
}