#ifndef FILELINK
#define FILELINK
#include "CharString.h"

//�ĵ��ڵ�
class FileNode{
public:
	int ID;//��ţ������ļ�����������ȷ��
	CharString content;//��������
	int times;//���ʳ��ֵĴ���
	FileNode* next;//��һ���ļ�

	FileNode() :times(0), next(nullptr) {}
	FileNode(int _ID,const CharString& _content) :ID(_ID),content(_content), times(0), next(nullptr) {}
};

//�ĵ�����
class FileLink {
public:
	FileNode* head, *tail;

	FileLink():head(nullptr),tail(nullptr){}
	void insert(FileNode* newnode);//����times�Ӵ�С����
	void traverse();
	bool searchFile(int ID, FileNode*& node);//����ĳ��ID���ļ������ҵ���nodeΪָ����ļ���ָ��
	bool empty() { return head == tail; }
};
#endif 