#pragma once //防止头文件重复包含
#include <iostream>  //包含输入输出流头文件
using namespace std;  //使用标准命名空间
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


class WorkManager
{
public:
    int mEmpNum;  //职工人数
    Worker** mEmpArray;  //职工数组指针

    //构造
    WorkManager();

    //析构
    ~WorkManager();

    //展示菜单
    void showMenu();

    //退出系统
    void exitSystem();

    //添加职工
    void addEmp();
};
