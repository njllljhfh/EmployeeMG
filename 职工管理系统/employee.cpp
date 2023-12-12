#include "employee.h"


Employee::Employee(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Employee::showInfo()
{
    cout << "职工编号：" << this->mId
        << " \t职工姓名：" << this->mName
        << " \t岗位：" << this->getDeptName()
        << " \t岗位职责：完成经理交给的任务"
        << endl;
}

string Employee::getDeptName()
{
    //直接写 "员工" 是  const char*  的类型
    return string("员工");
}