#include <string.h>
#include <iostream>
#include "hashtable.h"

using namespace std;

//表长取作比n大的最小的4M+3的素数
int nextPrime(int n) {
	int x = n;
	while (x % 4 != 3) x++;
	int flag;
	while (1) {
		flag = 0;
		for (int i = 2; i <= sqrt(x); ++i) {
			if (x%i == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			return x;
		}
		x+=4;
	}
}

//bkdr算法
int HashTable::_hash(char* key) {
	unsigned int seed = 131313;
	unsigned int hash = 0;
	while (*key)
	{
		hash = hash * seed + (*key++);
	}
	if (hash < 0) hash += _maxsize;
	return hash % _maxsize;

}

//查找字符串在哈希表中的位置
//若找到，返回所在的位置，found=true
//若没找到，返回发现不在时的位置，found=false
int HashTable::_find(char* key,bool& found) {
	
	int code = _hash(key);
	if (!occupied[code]) {
		found = false;
		return code;
	}
	else {//双平方探测
		int i = code;
		int j = 0;
		int flag = 1;
		while (occupied[i] && key!=_base[i]) {//建表时字符串内容和地址是一一对应的关系
			i = (code + flag*j*j) % _maxsize;
			if (i < 0) i += _maxsize;
			if (flag == -1) j++;
			flag = -flag;
		}
		found = occupied[i];
		return i;
	}
}

int HashTable::find(char* key, bool& found) {

	int code = _hash(key);
	if (!occupied[code]) {
		found = false;
		return code;
	}
	else {//双平方探测
		int i = code;
		int j = 0;
		int flag = 1;
		while (occupied[i] && strcmp(key,_base[i])) {//用户查表时应当比较字符串的内容而非地址
			i = (code + flag * j*j) % _maxsize;
			if (i < 0) i += _maxsize;
			if (flag == -1) j++;
			flag = -flag;
		}
		found = occupied[i];
		return i;
	}
}


int HashTable::insert(char* key) {
	if (_size+1 > 0.5*_maxsize) rehash();
	bool found = false;
	int index=_find(key, found);
	if (found) return -1;//如果已经存在，返回
	_base[index] = key;
	_size++;
	occupied[index] = true;
	return index;
}

//当装填因子大于0.5，再散列
void HashTable::rehash() {
	char** old = _base;
	int oldsize = _maxsize;
	_maxsize = nextPrime(_maxsize * 2);
	_base = new char*[_maxsize];
	bool* oldOccupied = occupied;
	occupied = new bool[_maxsize];
	for (int i = 0; i < _maxsize; ++i) occupied[i] = false;
	_size = 0;
	for (int i = 0; i < oldsize; ++i) {
		if (oldOccupied[i]) {
			insert(old[i]);
		}
	}
	delete old;
}

//打印哈希表中每个元素
void HashTable::printAll() {
	for (int i = 0; i < _maxsize; ++i) {
		if (occupied[i]) {
			cout << _base[i] << endl;
		}
	}
}

//析构
HashTable::~HashTable() {
	for (int i = 0; i < _maxsize; ++i) {
		if (occupied[i]) {
			delete[] _base[i];
		}
	}
	delete[] _base;
	delete[] occupied;
}