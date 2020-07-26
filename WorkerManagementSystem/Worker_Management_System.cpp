/*

项目提供了以下的7个功能

本文件是main函数

通过对象wm来调用各个函数

*/
#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{

	WorkManager wm;
	int choice = 0;

	while (true)
	{
		wm.Show_Menu();
		cout << "请输入您的指令（数字键0至7）：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退
			wm.Exit();
			break;
		case 1://增
			wm.Add_Emp();
			break;
		case 2://显
			wm.Show_Emp();
			break;
		case 3://删
			wm.Del_Emp();
			break;
		case 4://改
			wm.Mod_Emp();
			break;
		case 5://查
			wm.Find_Emp();
			break;
		case 6://排
			wm.Sort_Emp();
			break;
		case 7://清
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}