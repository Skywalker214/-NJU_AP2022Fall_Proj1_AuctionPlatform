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
commodity::commodity(char cID[5], char cName[21], double p, int num, char des[201], char sID[5], char addT[17], char reT[17], int sta)
{
	strcpy(commodityID, cID);
	strcpy(commodityName, cName);
	price = p;
	number = num;
	strcpy(description, des);
	strcpy(sellerID, sID);
	strcpy(addedTime, addT);
	strcpy(removeTime, reT);
	state = sta;
}

void commodity::print_()
{
	printf("%-8s%-20s%-8.1lf%-6d%-8s%-18s%-18s", commodityID, commodityName, price, number, sellerID, addedTime, removeTime);
	//printf("%-10s%-22s%-10.1lf%-8d%-10s%-22s%-22s", commodityID, commodityName, price, number, sellerID, addedTime, removeTime);
	if (state)
		printf("%s\n", "onAuction");
	else
		printf("%s\n", "removed");
}

int commodity::get_state()
{
	return state;
}

void commodity::write_back(FILE* fp)
{
	fprintf(fp, "%s %s %.1lf %d %s %s %s %s %d\n", commodityID, commodityName, price, number, description, sellerID, addedTime, removeTime, state);
}

void commodity::delete_()
{
	state = 0;
}

void commodity::print_detail()
{
	cout << "商品ID：" << commodityID << endl;
	cout << "商品名称：" << commodityName << endl;
	cout << "底价：" << price << endl;
	cout << "剩余数量：" << number << endl;
	cout << "商品描述：" << description << endl;
	cout << "卖家ID：" << sellerID << endl;
	cout << "上架时间：" << addedTime << endl;
	cout << "下架时间：" << removeTime << endl;
}

int commodity::get_num()
{
	return number;
}

double commodity::get_price()
{
	return price;
}

char* commodity::get_cID()
{
	return commodityID;
}

char* commodity::get_sID()
{
	return sellerID;
}

void commodity::modify()
{
L:	cout << "请选择您要修改的项目（1.商品名称 2.商品底价 3.商品描述 4.拍卖截止时间）：";
	int opeartion;
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):
		cout << "请输入新的商品名称：";
		char new_name[21];
		cin >> new_name;
		strcpy(commodityName, new_name);
		break;
	case(2):
		cout << "请输入新的商品价格(单位：人民币，精确到“角”)：";
		double new_price;
		cin >> new_price;
		price = new_price;
		break;
	case(3):
		cout << "请输入新的商品描述：";
		char new_description[201];
		cin >> new_description;
		strcpy(description, new_description);
		break;
	case(4):
		cout << "请输入拍卖截止时间（格式：YYYY-MM-DD,hh:mm）：";
		char new_reT[17];
		cin >> new_reT;
		strcpy(removeTime, new_reT);
		break;
	default:
		cout << "无该操作，请重试";
		goto L;
		break;
	}
}