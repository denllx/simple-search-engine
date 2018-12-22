#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <math.h>

#define _USE_MATH_DEFINES

#define MAXSIZE 560000

int nextPrime(int n);//返回比n大的最小素数

class HashTable {
	int _size;//表中已有地址个数
	int _maxsize;//表的容量
	char** _base;//地址列表
	bool* occupied;//哈希表中每个单元是否已被占据
	int _hash(char* key);//根据关键码返回地址
	int _find(char* key, bool& found);//面向建表者

public:
	HashTable() {//默认设置
		/*_size = 0;
		_maxsize = nextPrime(MAXSIZE);
		_base = new char*[_maxsize];
		occupied = new bool[_maxsize];
		for (int i = 0; i < _maxsize; ++i) occupied[i] = false;*/
		_size = 0;
		_maxsize = 0;
		_base = NULL;
		occupied = NULL;
	}
	HashTable(int s) {
		_size = 0;
		_maxsize = nextPrime(s);
		_base = new char*[_maxsize];
		occupied = new bool[_maxsize];
		for (int i = 0; i < _maxsize; ++i) occupied[i] = false;
	}
	void setcapacity(int s) {
		_size = 0;
		_maxsize = nextPrime(s);
		if (_base) delete _base;
		_base = new char*[_maxsize];
		if (occupied) delete occupied;
		occupied = new bool[_maxsize];
		for (int i = 0; i < _maxsize; i++) occupied[i] = false;
	}
	~HashTable();
	int size() { return _size; }
	int capacity() { return _maxsize; }
	
	int find(char* key,bool& found);//面向用户
	int insert(char* key);//返回插入的位置
	void rehash();
	void printAll();
};

#endif