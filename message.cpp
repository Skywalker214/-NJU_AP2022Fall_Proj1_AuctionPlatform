#define _CRT_SECURE_NO_WARNINGS
#include "admin.h"
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

message::message(char mID[5], char sID[5], char rID[5], char c[201], char t[17], int sta)
{
	strcpy(megID, mID);
	strcpy(senderID, sID);
	strcpy(receiverID, rID);
	strcpy(content, c);
	strcpy(time, t);
	state = sta;
}

void message::write_back(FILE* fp)
{
	fprintf(fp, "%s %s %s %s %s %d\n", megID, senderID, receiverID, content, time, state);
}

void message::print_()
{
	printf("%-10s%-12s%-12s%-20s", megID, senderID, receiverID, time);
	//printf("%-12s%-15s%-15s%-24s", megID, senderID, receiverID, time);
	if (state)
		printf("%s\n", "已读");
	else
		printf("%s\n", "未读");
}

void message::print_detail()
{
	cout << "发件人ID：" <<senderID << endl;
	cout << "收件人ID：" << receiverID << endl;
	cout << "发送时间：" << time << endl;
	cout << "信件内容：" << content << endl;
}