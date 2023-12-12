#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include <string>


class Manager :public Worker
{
public:
    Manager(int id, string name, int dId);
    //子类中 virtual 关键字可以不写
    void showInfo();
    string getDeptName();
};
