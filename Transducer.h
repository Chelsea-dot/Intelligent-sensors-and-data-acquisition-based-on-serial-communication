#ifndef __TRANSDUCER_H__
#define __TRANSDUCER_H__
#include<iostream>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h> 
#include <string>
using namespace std;

class Transducer {
private:
	int id, num;  
	char name[32];
	char currentvalue[32] = { 0 };
	string historyvalues;

public:
	Transducer(int id, const char* name);
	~Transducer();
	void init();
	char* data_Generation();
};

Transducer::Transducer(int id_send, const char* name_send) {
	id = id_send;
	strcpy_s(name, name_send);
	num = 0;
}

Transducer::~Transducer() {};

/*  初始化随机数  */
void Transducer::init() {
	srand((unsigned)time(NULL));
}

/*  产生数据，且对历史数据进行记录  */
char* Transducer::data_Generation() {
	if (strcmp(name, "DHT11") == 0) {
		for (int i = 0; i < 32; i++)
			currentvalue[i] = '0' + rand() % 2;
		historyvalues.append((const char*)currentvalue, 32);
		num += 32;
	}
	else if (strcmp(name, "MQ-2") == 0) {
		currentvalue[0] = '0' + rand() % 2;
		for (int i = 1; i < 4; i++)
			currentvalue[i] = '0' + rand() % 10;
		currentvalue[4] = '0' + rand() % 2;
		historyvalues.append((const char*)currentvalue, 4);
		num += 5;
	}
	return currentvalue;
}

#endif