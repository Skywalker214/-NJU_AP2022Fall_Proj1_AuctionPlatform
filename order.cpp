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


offer::offer(char ofID[5], char cID[5], double up, int num, double exp, char t[17], char sID[5], char bID[5], int sta)
{
	strcpy(offerID, ofID);
	strcpy(commodityID, cID);
	unitPrice = up;
	number = num;
	expenses = exp;
	strcpy(time, t);
	strcpy(sellerID, sID);
	strcpy(buyerID, bID);
	state = sta;
}

void offer::print_()
{
	printf("%-8s%-8s%-8.1lf%-6d%-8.1lf%-18s%-8s%-8s", offerID, commodityID, unitPrice, number, expenses, time, sellerID, buyerID);
	//printf("%-10s%-10s%-10.1lf%-8d%-10.1lf%-20s%-10s%-10s", offerID, commodityID, unitPrice, number, expenses, time, sellerID, buyerID);
	if (state == -1)
		printf("%s\n", "待确认");
	else if (state == 0)
		printf("%s\n", "未成交");
	else if (state == -2)
		printf("%s\n", "已取消");
	else
		printf("%s%d\n", "成交个数：", state);
}

void offer::write_back(FILE* fp)
{
	fprintf(fp, "%s %s %.1lf %d %.1lf %s %s %s %d\n", offerID, commodityID, unitPrice, number, expenses, time, sellerID, buyerID, state);
}

void offer::modify(double price, int num, user& u)
{
	cout << "======================================" << endl;
	cout << "1.修改报价  2.修改购买数量  3.全部修改" << endl;
	cout << "======================================" << endl << endl;
	cout << "请选择你要修改的内容：";
	int opeartion;
	cin >> opeartion;
	int new_buy_num = number;
	double new_buy_price = unitPrice;
	double old_exp = number * unitPrice;
	if (opeartion == 2 || opeartion == 3)
	{
	L1:		cout << "请修改您要购买的数量（至多为" << num << "）：";
		cin >> new_buy_num;
		if (new_buy_num > num)
		{
			cout << "数量不足，请重新输入数量!" << endl;
			goto L1;
		}
	}
	if (opeartion == 1 || opeartion == 3)
	{
	L2:		cout << "请修改您的报出的单价（至少为" << price << "）：";
		cin >> new_buy_price;
		if (new_buy_price < price)
		{
			cout << "出价太低，请重新出价！" << endl;
			goto L2;
		}
	}
	if (new_buy_num * new_buy_price > u.get_balance() + old_exp)
	{
		cout << "您的余额不足，无法修改，即将返回功能界面：" << endl;
	}
	else
	{
		unitPrice = new_buy_price;
		number = new_buy_num;
		expenses = new_buy_price * new_buy_num;
		//u.change_balance(old_exp - expenses);
		cal_money(u.get_ID(), old_exp - expenses);
		strcpy(time, get_time());
	}
}

void offer::cancel(user& u)
{
	state = -2;
	u.change_balance(expenses);
}

int offer::get_state()
{
	return state;
}

double offer::get_up()
{
	return unitPrice;
}

int offer::get_num()
{
	return number;
}

void offer::change_state(int new_state)
{
	state = new_state;
}

char* offer::get_cID()
{
	return commodityID;
}

char* offer::get_ofT()
{
	return time;
}

char* offer::get_sID()
{
	return sellerID;
}

char* offer::get_bID()
{
	return buyerID;
}


order::order(char orID[5], char cID[5], double up, int num, double exp, char oft[17], char ort[17], char sID[5], char bID[5])
{
	strcpy(orderID, orID);
	strcpy(commodityID, cID);
	unitPrice = up;
	number = num;
	expenses = exp;
	strcpy(offertime, oft);
	strcpy(ordertime, ort);
	strcpy(sellerID, sID);
	strcpy(buyerID, bID);
}

void order::print_()
{
	printf("%-8s%-8s%-8.1lf%-6d%-8.1lf%-18s%-18s%-8s%-8s\n", orderID, commodityID, unitPrice, number, expenses, offertime, ordertime, sellerID, buyerID);
	//printf("%-10s%-10s%-10.1lf%-8d%-10.1lf%-22s%-22s%-10s%-10s\n", orderID, commodityID, unitPrice, number, expenses, offertime, ordertime, sellerID, buyerID);
}

void order::write_back(FILE* fp)
{
	fprintf(fp, "%s %s %.1lf %d %.1lf %s %s %s %s\n", orderID, commodityID, unitPrice, number, expenses, offertime, ordertime, sellerID, buyerID);
}