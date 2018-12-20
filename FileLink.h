#ifndef FILELINK
#define FILELINK
#include "CharString.h"

//文档节点
class FileNode {
public:
	int ID;//编号，根据文件名最后的数字确定
	char* content;//单词内容
	int times;//单词出现的次数
	FileNode* next;//下一个文件

	FileNode() :times(0), next(nullptr) {}
	FileNode(int _ID, const char* _content) :ID(_ID), times(0), next(nullptr) {
		content = new char[strlen(_content) + 1];
		int i = 0;
		for (; _content[i] != '\0'; i++) content[i] = _content[i];
		content[i] = '\0';
	}
};

//文档链表
class FileLink {
public:
	FileNode* head, *tail;

	FileLink() :head(nullptr), tail(nullptr) {}
	void insert(FileNode* newnode);//按照times从大到小排序
	void traverse();
	bool searchFile(int ID, FileNode*& node);//查找某个ID的文件，若找到，node为指向该文件的指针
	bool empty() { return head == tail; }
};
#endif 