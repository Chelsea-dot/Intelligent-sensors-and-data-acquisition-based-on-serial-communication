#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include"ByteQueue.h"
#include"NioService_workstation.h"
#include"trans.h"

using namespace std;
#pragma comment(lib,"ws2_32.lib")
# define BUFFER_SIZE  1024    //��������С

struct DHT11 {
	double TEMP, HUMI;
};

struct MQ2 {
	int XLEL;
	char TTLD;
};

int main() {
	NioService NioService;
	char  receBuf_init[BUFFER_SIZE], receBuf_read[BUFFER_SIZE], sendBuf_init[BUFFER_SIZE], sendBuf_read[BUFFER_SIZE];
	char continue_cmd[9] = { 'c','o','n','t','i','n','u','e' ,'\0' };

	/*  �Դ��������г�ʼ��  */
	while (true) {
		cout << "The command to be executed:";
		cin >> sendBuf_init;
		if (strcmp(sendBuf_init, "init") != 0) {
			cout << "Sensors haven't been initialized. Please initialize first!" << endl;
			continue;
		}
		break;
	}
	NioService.send(sendBuf_init);
	int last = NioService.recv(receBuf_init);
	if (last > 0) {
		receBuf_init[last] = '\0';
		if (strcmp(receBuf_init, "Sensors have been initialized.") == 0 ) {
			cout << "Sensors have been initialized." << endl;
		}
	}

	/*  ��ȡ������������  */
	while (true) {
		cout << "The command to be executed:";
		cin >> sendBuf_read;
		if (strcmp(sendBuf_read, "read") != 0) {
			cout << "Unrecognized command." << endl << "The commands you can enter are:" << endl << "read" << endl;
			continue;
		}
		break;
	}
	NioService.send(sendBuf_read);

	while (true) {
		ByteQueue DHT11_data;
		int last1 = NioService.recv(receBuf_read); //����������
		DHT11_data.open(33);
		DHT11_data.writeback(receBuf_read, 32);

		/*  �õ�������ʪ������  */
		DHT11 data;
		data.TEMP = trans(DHT11_data);
		data.HUMI = trans(DHT11_data);
		
		/*  �ж��յ��������Ƿ����� �¶ȷ�Χ��0~50 ʪ�ȷ�Χ��20%~95%  */
		if (data.TEMP >= 0 && data.TEMP <= 50 && data.HUMI >= 20 && data.HUMI <= 95) {
			cout << data.TEMP << " " << data.HUMI << endl;
			system("pause");
		}
		else
			cout << "error" << " " << "error" << endl;
		DHT11_data.close();

		int last2 = NioService.recv(receBuf_read); //����������
		MQ2 data2;
		data2.XLEL = 0; data2.TTLD = 0;
		if (last2 > 0) {
			receBuf_read[last] = '\0';
			for (int i = 0; i < 4; i++) 
				data2.XLEL += (receBuf_read[i]-'0') * pow(10, (3 - i));
			data2.TTLD = receBuf_read[4]-'0';
		}
		cout << "The smoke concentration index is  " ;
		if (data2.XLEL < 1024)
			cout << data2.XLEL << endl;
		else
			cout << "error" << endl;
		if (data2.TTLD == 1)
			cout << "The smoke is not thick." << endl;
		else
			cout << "The smoke is thick." << endl;

	}
	NioService.close();
	system("pause");
	return 0;
}