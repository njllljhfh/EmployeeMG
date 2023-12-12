#pragma once
#include <iostream>
using namespace std;


//职工抽象基类
class Worker
{
public:
    //显示个人信息
    virtual void showInfo() = 0;
    //获取岗位名称
    virtual string getDeptName() = 0;

    int mId;       //职工编号
    string mName;  //职工姓名
    int mDeptId;   //职工所在部门名称编号
};
