#include "boss.h"


Boss::Boss(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Boss::showInfo()
{
    cout << "职工编号：" << this->mId
        << " \t职工姓名：" << this->mName
        << " \t岗位：" << this->getDeptName()
        << " \t岗位职责：管理公司所有事务"
        << endl;
}

string Boss::getDeptName()
{
    return string("老板");
}