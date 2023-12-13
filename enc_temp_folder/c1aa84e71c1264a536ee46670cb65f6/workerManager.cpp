#include "workerManager.h"


WorkManager::WorkManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);  //读文件

    //文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        //初始化属性
        this->mEmpNum = 0;
        this->mEmpArray = NULL;
        this->mFileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在，数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())  // 这种判空方式，还不太理解！！！
    {
        cout << "文件为空" << endl;
        this->mEmpNum = 0;
        this->mEmpArray = NULL;
        this->mFileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在，且有数据
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


//显示菜单
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


//添加职工
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
            int id;  // 职工编号
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
        this->save();

        //更新文件不为空的标记
        this->mFileIsEmpty = false;

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


//保存数据
void WorkManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);  // 写文件
    if (!ofs.is_open())
    {
        cout << "打开数据文件失败" << endl;
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


//统计已存在的人数
int WorkManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;

    /*
        在C++中，ifstream 对象使用默认的空白字符（包括空格、制表符、换行符等）作为分隔符，从文件中读取数据时会跳过这些空白字符。
        这是因为默认情况下，输入运算符 >> 会自动跳过输入流中的空白字符，直到遇到非空白字符为止。
    */
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }

    return num;
}


//初始化职工
void WorkManager::initEmp()
{
    int num = this->getEmpNum();
    cout << "已存在的职工人数为：" << num << endl;
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
        //根据不同的部门id创建不同对象
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
        //保存到数组中
        this->mEmpArray[index] = worker;
        index++;
    }

    //关闭文件
    ifs.close();
}


//显示职工
void WorkManager::shouEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "文件不存在，或者记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < this->mEmpNum; i++)
        {
            //利用多态调用程序接口
            this->mEmpArray[i]->showInfo();
        }
    }
    //按任意键后，清屏
    system("pause");
    system("cls");
}


//删除职工
void WorkManager::delEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "文件不存在，或者记录为空" << endl;
        return;
    }
    else
    {
        //按编号删除
        cout << "请输入想要删除的职工编号：" << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if (index != -1)
        {
            //职工存在
            for (int i = index; i < this->mEmpNum - 1; i++)
            {
                this->mEmpArray[i] = this->mEmpArray[i + 1];
            }
            //更新职工个数
            this->mEmpNum--;
            //同步数据到文件
            this->save();
            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
    }
    system("pause");
    system("cls");
}


//判断职工是否存在，存在返回数组 index，不存在返回-1
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


//退出系统
void WorkManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
