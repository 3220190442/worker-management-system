//����ְ����
#pragma once
#include<iostream>
using namespace std;
class Worker
{
public:
	//��ʾְ��������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;
	//ְ�����
	int m_ID;
	//ְ������;
	string m_Name;
	//���ű��
	int m_DeptID;
};