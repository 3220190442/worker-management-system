#include "workerManager.h"

WorkManager::WorkManager()//完成构造函数
{
	//1、若文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		//初始化记录人数为0
		this->m_EmpNum = 0;
		//初始化数组指针为空
		this->m_EmpArray = NULL;
		//初始化文件为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2、文件存在，但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件无内容！" << endl;
		//初始化记录人数为0
		this->m_EmpNum = 0;
		//初始化数组指针为空
		this->m_EmpArray = NULL;
		//初始化文件为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、文件存在且不为空
	int num = this->get_EmpNum();
	cout <<  endl;
	cout << "\t\t职工管理系统" << endl;
	cout << endl;
	cout << "\t\t *信息预览*" << endl;
	cout << endl;
	cout << "从本地文件中读取得当前在职人数：" << num << "\t详细名单如下：" << endl << endl;
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//调用初始化函数，将文件中的数据读取到数组中
	this->init_Emp();
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_ID
			<< "\t职工姓名：" << this->m_EmpArray[i]->m_Name
			<< "\t部门编号：" << this->m_EmpArray[i]->m_DeptID << endl;
	}
	cout << endl << endl << "操作菜单：" << endl;
}

void WorkManager::Show_Menu()//显示菜单
{
	cout << "***********************************************" << endl;
	cout << "**********   欢迎使用职工管理系统！  **********" << endl;
	cout << "*************   0.退出管理程序   **************" << endl;
	cout << "*************   1.添加职工信息   **************" << endl;
	cout << "*************   2.显示职工信息   **************" << endl;
	cout << "*************   3.删除离职员工   **************" << endl;
	cout << "*************   4.编辑职工信息   **************" << endl;
	cout << "*************   5.查找职工信息   **************" << endl;
	cout << "*************   6.按照编号排序   **************" << endl;
	cout << "*************   7.清空信息文档   **************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
}

void WorkManager::Exit()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void WorkManager::Add_Emp()//添加职工
{
	cout << "请输入批量添加职工人数：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//计算空间的大小
		int newSize = this->m_EmpNum + addNum;//新空间人数=原来记录的+新增的
		Worker** newSpace = new Worker * [newSize];
		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;//部门
			cout << "请输入第" << i + 1 << "个新职工的 编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的 姓名：" << endl;
			cin >> name;
			cout << "请选择第" << i + 1 << "个新职工的 岗位：" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原空间
		delete[] this->m_EmpArray;
		//把指针指向新开辟的空间
		this->m_EmpArray = newSpace;
		//更新此时员工总人数
		this->m_EmpNum = newSize;
		//输出成功添加的信息
		cout << "成功添加了" << addNum << "名新职工！" << endl;
		//文件为空标志更改
		this->m_FileIsEmpty = false;
		//保存到文件中
		this->save();
	}
	else
	{
		cout << "非法输入" << endl;
	}
	//按任意键后清屏，并回到上级目录
	system("pause");
	system("cls");

}

void WorkManager::save()//保存文件
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//以输出方式的打开文件，即写文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}

int WorkManager::get_EmpNum()//统计文件中记录的人数
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;//文件中读到一个就统计一个人数
	}
	return num;
}

void WorkManager::init_Emp()//初始化员工，把文件中的人分类别地读进一个数组中
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else//老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();


}

void WorkManager::Show_Emp()//显示职工信息
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "在显示中遇到问题：文件为空（文件不存在/文件无内容）！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();//利用多态打印每类别人员的信息
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");

}


void WorkManager::Del_Emp()//删除职工，数组中删除就是前移，不要忘记数组记录数量减1
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入需要删除的职工的编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->SomeOneIsExist(id);
		string del_name = this->m_EmpArray[index]->m_Name;
		if (index != -1)
		{
			//不等于-1说明职工存在，数据要从指定位置开始前移覆盖
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			//数组中已经删除了，并且人数-1。接下来要把结果保存在文件中
			this->save();
			cout << "已成功删除：" << del_name << endl;
		}
		else
		{
			cout << "删除失败，没有该编号职工" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");


}

int WorkManager::SomeOneIsExist(int id)//判断职工是否存在，给删除功能用，存则返回数组位置，不存在返回-1
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到了指定编号的职工
			index = i;
			break;
		}
	}
	return index;
}

