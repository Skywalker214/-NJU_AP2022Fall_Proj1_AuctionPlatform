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
int fuzzy_match(char a[], char b[])
{
	int i, j;
	int la = 0, lb = 0;
	for (i = 0; a[i] != '\0'; i++)
		la++;
	for (i = 0; b[i] != '\0'; i++)
		lb++;
	int flag = 0;
	for (i = 0; i < la - lb + 1; i++)
	{
		int flag1 = 1;
		for (j = 0; j < lb; j++)
		{
			if (a[i + j] != b[j])
				flag1 = 0;
		}
		if (flag1 == 1)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

char* get_time()//2022-10-05,23:32
{
	//char s_time[17];
	char* s_time=new char[17];
	time_t nowTime;
	nowTime = time(NULL);
	struct tm* sysTime = localtime(&nowTime);
	s_time[0] = (sysTime->tm_year + 1900) / 1000 + '0';
	s_time[1] = ((sysTime->tm_year + 1900) / 100) % 10 + '0';
	s_time[2] = ((sysTime->tm_year + 1900) / 10) % 10 + '0';
	s_time[3] = (sysTime->tm_year + 1900) % 10 + '0';
	s_time[4] = '-';
	s_time[5] = (sysTime->tm_mon + 1) / 10 + '0';
	s_time[6] = (sysTime->tm_mon + 1) % 10 + '0';
	s_time[7] = '-';
	s_time[8] = (sysTime->tm_mday) / 10 + '0';
	s_time[9] = (sysTime->tm_mday) % 10 + '0';
	s_time[10] = ',';
	s_time[11] = (sysTime->tm_hour) / 10 + '0';
	s_time[12] = (sysTime->tm_hour) % 10 + '0';
	s_time[13] = ':';
	s_time[14] = (sysTime->tm_min) / 10 + '0';
	s_time[15] = (sysTime->tm_min) % 10 + '0';
	s_time[16] = '\0';
	return s_time;
}

order make_order(char new_cID[5], double new_p, int new_num, char new_ofT[17], char new_orT[17], char new_sID[5], char new_bID[5])
{
	char new_orID[5];
	FILE* fp = fopen("order.txt", "r");
	char orID_[5]; char cID_[5]; double up_; int num_; double exp_; char oft_[17]; char ort_[17]; char sID_[5]; char bID_[5];
	char max_orID_[5] = "R000";
	for (int i = 0; feof(fp) == 0; i++)
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%s\n", orID_, cID_, &up_, &num_, &exp_, oft_, ort_, sID_, bID_);	
		strcpy(max_orID_, max(max_orID_, orID_));
	}
	fclose(fp);
	strcpy(new_orID, max_orID_);
	for (int j = 3; j > 1; j--)
	{
		new_orID[j]++;
		if (new_orID[j] > '9')
			new_orID[j] -= 10;
		else
			break;
	}
	order ret(new_orID, new_cID, new_p, new_num, new_p * new_num, new_ofT, new_orT, new_sID, new_bID);

	FILE* fp1 = fopen("order.txt", "a+");
	ret.write_back(fp1);
	fclose(fp1);

	return ret;
}

void cal_money(char the_uID[5], double money)
{
	vector<user> users;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		if (strcmp(uID, the_uID) == 0)
		{
			user temp(uID, uName, pw, te, addr, bal + money, sta);
			users.push_back(temp);
		}
		else
		{
			user temp(uID, uName, pw, te, addr, bal, sta);
			users.push_back(temp);
		}
	}
	fclose(fp);
	FILE* fp1 = fopen("user.txt", "w");
	for (int i = 0; i < users.size(); i++)
		users[i].write_back(fp1);
	fclose(fp1);
}

void auction_settlement()
{
	FILE* fp = fopen("commodity.txt", "r");
	vector<commodity> commoditys;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (sta == 1)
		{
			char time_of_now[17];
			strcpy(time_of_now, get_time());
			if (strcmp(time_of_now, reT) > 0)
			{
				vector<offer> target_offers;
				vector<offer> other_offers;
				FILE* fp1 = fopen("offer.txt", "r");
				char ofID_[5]; char cID_[5]; double up_; int num_; double exp_; char t_[17]; char sID_[5]; char bID_[5]; int sta_;
				while (!feof(fp1))
				{
					fscanf(fp1, "%s%s%lf%d%lf%s%s%s%d\n", ofID_, cID_, &up_, &num_, &exp_, t_, sID_, bID_, &sta_);
					offer temp(ofID_, cID_, up_, num_, exp_, t_, sID_, bID_, sta_);
					if (strcmp(cID_, cID) == 0 && sta_ == -1)
						target_offers.push_back(temp);
					else
						other_offers.push_back(temp);
				}
				fclose(fp1);
				//rank target_offers by unitprice
				//vector<order> new_order;
				int max_p_i = 0;
				while (num > 0 && max_p_i != -1)
				{
					max_p_i = -1;
					for (int i = 0; i < target_offers.size(); i++)
					{
						if (target_offers[i].get_state() == -1)
						{
							if (max_p_i == -1)
								max_p_i = i;
							else
							{
								if (target_offers[i].get_up() > target_offers[max_p_i].get_up())
									max_p_i = i;
							}
						}
					}
					if (max_p_i != -1)
					{
						int final_num = (num >= target_offers[max_p_i].get_num()) ? target_offers[max_p_i].get_num() : num;
						num -= final_num;
						target_offers[max_p_i].change_state(final_num);
						char new_cID[5]; char new_ofT[17]; char new_orT[17]; char new_sID[5]; char new_bID[5];
						strcpy(new_cID, target_offers[max_p_i].get_cID());
						strcpy(new_ofT, target_offers[max_p_i].get_ofT());
						strcpy(new_orT, get_time());
						strcpy(new_sID, target_offers[max_p_i].get_sID());
						strcpy(new_bID, target_offers[max_p_i].get_bID());
						order new_one = make_order(new_cID, target_offers[max_p_i].get_up(), final_num, new_ofT, new_orT, new_sID, new_bID);//make order and write back
						//new_order.push_back(new_one);
						cal_money(new_sID, final_num * target_offers[max_p_i].get_up());//give money to seller
						if (target_offers[max_p_i].get_num() > final_num)//return money for half-success offer
							cal_money(new_bID, (target_offers[max_p_i].get_num() - final_num) * target_offers[max_p_i].get_up());
					}
				}
				for (int i = 0; i < target_offers.size(); i++)//return money for unsuccess offer
				{
					if (target_offers[i].get_state() == -1)
					{
						target_offers[max_p_i].change_state(0);
						char new_bID[5];
						strcpy(new_bID, target_offers[i].get_bID());
						cal_money(new_bID, target_offers[i].get_num() * target_offers[i].get_up());
					}
				}
				FILE* fp_of = fopen("offer.txt", "w");
				for (int i = 0; i < target_offers.size(); i++)
					target_offers[i].write_back(fp_of);
				for (int i = 0; i < other_offers.size(); i++)
					other_offers[i].write_back(fp_of);
				fclose(fp_of);
				sta = 0;
			}
		}
		//modify commodity state, write back
		commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
		commoditys.push_back(temp);
		FILE* fp1 = fopen("commodity.txt", "w");
		for (int i = 0; i < commoditys.size(); i++)
			commoditys[i].write_back(fp1);
		fclose(fp1);
	}
	fclose(fp);
}