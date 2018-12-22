#include <iostream>
#include "CharStringLink.h"
using namespace std;

ostream& operator<<(ostream& out, const CharStringLink& csl) {
	if (!(csl.head)) {
		return out;
	}
	StringNode* p = csl.head;
	while (p) {
		out << p->str << endl;
		p = p->next;
	}
	return out;
}

//在表尾插入
void CharStringLink::add(CharString s) {
	StringNode* newnode = new StringNode(s);
	if (head == NULL) {
		head = newnode;
		tail = newnode;
	}
	else {
		tail->next = newnode;
		tail = newnode;
	}
	_size++;
}

//拷贝另一个链表
void CharStringLink::assign(CharStringLink& s) {
	StringNode* p = s.head;
	if (!p) return;
	head = new StringNode(p->str);
	tail = head;
	p = p->next;
	while (p) {
		StringNode* newnode = new StringNode(p->str);
		tail->next = newnode;
		tail = newnode;
		p = p->next;
	}
}

//将链表s连接到自己的后面，s保持不变
void CharStringLink::concat(CharStringLink& s) {
	if (head == NULL) {
		this->assign(s);
		return;
	}
	StringNode*p2 = s.head;
	while (p2) {
		StringNode* newnode = new StringNode(p2->str);
		tail->next = newnode;
		tail = newnode;
		p2 = p2->next;
	}
}

//插入为表头
void CharStringLink::insert(CharString s) {
	StringNode* newnode = new StringNode(s);
	if (head == NULL) {
		head = newnode;
		tail = newnode;
	}
	else {
		newnode->next = head;
		head = newnode;
	}
	_size++;
}

//除去所有等于s的元素
void CharStringLink::remove(CharString s) {
	StringNode* p = head,*prev=NULL;
	while (p) {
		if (p->str == s) {
			_size--;
			//prev p(s) p.next
			if (prev) {
				prev->next = p->next;
				delete p;
				p = prev->next;
			}
			else {
				//head(p)
				head = head->next;
				delete p;
				p = head;
			}
		}
		else {
			prev = p;
			p = p->next;
		}
	}
}

//查找第一个等于s的元素
//如果找不到，返回NULL
StringNode* CharStringLink::search(CharString s) {
	StringNode* p = head;
	while (p&&p->str!=s) {
		p = p->next;
	}
	//p=null or p.str=s
	return p;
}

CharStringLink::~CharStringLink() {
	StringNode* p;
	if (head) {
		while (head->next) {
			p = head->next;
			delete head;
			head = p;
		}
		delete head;
	}
}