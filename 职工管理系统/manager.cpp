#include "manager.h"


Manager::Manager(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->mId
        << " \t职工姓名：" << this->mName
        << " \t岗位：" << this->getDeptName()
        << " \t岗位职责：完成老板交给的任务，并下发任务给员工"
        << endl;
}

string Manager::getDeptName()
{
    return string("经理");
}
