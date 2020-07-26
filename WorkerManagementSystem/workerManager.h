#pragma once
#include<iostream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "EmpFile.txt"
using namespace std;

class WorkManager
{
public:

	WorkManager();//构造函数

	void Show_Menu();//显示菜单

	void Exit();//退出系统

	int m_EmpNum;//记录职工人数

	Worker** m_EmpArray;//职工数组指针

	void Add_Emp();//添加职工

	void save();//保存文件

	bool m_FileIsEmpty;//判断文件是否为空

	int get_EmpNum();//统计文件中已经记录的人数

	void init_Emp();//初始化员工，从文件读入数组

	void Show_Emp();//显示职工信息

	void Del_Emp();//删除职工

	int SomeOneIsExist(int id);//判断职工是否存在，存则返回数组位置，不存在返回-1

	void Mod_Emp();//修改职工信息

	void Find_Emp();//查找某职工

	void Sort_Emp();//排序

	void Clean_File();//清空文件

	~WorkManager();//析构函数

};
