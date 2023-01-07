#pragma once
#include<iostream>
class user
{
private:
	char userID[5];
	char userName[11];
	char password[21];
	char tel[21];
	char address[41];
	double balance;
	int state;						// 1:active 0:inactive
public:
	user() {}		//默认构造函数
	user(char uID[5], char uName[11], char pw[21], char te[21], char addr[41], double bal, int sta);		//构造函数
	void buyer();		//买家功能入口
	void seller();		//买家功能入口
	//for user
	void add_my_commodity();		//（卖家）上架商品
	void delete_my_commodity();		//（卖家）下架商品
	void modify_my_commodity();		//（卖家）修改商品信息
	void check_my_commodity();		//（卖家）查看我的商品
	void browse_all_commodity();	//（买家）浏览所有商品
	void search_commodity();		//（买家）搜索商品
	void print_detail_of_commodity();		//查看商品详细信息
	void make_offer();					//（买家）出价竞拍
	void modify_my_offer();			//（买家）修改/取消出价
	void buyer_check_order();		//（买家）查看历史订单
	void seller_check_order();		//（卖家）查看历史订单
	void check_my_offer();			//（买家）查看历史报价
	void manage_my_info();		//信息管理功能入口
	void check_my_info();			//查看个人信息
	void modify_my_info();			//修改个人信息
	void charge();				//充值
	//for admin
	void ban();						//封禁
	void print_();					//打印信息

	int get_state();		//获取用户状态
	void write_back(FILE* fp);			//用户信息写回文件
	double get_balance();				//获取余额数目
	void change_balance(double change);				//改变余额
	char* get_ID();							//获取用户ID
	void message_box();				//信箱功能入口
	void send_message();			//发送信息
	void check_receive_message();		//查看收件箱
	void check_send_message();			//查看发件箱
	void read_message();				//阅读消息（详情）
};

void User();
void User_register();
