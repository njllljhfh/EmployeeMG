#include "manager.h"


Manager::Manager(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Manager::showInfo()
{
    cout << "ְ����ţ�" << this->mId
        << " \tְ��������" << this->mName
        << " \t��λ��" << this->getDeptName()
        << " \t��λְ������ϰ彻�������񣬲��·������Ա��"
        << endl;
}

string Manager::getDeptName()
{
    return string("����");
}