void WorkManager::Mod_Emp()//修改职工信息
{
	if (this->m_FileIsEmpty) { cout << "文件不存在或内容为空" << endl; }
	else {
		cout << "请输入需要修改的职工的编号：" << endl;
		int id;
		cin >> id;
		int result = this->SomeOneIsExist(id);
		if (result != -1)
		{
			//有这么个人
			delete this->m_EmpArray[result];//按原来的先删除了再新建一个
			int newId = 0;
			string newName = "";
			int newdSelect = 0;
			cout << "以查询到该职工，请输入新的编号：" << endl;
			cin >> newId;
			cout << "请输入新的姓名：" << endl;
			cin >> newName;
			cout << "请选择新的岗位：1.员工 2.经理 3.老板" << endl;
			cin >> newdSelect;
			//根据不同的岗位选择，接下来创建不同的对象
			//先创建一个父类的指针
			Worker* worker = NULL;
			switch (newdSelect)
			{
			case 1:
				worker = new Employee(newId, newName, newdSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, newdSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, newdSelect);
				break;
			default:
				break;
			}

			//更新到数组中
			this->m_EmpArray[result] = worker;
			cout << "修改成功" << endl;
			//保存文件
			this->save();
		}
		else
		{
			cout << "该编号职工不存在！" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkManager::Find_Emp()//查找某职工
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或无内容" << endl;
	}
	else
	{
		cout << "请选择查找方式：" << endl;
		cout << "1.按职工的编号查询" << endl;
		cout << "2.按职工的姓名查询" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			//用户选择了按编号查找
			int id;
			cout << "请输入需要查找的职工编号：" << endl;
			cin >> id;
			int result = SomeOneIsExist(id);
			if (result != -1)
			{
				cout << "查询成功，信息如下：" << endl;
				this->m_EmpArray[result]->showInfo();
			}
			else {
				cout << "没有找到该编号用户！" << endl;
			}
		}
		else if (select == 2)
		{
			//按姓名查找
			string name;
			cout << "请输入需要查找的职工姓名：" << endl;
			cin >> name;
			bool flag = false;//定义一个标志，默认false，即没有找到
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找到编号为"
						<< this->m_EmpArray[i]->m_ID
						<< "号员工的信息如下：" << endl;

					flag = true;//一旦进入if中，就改为true，即至少有一个符合输入姓名的

					this->m_EmpArray[i]->showInfo();//调用显示信息的接口
				}
			}
			if (flag == false)//循环结束了还是false标志的话...
			{
				cout << "没有找到该姓名用户！" << endl;
			}
		}
		else
		{
			cout << "非法输入！" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}


void WorkManager::Sort_Emp()//排序
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或无内容" << endl;
		//按任意键清屏
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择按编号排序的方式：1.升序 2.降序" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值或最大值的下标（不确定升降序）

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)//降序
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else
				{
					cout << "非法输入" << endl;
				}
			}
			//判断一开始认定的最值是不是真实的最值，如果不是，则交换数据
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序结果如下：" << endl;
		this->save();//如果想改动文件中的顺序，则加上这行，即把排好的数组保存到文件中
		this->Show_Emp();

	}

}


void WorkManager::Clean_File()//清空文件
{
	cout << "此操作不可逆转，确认清空文件？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "请输入密码：" << endl;
		string key = "";
		cin >> key;
		if (key == "密码")
		{
			//清空文件
			ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
			ofs.close();

			if (this->m_EmpArray != NULL)//如果数组不为空，则置空每个不为零的元素
			{
				//删除堆区每个职工对象
				for (int i = 0; i < m_EmpNum; i++)
				{
					delete this->m_EmpArray[i];//每个职工本身删除
					this->m_EmpArray[i] = NULL;//每个职工指针置空
				}
				//删除堆区数组指针
				delete[] this->m_EmpArray;//数组本身删除
				this->m_EmpArray = NULL;//数组指针置空

				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			cout << "文件已清空！" << endl;

		}
		else
		{
			cout << "密码错误！" << endl;
			return;
		}
		//按任意键清屏
		system("pause");
		system("cls");
	}	
	else
	{
		//2 fanhui
		system("cls");
	}
}

WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)//如果数组不为空，则置空每个不为零的元素
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}