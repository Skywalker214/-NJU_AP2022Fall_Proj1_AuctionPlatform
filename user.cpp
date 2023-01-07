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


struct user_pair
{
	int flag = 0;
	user User = user();
};

user_pair user_load()
{
	auction_settlement();
	char nm[11], pw_[21];
	cout << "用户名：";
	cin >> nm;
	cout << "密码：";
	cin >> pw_;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	user_pair temp;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		if (strcmp(nm, uName) == 0 && strcmp(pw_, pw) == 0)
		{
			if(sta==1)
			{
				temp.flag = 1;
				temp.User = user(uID, uName, pw, te, addr, bal, sta);
				cout << "*******************登录成功！*******************" << endl;
				cout << "****************你好，" << uName << "****************" << endl;
				cout << "************************************************" << endl << endl << endl;
			}
			else
			{
				temp.flag = -2;
				cout << "*******************您已被封禁！*******************" << endl;
				cout << "**************如是误封，请联系管理员*************" << endl;
				cout << "***************************************************" << endl << endl << endl;
			}
		}
		if (strcmp(nm, uName) == 0 && strcmp(pw_, pw) != 0)
		{
			temp.flag = -1;
			cout << "*******************密码错误！！！*******************" << endl;
			cout << "******************即将返回登录界面******************" << endl;
			cout << "****************************************************" << endl << endl << endl;
		}
	}
	fclose(fp);
	if (temp.flag == 0)
	{
		cout << "*******************未找到该用户*******************" << endl;
		cout << "******************即将返回登录界面****************" << endl;
		cout << "**************************************************" << endl << endl << endl;
	}
	return temp;
}

void User()
{
	user_pair temp = user_load();
	if (temp.flag == 1)
	{
		user me = temp.User;
L:		auction_settlement();
		cout << "======================================================" << endl;
		cout << "1.我是买家  2.我是卖家  3.个人信息管理  4.信箱  5.注销" << endl;
		cout << "======================================================" << endl << endl;
		int opeartion;
		cout << "请输入操作：";
		cin >> opeartion;
		switch (opeartion)
		{
		case(1):me.buyer(); goto L; break;
		case(2):me.seller(); goto L; break;
		case(3):me.manage_my_info(); goto L; break;
		case(4):me.message_box(); goto L; break;
		case(5):break;
		default:cout << "无该操作，请重试" << endl << endl; goto L; break;
		}
	}
}

void User_register()
{
L:	cout << "请输入您想注册的用户名：";
	char new_name[11];
	cin >> new_name;
	int i = 0;
	//int num_of_user = -1;
	int flag = 0;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]="U000"; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	for (i = 0; feof(fp) == 0; i++)
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		if (strcmp(uName, new_name) == 0)
		{
			flag = 1;
		}
		//num_of_user++;
	}
	fclose(fp);
	if (flag == 1)
	{
		cout << "该用户名与已有用户名重复，请更换" << endl;
		goto L;
	}
	char new_ID[5]; char new_pw[21]; char new_tel[21]; char new_addr[41];
	//if (num_of_user == 0)
	//	strcpy(new_ID, "U001");
	//else
	//{
	//	strcpy(new_ID, uID);
	//	for (int j = 3; j > 1; j--)
	//	{
	//		new_ID[j]++;
	//		if (new_ID[j] > '9')
	//			new_ID[j] -= 10;
	//		else
	//			break;
	//	}
	//}
	strcpy(new_ID, uID);
	for (int j = 3; j > 1; j--)
	{
		new_ID[j]++;
		if (new_ID[j] > '9')
			new_ID[j] -= 10;
		else
			break;
	}
	cout << "请输入密码（不超过20位，仅包含小写字母和数字）：";
	cin >> new_pw;
	cout << "请输入联系方式：";
	cin >> new_tel;
	cout << "请输入地址（不超过20个字符，中文汉字或英文字母）：";
	cin >> new_addr;
	user new_one(new_ID, new_name, new_pw, new_tel, new_addr, 0.0, 1);
	FILE* fp1 = fopen("user.txt", "a");
	new_one.write_back(fp1);
	fclose(fp1);
	cout << "注册成功，即将返回登录界面" << endl << endl;
}

user::user(char uID[5], char uName[11], char pw[21], char te[21], char addr[41], double bal, int sta)
{
	strcpy(userID, uID);
	strcpy(userName, uName);
	strcpy(password, pw);
	strcpy(tel, te);
	strcpy(address, addr);
	balance = bal;
	state = sta;
}

