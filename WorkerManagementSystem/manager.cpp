#include"manager.h"

Manager::Manager(int id, string name, int dId)//构造函数
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
void Manager::showInfo()//显示职工所有信息
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t岗位职责：" << "安排任务" << endl;
}
string Manager::getDeptName()//获取岗位名称
{
	return string("经理");
}