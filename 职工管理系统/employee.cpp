#include "employee.h"


Employee::Employee(int id, string name, int dId)
{
    this->mId = id;
    this->mName = name;
    this->mDeptId = dId;
}

void Employee::showInfo()
{
    cout << "ְ����ţ�" << this->mId
        << " \tְ��������" << this->mName
        << " \t��λ��" << this->getDeptName()
        << " \t��λְ����ɾ�����������"
        << endl;
}

string Employee::getDeptName()
{
    //ֱ��д "Ա��" ��  const char*  ������
    return string("Ա��");
}