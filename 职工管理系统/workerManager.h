#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>  //�������������ͷ�ļ�
using namespace std;  //ʹ�ñ�׼�����ռ�
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


class WorkManager
{
public:
    int mEmpNum;  //ְ������
    Worker** mEmpArray;  //ְ������ָ��

    //����
    WorkManager();

    //����
    ~WorkManager();

    //չʾ�˵�
    void showMenu();

    //�˳�ϵͳ
    void exitSystem();

    //���ְ��
    void addEmp();
};
