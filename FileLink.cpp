#include "FileLink.h"

//�ĵ������в����ĵ��ڵ�
void FileLink::insert(FileNode* newnode) {
	if (!head) {
		head = newnode;
		tail = newnode;
	}
	else {
		tail->next = newnode;
		tail = newnode;
		/*FileNode* p = head,*q=nullptr;
		while (p&&p->times > newnode->times) {
			q = p;
			p = p->next;
		}
		//q>newnode>p
		//1.p=NULL
		if (!p) {//newnode.times��С
			tail->next = newnode;
			tail = newnode;
		}
		else {
			//p.content>=newnode  (q,newnode,p)
			if (q) {
				newnode->next = p;
				q->next = newnode;
			}
			//newnode.times���,q=null
			else {
				newnode->next = head;
				head = newnode;
			}
		}*/
	}
}

void FileLink::traverse() {
	FileNode* p = head;
	while (p) {
		cout << p->times << endl;
		p = p->next;
	}
}

bool FileLink::searchFile(int ID, FileNode*& node) {
	FileNode* p = head;
	while (p) {
		if (p->ID == ID) {
			node = p;
			return true;
		}
		p = p->next;
	}
	node = NULL;
	return false;
}
