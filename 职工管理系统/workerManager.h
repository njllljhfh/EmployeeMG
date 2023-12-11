#pragma once //防止头文件重复包含
#include <iostream>  //包含输入输出流头文件
using namespace std;  //使用标准命名空间


class WorkManager
{
public:
    //构造
    WorkManager();

    //析构
    ~WorkManager();

    //展示菜单
    void showMenu();

    //退出系统
    void exitSystem();
};