void user::print_()
{
	printf("%-8s%-10s%-16s%-24s%-10.1lf", userID, userName, tel, address, balance);
	//printf("%-10s%-13s%-20s%-26s%-14.1lf", userID, userName, tel, address, balance);
	if (state)
		printf("%s\n", "active");
	else
		printf("%s\n", "inactive");

}

int user::get_state()
{
	return state;
}

void user::ban()
{
	state = 0;
}

void user::write_back(FILE* fp)
{
	fprintf(fp, "%s %s %s %s %s %.1lf %d\n", userID, userName, password, tel, address, balance, state);
}

void user::buyer()
{
L:	auction_settlement();
	cout << "========================================================================================================================" << endl;
	cout << "1.查看商品列表  2.搜索商品  3.查看商品详细信息  4.竞拍商品  5.查看历史报价  6.修改报价  7.查看历史订单  8.返回用户主界面" << endl;
	cout << "========================================================================================================================" << endl << endl;
	int opeartion;
	cout << "请输入操作：";
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):browse_all_commodity(); goto L; break;
	case(2):search_commodity(); goto L; break;
	case(3):print_detail_of_commodity(); goto L; break;
	case(4):make_offer(); goto L; break;
	case(5):check_my_offer(); goto L; break;
	case(6):modify_my_offer(); goto L; break;
	case(7):buyer_check_order(); goto L; break;
	case(8):break;
	default:cout << "无该操作，请重试" << endl << endl; goto L; break;
	}
}

void user::seller()
{
L:	auction_settlement();
	cout << "========================================================================================" << endl;
	cout << "1.发布商品  2.查看发布商品  3.修改商品信息  4.下架商品  5.查看历史订单  6.返回用户主界面" << endl;
	cout << "========================================================================================" << endl << endl;
	int opeartion;
	cout << "请输入操作：";
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):add_my_commodity(); goto L; break;
	case(2):check_my_commodity(); goto L; break;
	case(3):modify_my_commodity();; goto L; break;
	case(4):delete_my_commodity(); goto L; break;
	case(5):seller_check_order(); goto L; break;
	case(6):break;
	default:cout << "无该操作，请重试" << endl << endl; goto L; break;
	}
}

void user::manage_my_info()
{
L:	cout << "======================================" << endl;
	cout << "1.查看信息  2.修改信息  3.充值  4.返回" << endl;
	cout << "======================================" << endl << endl;
	int opeartion;
	cout << "请输入操作：";
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):check_my_info(); goto L; break;
	case(2):modify_my_info(); goto L; break;
	case(3):charge();; goto L; break;
	case(4):break;
	default:cout << "无该操作，请重试" << endl << endl; goto L; break;
	}
}

void user::browse_all_commodity()
{
	FILE* fp = fopen("commodity.txt", "r");
	cout << "************************************************************************************************" << endl;
	cout << "商品ID  名称                底价    数量  卖家ID  上架时间          下架时间          状态      " << endl;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (sta)
		{
			commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "************************************************************************************************" << endl << endl;
}

void user::search_commodity()
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
		if (sta)
		{
			if (fuzzy_match(cName, target_word) == 1)
			{
				count++;
				if (count == 1)
					cout << "商品ID  名称                底价    数量  卖家ID  上架时间          下架时间          状态      " << endl;
				commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
				temp.print_();
			}
		}
	}
	if (!count)
		cout << "未找到您想找的商品，即将返回功能界面" << endl;
	cout << "************************************************************************************************" << endl;
	fclose(fp);
}

void user::print_detail_of_commodity()
{
	cout << "请输入您想查看的商品的ID：";
	char target_ID[5];
	cin >> target_ID;
	FILE* fp = fopen("commodity.txt", "r");
	cout << "********************************************************************************************" << endl;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	int flag = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (sta)
		{
			if (strcmp(cID, target_ID) == 0)
			{
				flag++;
				commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
				temp.print_detail();
			}
		}
	}
	if(!flag)
		cout << "未找到该商品，即将返回功能界面" << endl;
	cout << "********************************************************************************************" << endl << endl;
}

