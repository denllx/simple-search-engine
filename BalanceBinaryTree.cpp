#include "BalanceBinaryTree.h"

int max(int a1, int a2) {
	return a1 < a2 ? a2 : a1;
}

//�ڵ�ǰ���ʵ��ļ��б��в���IDΪID���ļ�
//�ҵ���ret=ָ����ļ���ָ��
//�Ҳ�����ret=NULL
bool WordNode::searchFile(int ID, FileNode*& ret) {
	return firstfile->searchFile(ID, ret);
}

//����rootΪ������������ֵΪs�Ľڵ�
//���ҵ���resultָ��ýڵ�
//���Ҳ�����resultָ�����·���ϵ����һ���ڵ�
bool BalanceBinaryTree::_search(WordNode* root, CharString& s, WordNode* father, WordNode*& result) {
	if (!root) {
		result = father;
		return false;//����ʧ��
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
		return false;//����ʧ��
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



//�����ҳɹ���resultָ��ֵΪs�Ľڵ�
//������ʧ�ܣ�result����·���ϵ����һ���ڵ�
bool BalanceBinaryTree::search(CharString& s, WordNode*& result) {
	return this->_search(this->root, s, nullptr, result);
}

bool BalanceBinaryTree::search(char* s, WordNode*& result) {
	return this->_search(this->root, s, nullptr, result);
}

//node����ɲ����������ĸ��ڵ�
//���Ѿ������У�ret=����Ϊ֮
//����������,ret=�����λ��
//�����ɹ�������true
bool BalanceBinaryTree::insert(WordNode*& node, WordNode*& ret, char* s) {
	bool inserted = false;
	if (!node) {
		node = new WordNode(s);//������1ƪ�����У��ܳ��ִ���Ϊ1
		ret = node;
		inserted = true;
		_size++;
	}
	else if (strcmp(s, node->content) < 0) {
		inserted = insert(node->left, ret, s);
		//��߸�
		if (_getHeight(node->left) - _getHeight(node->right) > 1) {
			if (strcmp(s, node->left->content) < 0) node = _ll(node);//����
			else node = _lr(node);//����
		}
	}
	else if (strcmp(s, node->content) > 0) {//�ұ߸�
		inserted = insert(node->right, ret, s);
		if (_getHeight(node->right) - _getHeight(node->left) > 1) {
			if (strcmp(s, node->right->content) > 0) node = _rr(node);//����
			else node = _rl(node);//����
		}
	}
	//��Ȼ���Ѿ������У�ʲôҲ����
	else {
		ret = node;
		inserted = false;
	}
	node->height = max(_getHeight(node->right), _getHeight(node->left)) + 1;
	return inserted;
}

//nodeΪɾ���������ĸ��ڵ�
//�����Ƿ�ɾ���ɹ�
bool BalanceBinaryTree::remove(WordNode*& node, char* s) {
	if (!node) return false;//��ɾ���ڵ㲻������
	else if (strcmp(s, node->content) == 0) {//�ҵ���Ҫɾ���Ľڵ�
		if (node->left && node->right) {//�����������ǿ�
			//�ڸ��ߵ������Ͻ���ɾ������

			//���������ߣ�ɾ���������������ӣ���ֵ���ڵ�
			if (_getHeight(node->left) > _getHeight(node->right)) {
				strcpy(node->content, _findmax(node->left)->content);//��ֵ
				remove(node->left, node->content);
			}

			//���������ߣ�ɾ������������С���ӣ���ֵ���ڵ�
			else {
				strcpy(node->content, _findmin(node->right)->content);//��ֵ
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
		//�ݹ�ɾ����������
		remove(node->left, s);
		//�ж��Ƿ���Ҫ��ת
		if (_getHeight(node->right) - _getHeight(node->left) > 1) {//��Ҫ��ת
			if (_getHeight(node->right->left) > _getHeight(node->right->right)) {
				//�ұߵ���������
				node = _rl(node);
			}
			else {
				//�ұߵ���������
				node = _rr(node);
			}
		}
		else {//����Ҫ��ת
			node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
		}
	}
	else {
		//�ݹ�ɾ��������
		remove(node->right, s);
		//�Ƿ���Ҫ��ת
		if (_getHeight(node->left) - _getHeight(node->right) > 1) {//��߸�
			//��ߵ��ұ߸�
			if (_getHeight(node->left->right) > _getHeight(node->left->left)) {
				node = _lr(node);
			}
			else {//��ߵ���߸�
				node = _ll(node);
			}
		}
		else {//������ת
			node->height = 1 + max(_getHeight(node->left), _getHeight(node->right));
		}
	}
	return true;
}

//����
WordNode* BalanceBinaryTree::_ll(WordNode* node) {
	WordNode* q = node->left;
	node->left = q->right;
	q->right = node;
	//node = q;

	//�����߶�
	node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
	q->height = max(_getHeight(q->left), _getHeight(q->right)) + 1;
	return q;
}

//����
WordNode* BalanceBinaryTree::_rr(WordNode* node) {
	WordNode* q = node->right;
	node->right = q->left;
	q->left = node;
	//node = q;
	//�����߶�
	node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
	q->height = max(_getHeight(q->left), _getHeight(q->right)) + 1;
	return q;
}

//����
WordNode* BalanceBinaryTree::_lr(WordNode* node) {
	//�ȶ�node����ڵ����RR
	//�ٶԸ��ڵ����LL
	node->left = _rr(node->left);
	return this->_ll(node);
}

//����
WordNode* BalanceBinaryTree::_rl(WordNode* node) {
	//�ȶ�node���Ҷ��ӽ���LL
	//�ٶԸ��ڵ����RR
	node->right = _ll(node->right);
	return this->_rr(node);
}

int BalanceBinaryTree::_getHeight(WordNode* node) {
	if (!node) return -1;
	else return node->height;
}

//��nodeΪ�������������ڵ�
WordNode* BalanceBinaryTree::_findmax(WordNode* node) {
	if (!node) return nullptr;//����
	if (!(node->right)) return node;//�м�ڵ����
	return _findmax(node->right);//�����������ڵ�
}

//��nodeΪ������������С�ڵ�
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
		cout << node->content << " ��" << node->articles << "ƪ�����г��ֹ�" << node->times << "��" << endl;
		cout << "�����⼸ƪ�����г��ֹ���" << endl;
		FileNode* p = node->firstfile->head;
		while (p) {
			cout << "(" << p->ID << "," << p->times << ") ";
			p = p->next;
		}
		cout << endl;
	}
}

//���ĵ��������ʳ��ִ����Ӷൽ�ٿ���
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
	//���ҵ����ҵ�������
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

