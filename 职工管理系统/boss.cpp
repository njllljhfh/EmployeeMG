#include "boss.h"


Boss::Boss(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Boss::showInfo()
{
    cout << "ְ����ţ�" << this->mId
        << " \tְ��������" << this->mName
        << " \t��λ��" << this->getDeptName()
        << " \t��λְ�𣺹���˾��������"
        << endl;
}

string Boss::getDeptName()
{
    return string("�ϰ�");
}