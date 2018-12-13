#include <string.h>
#include <iostream>
#include "hashtable.h"

using namespace std;

//��ȡ����n�����С��4M+3������
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

//bkdr�㷨
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

//�����ַ����ڹ�ϣ���е�λ��
//���ҵ����������ڵ�λ�ã�found=true
//��û�ҵ������ط��ֲ���ʱ��λ�ã�found=false
int HashTable::_find(char* key,bool& found) {
	
	int code = _hash(key);
	if (!occupied[code]) {
		found = false;
		return code;
	}
	else {//˫ƽ��̽��
		int i = code;
		int j = 0;
		int flag = 1;
		while (occupied[i] && key!=_base[i]) {//����ʱ�ַ������ݺ͵�ַ��һһ��Ӧ�Ĺ�ϵ
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
	else {//˫ƽ��̽��
		int i = code;
		int j = 0;
		int flag = 1;
		while (occupied[i] && strcmp(key,_base[i])) {//�û����ʱӦ���Ƚ��ַ��������ݶ��ǵ�ַ
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
	if (found) return -1;//����Ѿ����ڣ�����
	_base[index] = key;
	_size++;
	occupied[index] = true;
	return index;
}

//��װ�����Ӵ���0.5����ɢ��
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

//��ӡ��ϣ����ÿ��Ԫ��
void HashTable::printAll() {
	for (int i = 0; i < _maxsize; ++i) {
		if (occupied[i]) {
			cout << _base[i] << endl;
		}
	}
}

//����
HashTable::~HashTable() {
	for (int i = 0; i < _maxsize; ++i) {
		if (occupied[i]) {
			delete[] _base[i];
		}
	}
	delete[] _base;
	delete[] occupied;
}