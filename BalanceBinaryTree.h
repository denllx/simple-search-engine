#ifndef BALANCEBINARYTREE_H
#define BALANCEBINARYTREE_H

#include "CharString.h"
#include "FileLink.h"

//һ�����ʽڵ�
class WordNode {
public:
	int articles;//�ڶ���ƪ�����г��ֹ�
	int times;//�ܹ����ִ���
	char* content;//��������
	WordNode* left, *right;
	int height;//��ǰ�ڵ�ĸ߶ȣ��սڵ�Ϊ-1��Ҷ�ӽڵ�Ϊ0
	FileLink* firstfile;//ָ���һ���ĵ��ڵ��ָ�루Ҳ�ǳ��ִ������ģ�

	WordNode(char* s) :firstfile(new FileLink), height(0), times(0), articles(0), left(nullptr), right(nullptr) {
		content = new char[strlen(s) + 1];
		int i = 0;
		for (; s[i] != '\0'; i++) content[i] = s[i];
		content[i] = '\0';
	}
	void insertFile(FileNode* filenode) { firstfile->insert(filenode); }
	bool searchFile(int ID, FileNode*& file);//����ĳID���ļ��Ƿ�����ĵ��б��У������ڣ�����ָ����ĵ���ָ��
};

void printNode(WordNode* node);
void sortNodeFile(WordNode* node);//���ĵ���������

class BalanceBinaryTree {

public:
	WordNode* root;//���ڵ�
	BalanceBinaryTree() :root(nullptr), _size(0) {}
	BalanceBinaryTree(WordNode* r) :root(r), _size(0) {}

	bool search(CharString& s, WordNode*& result);
	bool search(char* s, WordNode*& result);
	bool insert(WordNode*& node, WordNode*& ret, char* s);
	void inorderTraversal(WordNode* node, void visit(WordNode*));//��nodeΪ���������
	bool remove(WordNode*& node, char* s);//ɾ��ֵΪs�Ľڵ㣬����ɾ���������ĸ��ڵ�node
	int size() { return _size; }

private:
	//����rootΪ������������ֵΪs�Ľڵ�
	//���ҵ���resultָ��ýڵ�
	//���Ҳ�����resultָ�����·���ϵ����һ���ڵ�
	int _size;//�ڵ�����

	bool _search(WordNode* root, CharString& s, WordNode* father, WordNode*& result);
	bool _search(WordNode* root, char* s, WordNode* father, WordNode*& result);
	int _getHeight(WordNode* node);
	WordNode* _ll(WordNode* node);//������ת
	WordNode* _rr(WordNode* node);//���ҵ�ѡת
	WordNode* _lr(WordNode* node);//����˫��ת
	WordNode* _rl(WordNode* node);//����˫��ת
	WordNode* _findmax(WordNode* node);//��nodeΪ���ڵ�������е����ڵ�
	WordNode* _findmin(WordNode* node);//��nodeΪ���ڵ�������е���С�ڵ�
};

#endif 