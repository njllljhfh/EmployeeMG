#include <iostream>
#include "workerManager.h"
using namespace std;
//#include "testWorker.h"


int main()
{
    //testAllWorker();
    //cout << "-------------------------------------------" << endl;

    WorkManager wm;

    int choice = 0;
    while (true)
    {
        wm.showMenu();

        cin >> choice;
        switch (choice)
        {
        case 0:  //�˳��������
            wm.exitSystem();
            break;
        case 1:  //����ְ����Ϣ
            wm.addEmp();
            break;
        case 2:  //��ʾְ����Ϣ
            wm.shouEmp();
            break;
        case 3:  //ɾ��ְ����Ϣ�����case��Ҫִ�е��߼��Ƚ϶࣬��Ҫ�Ӵ����ţ�����������ᱨ��
        {
            wm.delEmp();
            break;
        }
        case 4:  //�޸�ְ����Ϣ
            wm.modifyEmp();
            break;
        case 5:  //����ְ����Ϣ
            break;
        case 6:  //���ձ������
            break;
        case 7:  //��������ĵ�
            break;
        default:
            system("cls"); //�����Ļ
            break;
        }
    }

    system("pause");
    return 0;
}