#pragma once
#include "user.h"
#include<iostream>
class offer				//出价记录（不一定达成交易）
{
protected:
	char offerID[5];	//F001
	char commodityID[5];
	double unitPrice;
	int number;
	double expenses;	//总交易额
	char time[17];		//报价时间：YYYY-MM-DD,hh:mm
	char sellerID[5];
	char buyerID[5];
	int state;			//-2: 已取消  -1: 待确认  0: 未达成交易  i: 交易了i个物品（0 < i <= number)
public:
	offer(char ofID[5], char cID[5], double up, int num, double exp, char t[17], char sID[5], char bID[5], int sta);
	void modify(double p, int num, user &u);		//修改报价
	void cancel(user &u);		//取消报价
	void print_();		//打印信息
	void write_back(FILE* fp);		//写回文件
	int get_state();		//获取报价状态
	double get_up();	//获取交易单价
	int get_num();			//获取交易数量
	void change_state(int new_state);		//修改报价状态
	char* get_cID();		//获取商品ID
	char* get_ofT();		//获取出价ID
	char* get_sID();		//获取卖家ID
	char* get_bID();		//获取买家ID
};

class order				//订单记录
{
protected:
	char orderID[5];	//R001
	char commodityID[5];
	double unitPrice;
	int number;
	double expenses;		//总交易额
	char offertime[17];		//报价时间
	char ordertime[17];		//成交时间
	char sellerID[5];
	char buyerID[5];
public:
	order(char orID[5], char cID[5], double up, int num, double exp, char oft[17], char ort[17], char sID[5], char bID[5]);
	void print_();			//打印信息
	void write_back(FILE* fp);			//写回文件
};