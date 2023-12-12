#include "workerManager.h"


WorkManager::WorkManager()
{
    //��ʼ������
    this->mEmpNum = 0;
    this->mEmpArray = NULL;
}

WorkManager::~WorkManager()
{
    if (this->mEmpArray != NULL)
    {
        delete this->mEmpArray;
        this->mEmpArray = NULL;
    }
}

void WorkManager::showMenu()
{
    cout << "*****************************************" << endl;
    cout << "******** ��ӭʹ��ְ������ϵͳ��**********" << endl;
    cout << "*********** 0.�˳�������� **************" << endl;
    cout << "*********** 1.����ְ����Ϣ **************" << endl;
    cout << "*********** 2.��ʾְ����Ϣ **************" << endl;
    cout << "*********** 3.ɾ��ְ����Ϣ **************" << endl;
    cout << "*********** 4.�޸�ְ����Ϣ **************" << endl;
    cout << "*********** 5.����ְ����Ϣ **************" << endl;
    cout << "*********** 6.���ձ������ **************" << endl;
    cout << "*********** 7.��������ĵ� **************" << endl;
    cout << "*****************************************" << endl;
    cout << endl;
}

void WorkManager::addEmp()
{
    cout << "���������ְ��������" << endl;
    int addNum = 0;
    cin >> addNum; //�����û����������
    if (addNum > 0)
    {
        //��������¿ռ��С
        int newSize = this->mEmpNum + addNum;

        //�����¿ռ�
        Worker** newSpace = new Worker * [newSize];

        //��ԭ���ռ��е����ݣ��������¿ռ���
        if (this->mEmpArray != NULL)
        {
            for (int i = 0; i < this->mEmpNum; i++)
            {
                newSpace[i] = this->mEmpArray[i];
            }
        }

        //�������������
        for (int i = 0; i < addNum; i++)
        {
            int id;  //ְ�����
            string name;  //ְ������
            int dSelect;  //����ѡ��

            cout << "������� " << i + 1 << " ����ְ���ı�ţ�" << endl;
            cin >> id;

            cout << "������� " << i + 1 << " ����ְ����������" << endl;
            cin >> name;

            //TODO:����û�д��� �Ƿ� ���룡����
            cout << "��ѡ���ְ���ĸ�λ��" << endl;
            cout << "1����ְͨ��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, dSelect);
                break;
            case 2:
                worker = new Manager(id, name, dSelect);
                break;
            case 3:
                worker = new Boss(id, name, dSelect);
                break;
            default:
                break;
            }

            //��������ְ�����浽������
            newSpace[this->mEmpNum + i] = worker;  //��������������У�����Ϊʲô����ʾ���������������
            //��Ϊ��
            //���������ܻ�����������������������ľ��棬��Ϊ�ڴ������ʱ���������޷�ȷ�� this->mEmpNum + i �Ƿ�ᳬ������ķ�Χ��
            //�����ϣ������������棬���Կ���ʹ�þ�̬ǿ������ת����static_cast������ȷ���߱����������ͼ��
            //newSpace[static_cast<size_t>(this->mEmpNum) + i] = worker;
        }

        //�ͷ�ԭ��������
        delete[] this->mEmpArray;

        //��������ָ��ָ���µ�����
        this->mEmpArray = newSpace;

        //����ְ������
        this->mEmpNum = newSize;

        //�ɹ���Ӻ󣬱������ݵ��ļ���


        cout << "�ɹ���� " << addNum << " ����ְ����" << endl;
    }
    else
    {
        cout << "������������" << endl;
    }

    //����������������ص��ϼ�Ŀ¼
    system("pause");
    system("cls");
}

void WorkManager::exitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}
