#define _CRT_SECURE_NO_WARNINGS
#include "admin.h"
#include "user.h"
#include "commodity.h"
#include "order.h"
#include "helper.h"
#include "message.h"
#include<vector>
#include <stdio.h>
#include<cstring>
#include<iostream>
using namespace std;

int load()
{
	auction_settlement();
	int operation;
	cout << "=========================================" << endl;
	cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出" << endl;
	cout << "=========================================" << endl << endl;
	cout << "输入操作：";
	cin >> operation;
	return operation;
}


int main()
{
	auction_settlement();
L:	int operation = load();
	switch (operation)
	{
	case(1):User(); goto L; break;
	case(2):User_register(); goto L; break;
	case(3):Admin(); goto L; break;
	case(4):return 0; break;
	default:cout << "无该操作，请重试" << endl << endl; goto L; break;
	}
}