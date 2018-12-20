#ifndef FILELINK
#define FILELINK
#include "CharString.h"

//�ĵ��ڵ�
class FileNode {
public:
	int ID;//��ţ������ļ�����������ȷ��
	char* content;//��������
	int times;//���ʳ��ֵĴ���
	FileNode* next;//��һ���ļ�

	FileNode() :times(0), next(nullptr) {}
	FileNode(int _ID, const char* _content) :ID(_ID), times(0), next(nullptr) {
		content = new char[strlen(_content) + 1];
		int i = 0;
		for (; _content[i] != '\0'; i++) content[i] = _content[i];
		content[i] = '\0';
	}
};

//�ĵ�����
class FileLink {
public:
	FileNode* head, *tail;

	FileLink() :head(nullptr), tail(nullptr) {}
	void insert(FileNode* newnode);//����times�Ӵ�С����
	void traverse();
	bool searchFile(int ID, FileNode*& node);//����ĳ��ID���ļ������ҵ���nodeΪָ����ļ���ָ��
	bool empty() { return head == tail; }
};
#endif 