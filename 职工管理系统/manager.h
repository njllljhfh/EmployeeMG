#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include <string>


class Manager :public Worker
{
public:
    Manager(int id, string name, int dId);
    //������ virtual �ؼ��ֿ��Բ�д
    void showInfo();
    string getDeptName();
};