void user::make_offer()
{
	cout << "请输入您准备购买的商品的ID：";
	char target_ID[5];
	cin >> target_ID;
	int flag = 0;
	FILE* fp = fopen("commodity.txt", "r");
	commodity target;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (strcmp(target_ID, cID) == 0)
		{
			if (sta)
			{
				if (strcmp(userID, sID) != 0)
				{
					flag = 1;
					target = commodity(cID, cName, p, num, des, sID, addT, reT, sta);
				}
				else
				{
					cout << "这是您上架的商品，请勿刷单" << endl;
					flag = 2;
				}
			}
			else
			{
				cout << "该商品已下架或已售罄，无法购买" << endl;
				flag = 3;
			}
		}
	}
	fclose(fp);
	if (flag == 0)
		cout << "未找到该商品，即将返回功能界面" << endl;
	if (flag == 1)
	{
		int buy_num;
		double buy_price;
L1:		cout << "请输入您要购买的数量（至多为" << target.get_num() << "）：";
		cin >> buy_num;
		if (buy_num > target.get_num())
		{
			cout << "数量不足，请重新输入数量!" << endl;
			goto L1;
		}
L2:		cout << "请输入您的报出的单价（至少为" << target.get_price() << "）：";
		cin >> buy_price;
		if (buy_price < target.get_price())
		{
			cout << "出价太低，请重新出价！" << endl;
			goto L2;
		}
		if (buy_num * buy_price > balance)
		{
			cout << "您的余额不足，无法购买，即将返回功能界面：" << endl;
		}
		else
		{
			balance -= buy_num * buy_price;
			FILE* fp1 = fopen("offer.txt", "r");
			//int num_of_offer = 0;
			char ofID[5]= "F000"; char cID[5]; double up; int num; double exp; char t[17]; char sID[5]; char bID[5]; int sta;
			char max_ofID[5] = "F000";
			for (int i = 0; feof(fp) == 0; i++)
			{
				fscanf(fp1, "%s%s%lf%d%lf%s%s%s%d\n", ofID, cID, &up, &num, &exp, t, sID, bID, &sta);
				strcpy(max_ofID, strcmp(max_ofID, ofID) > 0 ? max_ofID : ofID);
				//num_of_offer++;
			}
			fclose(fp1);
			char new_ID[5]; char new_time[17]; char new_cID[5]; char new_sID[5];
			/*if (num_of_offer == 0)
				strcpy(new_ID, "F001");
			else
			{
				strcpy(new_ID, ofID);
				for (int j = 3; j > 1; j--)
				{
					new_ID[j]++;
					if (new_ID[j] > '9')
						new_ID[j] -= 10;
					else
						break;
				}
			}*/
			strcpy(new_ID, max_ofID);
			for (int j = 3; j > 1; j--)
			{
				new_ID[j]++;
				if (new_ID[j] > '9')
					new_ID[j] -= 10;
				else
					break;
			}
			strcpy(new_time, get_time());
			strcpy(new_cID, target.get_cID());
			strcpy(new_sID, target.get_sID());
			offer new_one(new_ID, new_cID, buy_price, buy_num, buy_price * buy_num, new_time, new_sID, userID, -1);
			FILE* fp2 = fopen("offer.txt", "a");
			new_one.write_back(fp2);
			fclose(fp2);
			cout << "报价成功，请等待该商品竞拍结束" << endl;
			cout << "在竞拍结束前，你可以随时修改和取消报价" << endl;
			cal_money(this->userID, buy_num * buy_price * (-1));
		}
	}
}

void user::check_my_offer()
{
	FILE* fp = fopen("offer.txt", "r");
	cout << "**************************************************************************************" << endl;
	cout << "报价ID  商品ID  单价    数量  总价    时间              卖家ID  买家ID  状态          " << endl;
	char ofID[5]; char cID[5]; double up; int num; double exp; char t[17]; char sID[5]; char bID[5]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%d\n", ofID, cID, &up, &num, &exp, t, sID, bID, &sta);
		if (strcmp(bID, userID) == 0)
		{
			offer temp(ofID, cID, up, num, exp, t, sID, bID, sta);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "**************************************************************************************" << endl << endl;
}

void user::modify_my_offer()
{
	cout << "请输入您要变更的报价ID：";
	char target_ID[5];
	cin >> target_ID;
	cout << "请问您要（1.修改报价  2.取消报价）：";
	int opeartion;
	cin >> opeartion;
	FILE* fp = fopen("offer.txt", "r");
	vector<offer> offers;
	int flag = 0;
	char ofID[5]; char cID[5]; double up; int num; double exp; char t[17]; char sID[5]; char bID[5]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%d\n", ofID, cID, &up, &num, &exp, t, sID, bID, &sta);
		offer temp(ofID, cID, up, num, exp, t, sID, bID, sta);
		if (strcmp(ofID, target_ID) == 0)
		{
			if (strcmp(bID, userID) != 0)
			{
				cout << "这不是你的报价，请重试!" << endl;
				modify_my_offer();
			}
			else
			{
				if (sta == -1)
				{
					if (opeartion == 1)
					{
						FILE* fp1 = fopen("commodity.txt", "r");
						char cID_[5]; char cName_[21]; double p_; int num_; char des_[201]; char sID_[5]; char addT_[17]; char reT_[17]; int sta_;
						while (!feof(fp1))
						{
							fscanf(fp1, "%s%s%lf%d%s%s%s%s%d\n", cID_, cName_, &p_, &num_, des_, sID_, addT_, reT_, &sta_);
							if (strcmp(cID, cID_) == 0)
								break;
						}
						temp.modify(p_, num_, *this);
						cout << "报价修改成功！" << endl;
					}
					else if (opeartion == 2)
					{
						temp.cancel(*this);
						cout << "报价取消成功！" << endl;
					}
				}
				else
					cout << "该报价已结算或取消，无法变更！" << endl;
			}
		}
		offers.push_back(temp);
	}
	fclose(fp);
	FILE* fp1 = fopen("offer.txt", "w");
	for (int i = 0; i < offers.size(); i++)
		offers[i].write_back(fp1);
	fclose(fp1);
}

