#pragma once
#include<time.h>
#include<iostream>
class commodity
{
private:
	char commodityID[5];
	char commodityName[21];
	double price;
	int number;
	char description[201];
	char sellerID[5];
	char addedTime[17];			//上架时间：YYYY-MM-DD,hh:mm
	char removeTime[17];		//下架时间：YYYY-MM-DD,hh:mm
	int state;					//0: removed  1: onAuction
public:
	commodity(){}
	commodity(char cID[5], char cName[21], double p, int num, char des[201], char sID[5], char addT[17], char reT[17], int sta);
	void print_();			//打印信息
	void delete_();			//下架
	void modify();			//修改信息
	int get_state();		//获取商品状态
	void write_back(FILE* fp);		//商品信息写回文件
	void print_detail();		//打印商品详细信息
	int get_num();			//获取商品数量
	double get_price();		//获取商品单价
	char* get_cID();		//获取商品ID
	char* get_sID();		//获取卖家ID
};
