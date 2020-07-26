#include"boss.h"

Boss::Boss(int id, string name, int dId)//构造函数
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
void Boss::showInfo()//显示职工所有信息
{
	cout<< "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t岗位职责：" << "设计任务" << endl;
}
string Boss::getDeptName()//获取岗位名称
{
	return string("老板");
}