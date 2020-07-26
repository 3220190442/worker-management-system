#include"employee.h"

Employee::Employee(int id, string name, int dId)//构造函数
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}
void Employee::showInfo()//显示职工所有信息
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->getDeptName()
		<< "\t岗位职责：" << "执行任务" << endl;
}
string Employee::getDeptName()//获取岗位名称
{
	return string("员工");
}