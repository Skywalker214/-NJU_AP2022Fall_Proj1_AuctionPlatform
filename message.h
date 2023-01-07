#pragma once
#include<iostream>
class message
{
private:
	char megID[5];
	char senderID[5];
	char receiverID[5];
	char content[201];
	char time[17];
	int state;	//0:未读 1:已读
public:
	message(char mID[5], char sID[5], char rID[5], char c[201], char t[17], int sta);
	void write_back(FILE* fp);		//写回文件
	void print_();		//打印消息（简略）
	void print_detail();		//打印信息（详情）
};
