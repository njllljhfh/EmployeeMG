#include "workerManager.h"


WorkManager::WorkManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);  //���ļ�

    //�ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ�������" << endl;
        //��ʼ������
        this->mEmpNum = 0;
        this->mEmpArray = NULL;
        this->mFileIsEmpty = true;
        ifs.close();
        return;
    }

    //�ļ����ڣ�����Ϊ��
    char ch;
    ifs >> ch;
    if (ifs.eof())  // �����пշ�ʽ������̫��⣡����
    {
        cout << "�ļ�Ϊ��" << endl;
        this->mEmpNum = 0;
        this->mEmpArray = NULL;
        this->mFileIsEmpty = true;
        ifs.close();
        return;
    }

    //�ļ����ڣ���������
    this->initEmp();
}


WorkManager::~WorkManager()
{
    if (this->mEmpArray != NULL)
    {
        delete this->mEmpArray;
        this->mEmpArray = NULL;
    }
}


//��ʾ�˵�
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


//���ְ��
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
            int id;  // ְ�����
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
        this->save();

        //�����ļ���Ϊ�յı��
        this->mFileIsEmpty = false;

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


//��������
void WorkManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);  // д�ļ�
    if (!ofs.is_open())
    {
        cout << "�������ļ�ʧ��" << endl;
        return;
    }

    for (int i = 0; i < this->mEmpNum; i++)
    {
        ofs << this->mEmpArray[i]->mId << " "
            << this->mEmpArray[i]->mName << " "
            << this->mEmpArray[i]->mDeptId << endl;
    }

    ofs.close();
}


//ͳ���Ѵ��ڵ�����
int WorkManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;

    /*
        ��C++�У�ifstream ����ʹ��Ĭ�ϵĿհ��ַ��������ո��Ʊ�������з��ȣ���Ϊ�ָ��������ļ��ж�ȡ����ʱ��������Щ�հ��ַ���
        ������ΪĬ������£���������� >> ���Զ������������еĿհ��ַ���ֱ�������ǿհ��ַ�Ϊֹ��
    */
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }

    return num;
}


//��ʼ��ְ��
void WorkManager::initEmp()
{
    int num = this->getEmpNum();
    cout << "�Ѵ��ڵ�ְ������Ϊ��" << num << endl;
    this->mEmpNum = num;
    this->mEmpArray = new Worker * [this->mEmpNum];

    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker* worker = NULL;
        //���ݲ�ͬ�Ĳ���id������ͬ����
        if (dId == 1)
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)
        {
            worker = new Manager(id, name, dId);
        }
        else
        {
            worker = new Boss(id, name, dId);
        }
        //���浽������
        this->mEmpArray[index] = worker;
        index++;
    }

    //�ر��ļ�
    ifs.close();
}


//��ʾְ��
void WorkManager::shouEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "�ļ������ڣ����߼�¼Ϊ��" << endl;
    }
    else
    {
        for (int i = 0; i < this->mEmpNum; i++)
        {
            //���ö�̬���ó���ӿ�
            this->mEmpArray[i]->showInfo();
        }
    }
    //�������������
    system("pause");
    system("cls");
}


//ɾ��ְ��
void WorkManager::delEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "�ļ������ڣ����߼�¼Ϊ��" << endl;
        return;
    }
    else
    {
        //�����ɾ��
        cout << "��������Ҫɾ����ְ����ţ�" << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if (index != -1)
        {
            //ְ������
            for (int i = index; i < this->mEmpNum - 1; i++)
            {
                this->mEmpArray[i] = this->mEmpArray[i + 1];
            }
            //����ְ������
            this->mEmpNum--;
            //ͬ�����ݵ��ļ�
            this->save();
            cout << "ɾ���ɹ���" << endl;
        }
        else
        {
            cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
        }
    }
    system("pause");
    system("cls");
}


//�ж�ְ���Ƿ���ڣ����ڷ������� index�������ڷ���-1
int WorkManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->mEmpNum; i++)
    {
        if (this->mEmpArray[i]->mId == id) 
        {
            index = i;
            break;
        }
    }
    return index;
}


//�˳�ϵͳ
void WorkManager::exitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}
