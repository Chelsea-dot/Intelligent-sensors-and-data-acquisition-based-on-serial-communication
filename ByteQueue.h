#ifndef __BYTEQUEUE_H__
#define __BYTEQUEUE_H__
#include<stdlib.h>

class ByteQueue {
private:
	int head, rear, size;  //head指向第一个元素前的空位，rear指向队尾元素                                           //isfull = 1表示队满，isempty = 1表示队空
	char* buf;

public:
	ByteQueue();
	~ByteQueue();
	void open(int n);
	void close();
	bool isempty();
	bool isfull();
	int pushback(char ch);
	char popfront();
	int writeback(char* buf1, int len);
	char* readfront(char* buf2, int n);
};

ByteQueue::ByteQueue() {
	head = 0; rear = 0; size = 0;
	buf = NULL;
};

ByteQueue::~ByteQueue() {};

/*  给队列分配空间  */
void ByteQueue::open(int n) {
	buf = (char*)malloc(n*sizeof(char));
	size = n;
}

void ByteQueue::close() {
	free(buf);
}

bool ByteQueue::isempty(){
	if (head == rear)
		return 1;
	return 0;
}

bool ByteQueue::isfull() {
	if ( (rear+1)%size == head)
		return 1;
	return 0;
}

//push成功返回1，push失败返回0；并判断队是否已满
int ByteQueue::pushback(char ch) {
	rear = (rear + 1) % size;
	if (rear == head) {
		rear = (rear - 1 + size) % size;
		return 0;
	}
	buf[rear] = ch;
	return 1;
}

//pop成功返回被pop出来的值，pop失败返回0;并判断队是否已空
char ByteQueue::popfront() {
	if (isempty() == 1)
		return 0;
	head = (head + 1) % size;
	char front = buf[head];
	return front;
}

//一次性写入buf1中的多个字符；成功返回1，失败返回0
int ByteQueue::writeback(char* buf1, int len) {
	for (int i = 0; i < len; i++) {
		rear = (rear + 1) % size;
		if (rear == head) {
			rear = (rear - 1 + size) % size;
			return 0;
		}
		buf[rear] = buf1[i];
	}
	return 1;
}

/*  一次性读取n个字符  */
char* ByteQueue::readfront(char* buf2, int n) {
	for (int i = 0; i < n; i++) {
		if (isempty() == 1)
			return NULL;
		head = (head + 1) % size;
		buf2[i] = buf[head];
	}
	return buf2;
}

#endif