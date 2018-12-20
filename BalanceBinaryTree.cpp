#include "BalanceBinaryTree.h"

int max(int a1, int a2) {
	return a1 < a2 ? a2 : a1;
}

//在当前单词的文件列表中查找ID为ID的文件
//找到：ret=指向该文件的指针
//找不到：ret=NULL
bool WordNode::searchFile(int ID, FileNode*& ret) {
	return firstfile->searchFile(ID, ret);
}

//在以root为根的子树中找值为s的节点
//若找到，result指向该节点
//若找不到，result指向遍历路径上的最后一个节点
bool BalanceBinaryTree::_search(WordNode* root, CharString& s, WordNode* father, WordNode*& result) {
	if (!root) {
		result = father;
		return false;//查找失败
	}
	else if (s == root->content) {
		result = root;
		return true;
	}
	else if (s < root->content) {
		return _search(root->left, s, root, result);
	}
	else {
		return _search(root->right, s, root, result);
	}
}

bool BalanceBinaryTree::_search(WordNode* root, char* s, WordNode* father, WordNode*& result) {
	if (!root) {
		result = father;
		return false;//查找失败
	}
	else if (root->content == s) {
		result = root;
		return true;
	}
	else if (root->content > s) {
		return _search(root->left, s, root, result);
	}
	else {
		return _search(root->right, s, root, result);
	}
}



//若查找成功，result指向值为s的节点
//若查找失败，result查找路径上的最后一个节点
bool BalanceBinaryTree::search(CharString& s, WordNode*& result) {
	return this->_search(this->root, s, nullptr, result);
}

bool BalanceBinaryTree::search(char* s, WordNode*& result) {
	return this->_search(this->root, s, nullptr, result);
}

//node是完成插入后的子树的根节点
//若已经在树中，ret=所在为之
//若不在树中,ret=插入的位置
//如插入成功，返回true
bool BalanceBinaryTree::insert(WordNode*& node, WordNode*& ret, char* s) {
	bool inserted = false;
	if (!node) {
		node = new WordNode(s);//出现在1篇文章中，总出现次数为1
		ret = node;
		inserted = true;
		_size++;
	}
	else if (strcmp(s, node->content) < 0) {
		inserted = insert(node->left, ret, s);
		//左边高
		if (_getHeight(node->left) - _getHeight(node->right) > 1) {
			if (strcmp(s, node->left->content) < 0) node = _ll(node);//左左
			else node = _lr(node);//左右
		}
	}
	else if (strcmp(s, node->content) > 0) {//右边高
		inserted = insert(node->right, ret, s);
		if (_getHeight(node->right) - _getHeight(node->left) > 1) {
			if (strcmp(s, node->right->content) > 0) node = _rr(node);//右右
			else node = _rl(node);//右左
		}
	}
	//不然，已经在树中，什么也不做
	else {
		ret = node;
		inserted = false;
	}
	node->height = max(_getHeight(node->right), _getHeight(node->left)) + 1;
	return inserted;
}

//node为删除后子树的根节点
//返回是否删除成功
bool BalanceBinaryTree::remove(WordNode*& node, char* s) {
	if (!node) return false;//待删除节点不在树中
	else if (strcmp(s, node->content) == 0) {//找到了要删除的节点
		if (node->left && node->right) {//左右子树均非空
			//在更高的子树上进行删除操作

			//左子树更高，删除左子树中最大儿子，赋值根节点
			if (_getHeight(node->left) > _getHeight(node->right)) {
				strcpy(node->content, _findmax(node->left)->content);//赋值
				remove(node->left, node->content);
			}

			//右子树更高，删除右子树中最小儿子，赋值根节点
			else {
				strcpy(node->content, _findmin(node->right)->content);//赋值
				remove(node->right, node->content);
			}
		}
		else {
			WordNode* tmp = node;
			node = node->left ? node->left : node->right;
			delete tmp;
		}
	}
	else if (s < node->content) {
		//递归删除左子树上
		remove(node->left, s);
		//判断是否需要旋转
		if (_getHeight(node->right) - _getHeight(node->left) > 1) {//需要旋转
			if (_getHeight(node->right->left) > _getHeight(node->right->right)) {
				//右边的左子树高
				node = _rl(node);
			}
			else {
				//右边的右子树高
				node = _rr(node);
			}
		}
		else {//不需要旋转
			node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
		}
	}
	else {
		//递归删除右子树
		remove(node->right, s);
		//是否需要旋转
		if (_getHeight(node->left) - _getHeight(node->right) > 1) {//左边高
			//左边的右边高
			if (_getHeight(node->left->right) > _getHeight(node->left->left)) {
				node = _lr(node);
			}
			else {//左边的左边高
				node = _ll(node);
			}
		}
		else {//不用旋转
			node->height = 1 + max(_getHeight(node->left), _getHeight(node->right));
		}
	}
	return true;
}

