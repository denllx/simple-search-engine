#ifndef FILELINK
#define FILELINK
#include "CharString.h"

//文档节点
class FileNode{
public:
	int ID;//编号，根据文件名最后的数字确定
	CharString content;//单词内容
	int times;//单词出现的次数
	FileNode* next;//下一个文件

	FileNode() :times(0), next(nullptr) {}
	FileNode(int _ID,const CharString& _content) :ID(_ID),content(_content), times(0), next(nullptr) {}
};

//文档链表
class FileLink {
public:
	FileNode* head, *tail;

	FileLink():head(nullptr),tail(nullptr){}
	void insert(FileNode* newnode);//按照times从大到小排序
	void traverse();
	bool searchFile(int ID, FileNode*& node);//查找某个ID的文件，若找到，node为指向该文件的指针
	bool empty() { return head == tail; }
};
#endif 