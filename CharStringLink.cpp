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

//�ڱ�β����
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

//����Ϊ��ͷ
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

//��ȥ���е���s��Ԫ��
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

//���ҵ�һ������s��Ԫ��
//����Ҳ���������NULL
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