#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include <stdlib.h> 
#include <time.h>  
#include"Transducer.h"
#include"NioService_sensor.h"
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE 1024
#define BUFFER_SIZE2 1024

int main() {
	char cmd[BUFFER_SIZE];
	NioService NioService;

	Transducer DHT11(1, "DHT11");
	Transducer MQ_2(2, "MQ-2");

	while (true) {
		int last1 = NioService.recv(cmd);
		if (last1 > 0) {
			cmd[last1] = '\0';
			if (strcmp(cmd, "init") == 0) {   //ÏìÓ¦initÃüÁî
				DHT11.init(); MQ_2.init();
				char ans[] = "Sensors have been initialized.";
				NioService.send(ans);
			}
			else if (strcmp(cmd, "read") == 0) {  //ÏìÓ¦readÃüÁî
				while (true) {
					char* send_data1 = DHT11.data_Generation();
					NioService.send(send_data1);
					Sleep(20);
					char* send_data2 = MQ_2.data_Generation();
					NioService.send(send_data2);
					Sleep(20);
				}
			}
		}
	}
	NioService.close();
	system("pause");
	return 0;
}