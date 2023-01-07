#pragma once
class admin
{
private:
	const char name[6] = "admin";
	const char password[7] = "123456";
public:
	void check_all_commodity();		//查看所有商品
	void search_commodity();		//查找商品
	void delete_commodity();		//下架商品
	void check_all_offer();			//查看报价
	void check_all_order();			//查看订单
	void check_all_user();			//查看用户
	void ban_user();				//封禁用户
};

void Admin();
