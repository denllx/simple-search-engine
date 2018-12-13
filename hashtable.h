#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <math.h>

#define _USE_MATH_DEFINES

#define MAXSIZE 560000

int nextPrime(int n);//���ر�n�����С����

class HashTable {
	int _size;//�������е�ַ����
	int _maxsize;//�������
	char** _base;//��ַ�б�
	bool* occupied;//��ϣ����ÿ����Ԫ�Ƿ��ѱ�ռ��
	int _hash(char* key);//���ݹؼ��뷵�ص�ַ
	int _find(char* key, bool& found);//���򽨱���

public:
	HashTable() {//Ĭ������
		_size = 0;
		_maxsize = nextPrime(MAXSIZE);
		_base = new char*[_maxsize];
		occupied = new bool[_maxsize];
		for (int i = 0; i < _maxsize; ++i) occupied[i] = false;
	}
	HashTable(int s) {
		_size = 0;
		_maxsize = nextPrime(s);
		_base = new char*[_maxsize];
		occupied = new bool[_maxsize];
		for (int i = 0; i < _maxsize; ++i) occupied[i] = false;
	}
	~HashTable();
	int size() { return _size; }
	int capacity() { return _maxsize; }
	
	int find(char* key,bool& found);//�����û�
	int insert(char* key);//���ز����λ��
	void rehash();
	void printAll();
};

#endif