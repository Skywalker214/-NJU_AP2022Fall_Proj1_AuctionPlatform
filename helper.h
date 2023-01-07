#pragma once
#include<time.h>
int fuzzy_match(char a[], char b[]);        //模糊搜索
char* get_time();       //获取系统时间，转换为特定格式
void cal_money(char the_uID[5], double money);          //给指定用户结算交易额
void auction_settlement();          //拍卖机制