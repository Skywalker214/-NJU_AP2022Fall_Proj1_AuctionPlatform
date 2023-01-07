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


struct admin_pair
{
	int flag = 0;
	admin administrator = admin();
};

admin_pair admin_load()
{
	auction_settlement();
	char nm[6], pw[7];
	cout << "账号：";
	cin >> nm;
	cout << "密码：";
	cin >> pw;
	char name[6] = "admin";
	char password[7] = "123456";
	admin_pair temp;
	if (strcmp(nm, name) == 0 && strcmp(pw, password) == 0)
	{
		cout << "*********************登录成功！*********************" << endl;
		cout << "********************你好，管理员********************" << endl;
		temp.flag = 1;
	}
	if (strcmp(nm, name) == 0 && strcmp(pw, password) != 0)
	{
		cout << "*******************密码错误！！！*******************" << endl;
		cout << "******************即将返回登录界面******************" << endl;
		cout << "****************************************************" << endl << endl << endl;
	}
	if (strcmp(nm, name) != 0)
	{
		cout << "*******************未找到该管理员*******************" << endl;
		cout << "******************即将返回登录界面******************" << endl;
		cout << "****************************************************" << endl << endl << endl;
	}
	return temp;
}

void Admin()
{
	admin_pair temp = admin_load();
L:	if (temp.flag)
	{
		auction_settlement();
		admin me = temp.administrator;
		cout << "==========================================================================================================" << endl;
		cout << "1.查看所有商品  2.搜索商品  3.下架商品  4.查看所有报价  5.查看所有订单  6.查看所有用户  7.删除用户  8.注销" << endl;
		cout << "==========================================================================================================" << endl << endl;
		int opeartion;
		cout << "请输入操作：";
		cin >> opeartion;
		switch (opeartion)
		{
		case(1):me.check_all_commodity(); goto L; break;
		case(2):me.search_commodity(); goto L; break;
		case(3):me.delete_commodity(); goto L; break;
		case(4):me.check_all_offer(); goto L; break;
		case(5):me.check_all_order(); goto L; break;
		case(6):me.check_all_user(); goto L; break;
		case(7):me.ban_user(); goto L; break;
		case(8):break;
		default:cout << "无该操作，请重试" << endl << endl; goto L; break;
		}
	}
}


void admin::check_all_commodity()
{
	FILE* fp = fopen("commodity.txt", "r");
	cout << "************************************************************************************************" << endl;
	cout << "商品ID  名称                底价    数量  卖家ID  上架时间          下架时间          状态      " << endl;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
		temp.print_();
	}
	fclose(fp);
	cout << "************************************************************************************************" << endl << endl;
}

void admin::search_commodity()
{
	cout << "请输入您要搜索的关键词：";
	char target_word[21];
	cin >> target_word;
	FILE* fp = fopen("commodity.txt", "r");
	cout << "************************************************************************************************" << endl;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	int count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (fuzzy_match(cName, target_word) == 1)
		{
			count++;
			if(count==1)
				cout << "商品ID  名称                底价    数量  卖家ID  上架时间          下架时间          状态      " << endl;
			commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
			temp.print_();
		}
	}
	if(!count)
		cout << "未找到您想找的商品，即将返回功能界面" << endl;
	cout << "************************************************************************************************" << endl;
	fclose(fp);
}

void admin::delete_commodity()
{
	cout << "请输入您要下架的商品ID:";
	char target_cID[5];
	cin >> target_cID;
	vector<commodity> commoditys;
	int flag = 0;
	FILE* fp = fopen("commodity.txt", "r");
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
		if (strcmp(target_cID, cID) == 0)
		{
			if (temp.get_state() == 0)
				flag = 2;
			else
			{
				temp.delete_();
				flag = 1;
			}
		}
		commoditys.push_back(temp);
	}
	fclose(fp);
	FILE* fp1 = fopen("commodity.txt", "w");
	for (int i = 0; i < commoditys.size(); i++)
		commoditys[i].write_back(fp1);
	fclose(fp1);
	if (flag == 1)
	{
		cout << "*****************已成功下架该商品*******************" << endl << endl;
	}
	if (flag == 0)
	{
		cout << "****************未找到该商品，请重试****************" << endl << endl;
		delete_commodity();
	}
	if (flag == 2)
		cout << "**************该商品已是“被下架”状态**************" << endl << endl;
}

void admin::check_all_offer()
{
	FILE* fp = fopen("offer.txt", "r");
	cout << "**************************************************************************************" << endl;
	cout << "报价ID  商品ID  单价    数量  总价    时间              卖家ID  买家ID  状态          " << endl;
	char ofID[5]; char cID[5]; double up; int num; double exp; char t[17]; char sID[5]; char bID[5]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%d\n", ofID, cID, &up, &num, &exp, t, sID, bID, &sta);
		offer temp(ofID, cID, up, num, exp, t, sID, bID, sta);
		temp.print_();
	}
	fclose(fp);
	cout << "**************************************************************************************" << endl << endl;
}

void admin::check_all_order()
{
	FILE* fp = fopen("order.txt", "r");
	cout << "******************************************************************************************" << endl;
	cout << "订单ID  商品ID  单价    数量  总价    报价时间          成交时间          卖家ID  买家ID  " << endl;
	char orID[5]; char cID[5]; double up; int num; double exp; char oft[17]; char ort[17]; char sID[5]; char bID[5];
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%s\n", orID, cID, &up, &num, &exp, oft, ort, sID, bID);
		order temp(orID, cID, up, num, exp, oft, ort, sID, bID);
		temp.print_();
	}
	fclose(fp);
	cout << "******************************************************************************************" << endl << endl;
}

void admin::check_all_user()
{
	FILE* fp = fopen("user.txt", "r");
	cout << "****************************************************************************" << endl;
	cout << "用户ID  用户名    联系方式        地址                    钱包余额  状态    " << endl;
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		user temp(uID, uName, pw, te, addr, bal, sta);
		temp.print_();
	}
	fclose(fp);
	cout << "****************************************************************************" << endl << endl;
}

void admin::ban_user()
{
	cout << "请输入您要封禁的用户ID:";
	char target_uID[5];
	cin >> target_uID;
	vector<user> users;
	int flag = 0;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		user temp(uID, uName, pw, te, addr, bal, sta);
		if (strcmp(target_uID, uID) == 0)
		{
			if (temp.get_state() == 0)
				flag = 2;
			else
			{
				temp.ban();
				flag = 1;
			}
		}
		users.push_back(temp);
	}
	fclose(fp);
	FILE* fp1 = fopen("user.txt", "w");
	for (int i = 0; i < users.size(); i++)
		users[i].write_back(fp1);
	fclose(fp1);
	if (flag == 1)
	{
		cout << "*****************已成功封禁该用户*******************" << endl << endl;
	}
	if (flag == 0)
	{
		cout << "****************未找到该用户，请重试****************" << endl << endl;
		ban_user();
	}
	if (flag == 2)
		cout << "*******************该用户已被封禁*******************" << endl << endl;
}