void user::buyer_check_order()
{
	FILE* fp = fopen("order.txt", "r");
	cout << "******************************************************************************************" << endl;
	cout << "订单ID  商品ID  单价    数量  总价    报价时间          成交时间          卖家ID  买家ID  " << endl;
	char orID[5]; char cID[5]; double up; int num; double exp; char oft[17]; char ort[17]; char sID[5]; char bID[5];
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%s\n", orID, cID, &up, &num, &exp, oft, ort, sID, bID);
		if (strcmp(bID, userID) == 0)
		{
			order temp(orID, cID, up, num, exp, oft, ort, sID, bID);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "******************************************************************************************" << endl << endl;
}

void user::add_my_commodity()
{
	char new_ID[5]; char new_name[21]; double new_price; int new_num; char new_des[201]; char new_addT[17]; char new_reT[17];
	cout << "请输入您想上架的商品名称：";
	cin >> new_name;
	cout << "请设定该商品的底价(单位：人民币，精确到“角”)：";
	cin >> new_price;
	cout << "请输入您想上架的商品数量：";
	cin >> new_num;
	cout << "请为您想上架的商品添加描述：";
	cin >> new_des;
	cout << "请为您想上架的商品设置拍卖截止时间（格式：YYYY-MM-DD,hh:mm）:";
	cin >> new_reT;
	FILE* fp = fopen("commodity.txt", "r");
	char cID[5]="C000"; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	//int num_of_com = 0;
	for (int i = 0; feof(fp) == 0; i++)
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		//num_of_com++;
	}
	fclose(fp);
	//if (num_of_com == 0)
	//	strcpy(new_ID, "C001");
	//else
	//{
	//	strcpy(new_ID, cID);
	//	for (int j = 3; j > 1; j--)
	//	{
	//		new_ID[j]++;
	//		if (new_ID[j] > '9')
	//			new_ID[j] -= 10;
	//		else
	//			break;
	//	}
	//}
	strcpy(new_ID, cID);
	for (int j = 3; j > 1; j--)
	{
		new_ID[j]++;
		if (new_ID[j] > '9')
			new_ID[j] -= 10;
		else
			break;
	}
	strcpy(new_addT, get_time());
	commodity new_one(new_ID, new_name, new_price, new_num, new_des, userID, new_addT, new_reT, 1);
	FILE* fp1 = fopen("commodity.txt", "a");
	new_one.write_back(fp1);
	fclose(fp1);
	cout << "上架成功！" << endl << endl;
}

