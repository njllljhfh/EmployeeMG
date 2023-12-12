#include "workerManager.h"


WorkManager::WorkManager()
{
    //初始化属性
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
    cout << "******** 欢迎使用职工管理系统！**********" << endl;
    cout << "*********** 0.退出管理程序 **************" << endl;
    cout << "*********** 1.增加职工信息 **************" << endl;
    cout << "*********** 2.显示职工信息 **************" << endl;
    cout << "*********** 3.删除职工信息 **************" << endl;
    cout << "*********** 4.修改职工信息 **************" << endl;
    cout << "*********** 5.查找职工信息 **************" << endl;
    cout << "*********** 6.按照编号排序 **************" << endl;
    cout << "*********** 7.清空所有文档 **************" << endl;
    cout << "*****************************************" << endl;
    cout << endl;
}

void WorkManager::addEmp()
{
    cout << "请输入添加职工数量：" << endl;
    int addNum = 0;
    cin >> addNum; //保存用户输入的数量
    if (addNum > 0)
    {
        //计算添加新空间大小
        int newSize = this->mEmpNum + addNum;

        //开辟新空间
        Worker** newSpace = new Worker * [newSize];

        //将原来空间中的数据，拷贝到新空间中
        if (this->mEmpArray != NULL)
        {
            for (int i = 0; i < this->mEmpNum; i++)
            {
                newSpace[i] = this->mEmpArray[i];
            }
        }

        //批量添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;  //职工编号
            string name;  //职工姓名
            int dSelect;  //部门选择

            cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
            cin >> id;

            cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
            cin >> name;

            //TODO:这里没有处理 非法 输入！！！
            cout << "请选择该职工的岗位：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
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

            //将创建的职工保存到数组中
            newSpace[this->mEmpNum + i] = worker;  //代码可以正常运行，这里为什么会提示缓冲区溢出？？？
            //因为：
            //编译器可能会对这种情况发出缓冲区溢出的警告，因为在代码分析时，编译器无法确定 this->mEmpNum + i 是否会超出数组的范围。
            //如果你希望消除这个警告，可以考虑使用静态强制类型转换（static_cast）来明确告诉编译器你的意图：
            //newSpace[static_cast<size_t>(this->mEmpNum) + i] = worker;
        }

        //释放原来的数组
        delete[] this->mEmpArray;

        //更改数组指向，指向新的数组
        this->mEmpArray = newSpace;

        //更新职工人数
        this->mEmpNum = newSize;

        //成功添加后，保存数据到文件中


        cout << "成功添加 " << addNum << " 名新职工！" << endl;
    }
    else
    {
        cout << "输入数据有误！" << endl;
    }

    //按任意键后，清屏，回到上级目录
    system("pause");
    system("cls");
}

void WorkManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
