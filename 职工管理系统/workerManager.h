#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>  //�������������ͷ�ļ�
using namespace std;  //ʹ�ñ�׼�����ռ�
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>

#define FILENAME "empFile.txt"


class WorkManager
{
public:
    int mEmpNum;  //ְ������
    Worker** mEmpArray;  //ְ������ָ��
    bool mFileIsEmpty;  //�ж��ļ��Ƿ�Ϊ�յı��

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

    //��������
    void save();

    //ͳ������
    int getEmpNum();

    //��ʼ��ְ��
    void initEmp();
};
