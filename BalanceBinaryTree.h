#ifndef BALANCEBINARYTREE_H
#define BALANCEBINARYTREE_H

#include "CharString.h"
#include "FileLink.h"

//一个单词节点
class WordNode {
public:
	int articles;//在多少篇文章中出现过
	int times;//总共出现次数
	char* content;//单词内容
	WordNode* left, *right;
	int height;//当前节点的高度，空节点为-1，叶子节点为0
	FileLink* firstfile;//指向第一个文档节点的指针（也是出现次数最多的）

	WordNode(char* s) :firstfile(new FileLink), height(0), times(0), articles(0), left(nullptr), right(nullptr) {
		content = new char[strlen(s) + 1];
		int i = 0;
		for (; s[i] != '\0'; i++) content[i] = s[i];
		content[i] = '\0';
	}
	void insertFile(FileNode* filenode) { firstfile->insert(filenode); }
	bool searchFile(int ID, FileNode*& file);//查找某ID的文件是否存在文档列表中，若存在，返回指向该文档的指针
};

void printNode(WordNode* node);
void sortNodeFile(WordNode* node);//将文档链表排序

class BalanceBinaryTree {

public:
	WordNode* root;//根节点
	BalanceBinaryTree() :root(nullptr), _size(0) {}
	BalanceBinaryTree(WordNode* r) :root(r), _size(0) {}

	bool search(CharString& s, WordNode*& result);
	bool search(char* s, WordNode*& result);
	bool insert(WordNode*& node, WordNode*& ret, char* s);
	void inorderTraversal(WordNode* node, void visit(WordNode*));//以node为根中序遍历
	bool remove(WordNode*& node, char* s);//删除值为s的节点，返回删除后子树的根节点node
	int size() { return _size; }

private:
	//在以root为根的子树中找值为s的节点
	//若找到，result指向该节点
	//若找不到，result指向遍历路径上的最后一个节点
	int _size;//节点总数

	bool _search(WordNode* root, CharString& s, WordNode* father, WordNode*& result);
	bool _search(WordNode* root, char* s, WordNode* father, WordNode*& result);
	int _getHeight(WordNode* node);
	WordNode* _ll(WordNode* node);//左左单旋转
	WordNode* _rr(WordNode* node);//右右单选转
	WordNode* _lr(WordNode* node);//左右双旋转
	WordNode* _rl(WordNode* node);//右左双旋转
	WordNode* _findmax(WordNode* node);//以node为根节点的子树中的最大节点
	WordNode* _findmin(WordNode* node);//以node为根节点的子树中的最小节点
};

#endif 