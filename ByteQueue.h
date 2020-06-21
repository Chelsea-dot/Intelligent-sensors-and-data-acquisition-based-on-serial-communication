#ifndef __BYTEQUEUE_H__
#define __BYTEQUEUE_H__
#include<stdlib.h>

class ByteQueue {
private:
	int head, rear, size;  //headָ���һ��Ԫ��ǰ�Ŀ�λ��rearָ���βԪ��                                           //isfull = 1��ʾ������isempty = 1��ʾ�ӿ�
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

/*  �����з���ռ�  */
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

//push�ɹ�����1��pushʧ�ܷ���0�����ж϶��Ƿ�����
int ByteQueue::pushback(char ch) {
	rear = (rear + 1) % size;
	if (rear == head) {
		rear = (rear - 1 + size) % size;
		return 0;
	}
	buf[rear] = ch;
	return 1;
}

//pop�ɹ����ر�pop������ֵ��popʧ�ܷ���0;���ж϶��Ƿ��ѿ�
char ByteQueue::popfront() {
	if (isempty() == 1)
		return 0;
	head = (head + 1) % size;
	char front = buf[head];
	return front;
}

//һ����д��buf1�еĶ���ַ����ɹ�����1��ʧ�ܷ���0
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

/*  һ���Զ�ȡn���ַ�  */
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