void user::check_my_commodity()
{
	FILE* fp = fopen("commodity.txt", "r");
	cout << "************************************************************************************************" << endl;
	cout << "商品ID  名称                底价    数量  卖家ID  上架时间          下架时间          状态      " << endl;
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		if (strcmp(sID, userID) == 0)
		{
			commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "************************************************************************************************" << endl << endl;
}

void user::modify_my_commodity()
{
	cout << "请输入您要修改的商品ID:";
	char target_cID[5];
	cin >> target_cID;
	vector<commodity> commoditys;
	FILE* fp = fopen("commodity.txt", "r");
	char cID[5]; char cName[21]; double p; int num; char des[201]; char sID[5]; char addT[17]; char reT[17]; int sta;
	int flag = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%s%s%s%s%d\n", cID, cName, &p, &num, des, sID, addT, reT, &sta);
		commodity temp(cID, cName, p, num, des, sID, addT, reT, sta);
		if (strcmp(target_cID, cID) == 0)
		{
			if (strcmp(sID, userID) == 0)
			{
				if (temp.get_state() == 0)
					flag = 2;
				else
				{
					temp.modify();
					flag = 1;
				}
			}
			else
				flag = 3;
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
		cout << "*****************已成功修改该商品*******************" << endl << endl;
	}
	if (flag == 0)
	{
		cout << "****************未找到该商品，请重试****************" << endl << endl;
		modify_my_commodity();
	}
	if (flag == 2)
		cout << "***************该商品已下架，无法修改***************" << endl << endl;
	if (flag == 3)
		cout << "************这不是你上架的商品，无法修改************" << endl << endl;

}

void user::delete_my_commodity()
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
			if (strcmp(sID, userID) == 0)
			{
				if (temp.get_state() == 0)
					flag = 2;
				else
				{
					temp.delete_();
					flag = 1;
				}
			}
			else
				flag = 3;
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
		delete_my_commodity();
	}
	if (flag == 2)
		cout << "**************该商品已是“被下架”状态**************" << endl << endl;
	if (flag == 3)
	{
		cout << "*************这不是您上架的商品，请重试*************" << endl << endl;
		delete_my_commodity();
	}
}