//左左
WordNode* BalanceBinaryTree::_ll(WordNode* node) {
	WordNode* q = node->left;
	node->left = q->right;
	q->right = node;
	//node = q;

	//调整高度
	node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
	q->height = max(_getHeight(q->left), _getHeight(q->right)) + 1;
	return q;
}

//右右
WordNode* BalanceBinaryTree::_rr(WordNode* node) {
	WordNode* q = node->right;
	node->right = q->left;
	q->left = node;
	//node = q;
	//调整高度
	node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
	q->height = max(_getHeight(q->left), _getHeight(q->right)) + 1;
	return q;
}

//左右
WordNode* BalanceBinaryTree::_lr(WordNode* node) {
	//先对node的左节点进行RR
	//再对根节点进行LL
	node->left = _rr(node->left);
	return this->_ll(node);
}

//右左
WordNode* BalanceBinaryTree::_rl(WordNode* node) {
	//先对node的右儿子进行LL
	//再对根节点进行RR
	node->right = _ll(node->right);
	return this->_rr(node);
}

int BalanceBinaryTree::_getHeight(WordNode* node) {
	if (!node) return -1;
	else return node->height;
}

//以node为根的子树的最大节点
WordNode* BalanceBinaryTree::_findmax(WordNode* node) {
	if (!node) return nullptr;//空树
	if (!(node->right)) return node;//中间节点最大
	return _findmax(node->right);//右子树中最大节点
}

//以node为根的子树的最小节点
WordNode* BalanceBinaryTree::_findmin(WordNode* node) {
	if (!node) return nullptr;
	if (!(node->left)) return node;
	return _findmin(node->left);
}

void BalanceBinaryTree::inorderTraversal(WordNode* node, void visit(WordNode*)) {
	if (node) {
		inorderTraversal(node->left, visit);
		visit(node);
		inorderTraversal(node->right, visit);
	}
}

void printNode(WordNode* node) {
	if (node->articles > 1) {
		cout << node->content << " 在" << node->articles << "篇文章中出现过" << node->times << "次" << endl;
		cout << "共在这几篇文章中出现过：" << endl;
		FileNode* p = node->firstfile->head;
		while (p) {
			cout << "(" << p->ID << "," << p->times << ") ";
			p = p->next;
		}
		cout << endl;
	}
}

//将文档链表按单词出现次数从多到少快排
void sortNodeFile(WordNode* node) {
	if (node->articles <= 1) return;
	if (node->firstfile->head->times == 1 && node->firstfile->tail->times == 2) {
		cout << "";
	}
	int len = node->times;
	FileLink* links = new FileLink[len + 1];
	FileNode* p = node->firstfile->head;
	while (p) {
		FileNode* tmp = p->next;
		int idx = p->times;
		links[idx].insert(p);
		p = tmp;
	}
	//从右到左找到最大次数
	int i = len, j = i - 1;
	while (i >= 0 && links[i].empty()) i--;
	if (i >= 0) {
		node->firstfile->head = links[i].head;
		j = i - 1;
		while (1) {
			if (i <= 0) break;
			while (j >= 0 && links[j].empty()) j--;
			if (j < 0) break;
			links[i].tail->next = links[j].head;
			i = j;
		}
	}
}

