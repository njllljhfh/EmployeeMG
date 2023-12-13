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
        for (int i = 0; i < this->mEmpNum; i++)
        {
            delete this->mEmpArray[i];
            this->mEmpArray[i] = NULL;
        }
        delete[] this->mEmpArray;
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
                //数据前移
                this->mEmpArray[i] = this->mEmpArray[i + 1];
            }
            //更新职工个数
            this->mEmpNum--;
            //同步数据到文件
            this->save();

            //当最后一个职工被删除，要修改文件为空的标记为true
            if (this->mEmpNum == 0)
            {
                this->mFileIsEmpty = true;
            }

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


//修改职工
void WorkManager::modifyEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "文件不存在，或记录为空" << endl;
    }
    else
    {
        cout << "请输入要修改的职工编号：" << endl;
        int id;
        cin >> id;

        int index = this->isExist(id);

        if (index != -1)
        {
            //释放要修改的职工的内存空间
            delete this->mEmpArray[index];

            int newId = 0;
            string newName = "";
            int newDeptId = 0;

            cout << "查到：" << id << "号职工" << endl;
            cout << "请输入新职工号：" << endl;
            cin >> newId;

            cout << "请输入新姓名：" << endl;
            cin >> newName;

            cout << "请输入新部门编号：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> newDeptId;

            Worker* worker = NULL;
            switch (newDeptId)
            {
            case 1:
                worker = new Employee(newId, newName, newDeptId);
                break;
            case 2:
                worker = new Manager(newId, newName, newDeptId);
                break;
            case 3:
                worker = new Boss(newId, newName, newDeptId);
                break;
            default:
                break;
            }

            this->mEmpArray[index] = worker;
            cout << "修改成功" << endl;

            this->save();
        }
        else
        {
            cout << "修改失败，未找到该职工" << endl;
        }
    }
    system("pause");
    system("cls");
}


//查找职工
void WorkManager::findEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "文件不存在，或记录为空" << endl;
    }
    else
    {
        cout << "请输入查找方式：" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按职工姓名查找" << endl;
        int select = 1;
        cin >> select;
        if (select == 1)
        {
            //按编号查找
            int id;
            cout << "请输入职工编号：" << endl;
            cin >> id;
            int index = isExist(id);
            if (index != -1)
            {
                cout << "查找成功！该职工信息如下：" << endl;
                this->mEmpArray[index]->showInfo();
            }
            else
            {
                cout << "查找失败，未找到该职工" << endl;
            }
        }
        else if (select == 2)
        {
            //按姓名查找
            string name;
            cout << "请输入职工姓名" << endl;
            cin >> name;

            bool flag = false;
            for (int i = 0; i < mEmpNum; i++)
            {
                if (this->mEmpArray[i]->mName == name)
                {
                    cout << "查找成功！该职工信息如下：" << endl;
                    flag = true;
                    this->mEmpArray[i]->showInfo();
                }
            }

            if (flag == false)
            {
                cout << "查找失败，未找到该职工" << endl;
            }
        }
        else
        {
            cout << "输入的选项有误，请重新输入" << endl;
        }
    }
    system("pause");
    system("cls");
}


//按照编号排序
void WorkManager::sortEmp()
{
    if (this->mFileIsEmpty)
    {
        cout << "文件不存在，或记录为空" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "请选择排序的方式：" << endl;
        cout << "1、按职工编号升序" << endl;
        cout << "2、按职工编号降序" << endl;
        int select;
        cin >> select;

        //选择排序法
        for (int i = 0; i < this->mEmpNum; i++)
        {
            //声明最小值 或 最大值的索引
            int minOrMax = i;
            for (int j = i + 1; j < this->mEmpNum; j++)
            {
                if (select == 1)  
                {
                    // 升序
                    if (this->mEmpArray[minOrMax]->mId > this->mEmpArray[j]->mId)
                    {
                        minOrMax = j;
                    }
                }
                else
                {
                    //降序
                    if (this->mEmpArray[minOrMax]->mId < this->mEmpArray[j]->mId)
                    {
                        minOrMax = j;
                    }
                }
            }

            //判断一开始认定的 最小值或最大值 是不是方面循环计算出的值，如果不是，交换数据
            if (i != minOrMax)
            {
                Worker* temp = this->mEmpArray[i];
                this->mEmpArray[i] = this->mEmpArray[minOrMax];
                this->mEmpArray[minOrMax] = temp;
            }
        }

        cout << "排序成功！排序后的结果为：" << endl;
        this->save();
        this->shouEmp();
    }
}



//清空文件
void WorkManager::cleanFile()
{
    cout << "确认清空？" << endl;
    cout << "1、确定" << endl;
    cout << "2、返回" << endl;
    int select;
    cin >> select;
    if (select == 1)
    {
        //清空文件
        ofstream ofs(FILENAME, ios::trunc);  // 删除文件后重新创建
        ofs.close();

        if (this->mEmpArray != NULL)
        {
            //删除堆区的每个职工对象
            for (int i = 0; i < this->mEmpNum; i++)
            {
                delete this->mEmpArray[i];
                this->mEmpArray[i] = NULL;
            }

            //删除堆区数组指针
            delete[] this->mEmpArray;
            this->mEmpArray = NULL;
            this->mEmpNum = 0;
            this->mFileIsEmpty = true;
        }
        cout << "清空成功！" << endl;
    }
    system("pause");
    system("cls");
}


//退出系统
void WorkManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
