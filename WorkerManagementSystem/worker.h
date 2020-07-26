//抽象职工类
#pragma once
#include<iostream>
using namespace std;
class Worker
{
public:
	//显示职工所有信息
	virtual void showInfo() = 0;
	//获取岗位名称，这个函数有些愚蠢，重写时就是返回3个岗位
	virtual string getDeptName() = 0;
	//职工编号
	int m_ID;
	//职工姓名;
	string m_Name;
	//部门编号
	int m_DeptID;
};