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
		cout << "����������ָ����ּ�0��7����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://��
			wm.Exit();
			break;
		case 1://��
			wm.Add_Emp();
			break;
		case 2://��
			wm.Show_Emp();
			break;
		case 3://ɾ
			wm.Del_Emp();
			break;
		case 4://��
			wm.Mod_Emp();
			break;
		case 5://��
			wm.Find_Emp();
			break;
		case 6://��
			wm.Sort_Emp();
			break;
		case 7://��
			wm.Clean_File();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	system("pause");
	return 0;
}