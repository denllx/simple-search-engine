#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include <iostream>
#include "CharString.h"
using namespace std;

class StringNode {
public:
	CharString str;
	StringNode* next;
	StringNode(CharString s):str(s),next(NULL){}
	StringNode(){}
};

class CharStringLink {
	int _size;
public:
	StringNode* head, *tail;
	~CharStringLink();
	CharStringLink():head(NULL),tail(NULL),_size(0){}
	void add(CharString s);//在表尾插入
	void insert(CharString s);//在表头插入
	void remove(CharString s);
	bool empty() { return (head == NULL); }
	StringNode* search(CharString s);
	friend ostream& operator<<(ostream& out, const CharStringLink& c);
	int size() { return _size; }
};

#endif