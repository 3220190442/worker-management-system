//��ͨԱ�����̳�worker.h
#pragma once
#include"worker.h"
#include<iostream>
using namespace std;

class Employee :public Worker
{
public:
	Employee(int id,string name,int dId);//���캯��
	virtual void showInfo();//��ʾְ��������Ϣ
	virtual string getDeptName();//��ȡ��λ����
};