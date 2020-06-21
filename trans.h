#ifndef __TRANS_H__
#define __TRANS_H__
#include<iostream>
#include"ByteQueue.h"
using namespace std;

/*  DHT11���͵��Ƕ����Ƶ�����:8λ�¶�С��+8λ�¶�����+8λʪ��С��+8λʪ���������ú������ڰ��յ��Ķ���������ת����10����  */
double trans(ByteQueue& DHT11_data) {
	int INT = 0;
	double DEC = 0, ans;
	for (int i = 0; i < 8; i++) {
		int bit = DHT11_data.popfront();
		bit = bit - '0';
		//cout << "bit:" << bit<<endl;
		DEC = DEC + bit * pow(2, i);
	}
	for (int i = 0; i < 8; i++) {
		int bit = DHT11_data.popfront();
		bit = bit - '0';
		//cout << "bit:" << bit << endl;
		INT = INT + (int)bit * pow(2, i);
	}
	if (DEC < 10)
		DEC = DEC * 0.1;
	else if (DEC < 100)
		DEC = DEC * 0.01;
	else
		DEC = DEC * 0.001;
	ans = (double)INT + DEC;
	return ans;
}
#endif