void user::seller_check_order()
{
	FILE* fp = fopen("order.txt", "r");
	cout << "******************************************************************************************" << endl;
	cout << "订单ID  商品ID  单价    数量  总价    报价时间          成交时间          卖家ID  买家ID  " << endl;
	char orID[5]; char cID[5]; double up; int num; double exp; char oft[17]; char ort[17]; char sID[5]; char bID[5];
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%d%lf%s%s%s%s\n", orID, cID, &up, &num, &exp, oft, ort, sID, bID);
		if (strcmp(sID, userID) == 0)
		{
			order temp(orID, cID, up, num, exp, oft, ort, sID, bID);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "******************************************************************************************" << endl << endl;
}

void user::check_my_info()
{
	cout << "用户ID：" << userID << endl;
	cout << "用户名：" << userName << endl;
	cout << "联系方式：" << tel << endl;
	cout << "地址：" << address << endl;
	cout << "钱包余额：" << balance << endl;
}

void user::modify_my_info()
{
	cout << "请输入您要修改的项目（1.用户名 2.联系方式 3.地址）：";
	int opeartion;
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):
	{
		cout << "请输入新的用户名：";
		char new_name[21];
		cin >> new_name;
		int flag = 0;
		FILE* fp = fopen("user.txt", "r");
		char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
		while (!feof(fp))
		{
			fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
			if (strcmp(uName, new_name) == 0)
			{
				flag = 1;
			}
		}
		fclose(fp);
		if (flag == 1)
		{
			cout << "该用户名与已有用户名重复，请更换" << endl;
			modify_my_info();
		}
		else
			cout << "修改成功" << endl;
	}
		break;
	case(2):
		cout << "请输入新的联系方式：";
		char new_tel[21];
		cin >> new_tel;
		strcpy(tel, new_tel);
		cout << "修改成功" << endl;
		break;
	case(3):
		cout << "请输入新的地址：";
		char new_addr[41];
		cin >> new_addr;
		strcpy(address, new_addr);
		cout << "修改成功" << endl;
		break;
	default:
		cout << "无该操作，请重试";
		modify_my_info();
		break;
	}
	vector<user> users;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		if(strcmp(uID,userID)==0)
		{
			user temp(userID, userName, password, tel, address, balance, state);
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

void user::charge()
{
	cout << "请输入充值金额：";
	double change;
	cin >> change;
	balance += change;
	vector<user> users;
	FILE* fp = fopen("user.txt", "r");
	char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
		if (strcmp(uID, userID) == 0)
		{
			user temp(userID, userName, password, tel, address, balance, state);
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

double user::get_balance()
{
	return balance;
}

void user::change_balance(double change)
{
	balance += change;
}

char* user::get_ID()
{
	return userID;
}

void user::message_box()
{
L:	auction_settlement();
	cout << "========================================================================" << endl;
	cout << "1.发送信息  2.查看收信箱  3.查看发信箱  4.查看信息详情  5.返回用户主界面" << endl;
	cout << "========================================================================" << endl << endl;
	int opeartion;
	cout << "请输入操作：";
	cin >> opeartion;
	switch (opeartion)
	{
	case(1):send_message(); goto L; break;
	case(2):check_receive_message(); goto L; break;
	case(3):check_send_message(); goto L; break;
	case(4):read_message();; goto L; break;
	case(5):break;
	default:cout << "无该操作，请重试" << endl << endl; goto L; break;
	}
}

void user::send_message()
{
	char rID[5];
L:	cout << "请输入收件人ID：";
	cin >> rID;
	if (strcmp(rID, userID) == 0)
	{
		cout << "无法给自己发信息哦，请重新选择收件人" << endl;
		goto L;
	}
	else
	{
		int flag = 0;
		FILE* fp = fopen("user.txt", "r");
		char uID[5]; char uName[11]; char pw[21]; char te[21]; char addr[41]; double bal; int sta;
		while (!feof(fp))
		{
			fscanf(fp, "%s%s%s%s%s%lf%d\n", uID, uName, pw, te, addr, &bal, &sta);
			if (strcmp(uID, rID) == 0)
			{
				flag = 1;
				break;
			}
		}
		fclose(fp);
		if (flag == 0)
		{
			cout << "未找到该用户，请查正ID后重试" << endl;
			goto L;
		}
		else
		{
			cout << "请输入您要发送的内容：" << endl;
			char text[201];
			cin >> text;
			char time_[17];
			strcpy(time_, get_time());
			char new_ID[5];
			FILE* fp1 = fopen("message.txt", "r");
			char mID[5]="M000"; char sID[5]; char rID_[5]; char c[201]; char t[17]; int sta;
			for (int i = 0; feof(fp1) == 0; i++)
			{
				fscanf(fp1, "%s%s%s%s%s%d\n", mID, sID, rID_, c, t, &sta);
			}
			fclose(fp1);
			strcpy(new_ID, mID);
			for (int j = 3; j > 1; j--)
			{
				new_ID[j]++;
				if (new_ID[j] > '9')
					new_ID[j] -= 10;
				else
					break;
			}
			message new_one(new_ID, userID, rID, text, time_, 0);
			FILE* fp2 = fopen("message.txt", "a");
			new_one.write_back(fp2);
			fclose(fp2);
			cout << "消息发送成功！" << endl << endl;
		}
	}
}

void user::check_receive_message()
{
	FILE* fp = fopen("message.txt", "r");
	cout << "**********************************************************" << endl;
	cout << "信息ID    发件人ID    收件人ID    发送时间            状态" << endl;
	char mID[5]; char sID[5]; char rID[5]; char c[201]; char t[17]; int sta;
	while(!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%d\n", mID, sID, rID, c, t, &sta);
		if(strcmp(rID,userID)==0)
		{
			message temp(mID, sID, rID, c, t, sta);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "**********************************************************" << endl;
}

void user::check_send_message()
{
	FILE* fp = fopen("message.txt", "r");
	cout << "**********************************************************" << endl;
	cout << "信息ID    发件人ID    收件人ID    发送时间            状态" << endl;
	char mID[5]; char sID[5]; char rID[5]; char c[201]; char t[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%d\n", mID, sID, rID, c, t, &sta);
		if (strcmp(sID, userID) == 0)
		{
			message temp(mID, sID, rID, c, t, sta);
			temp.print_();
		}
	}
	fclose(fp);
	cout << "**********************************************************" << endl;
}

void user::read_message()
{
	char target_mID[5];
	cout << "请输入您要阅读的信息的ID：";
	cin >> target_mID;
	vector<message> messages;
	int flag = 0;
	FILE* fp = fopen("message.txt", "r");
	char mID[5]; char sID[5]; char rID[5]; char c[201]; char t[17]; int sta;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s%s%d\n", mID, sID, rID, c, t, &sta);
		if (strcmp(mID, target_mID) == 0 && (strcmp(rID, userID) == 0 || strcmp(sID, userID) == 0))
		{
			message temp(mID, sID, rID, c, t, 1);
			messages.push_back(temp);
			temp.print_detail();
			flag = 1;
		}
		else
		{
			message temp(mID, sID, rID, c, t, sta);
			messages.push_back(temp);
		}
	}
	fclose(fp);
	if (flag == 0)
		cout << "未在您的信箱找到该信息，请重试" << endl;
	else
	{
		FILE* fp1 = fopen("message.txt", "w");
		for (int i = 0; i < messages.size(); i++)
			messages[i].write_back(fp1);
		fclose(fp1);
	}
}