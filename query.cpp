#include <algorithm>
#include <iostream>
#include <sstream>
#include "query.h"
#include "getfile.h"
#include "CharStringLink.h"

bool cmpByValueReverse(const pair<int, int>& p1, const pair<int, int>& p2) {
	return p1.second > p2.second;
}

//TODO��������йؼ���
//��ȡ�����һ�йؼ��ʣ��������ַ���������
void getInput(char* input,CharStringLink& words) {
	
	char word[100];
	stringstream ss(input);
	while (ss >> word) {
		CharString cs(word);
		words.add(cs);
	}
}	

//TODO��������в�ѯ
//�����β�ѯ�Ľ��������result1.txt
void outputQueryResult(vector<vector<pair<int, int>>>& rets) {
	string outputdir;
	getSubDir(outputdir, "\\");
	outputdir += "result1.txt";

	ofstream fout(outputdir.c_str());
	for (auto ret : rets) {
		for (auto it : ret) {
			fout << "(" << it.first << "," << it.second << ")" << " ";
		}
		fout << endl;
	}
	fout.close();
}

//һ��numarticles=780
vector<pair<int, int>> query(BalanceBinaryTree* tree,CharStringLink& words) {
	map<int, int> id2times;//keyΪ��ҳ��ID��valueΪ���йؼ��ֳ��ֵ��ܴ���
	StringNode* p = words.head;
	while (p) {
		WordNode* node = NULL;
		bool found = tree->search(p->str, node);
		if (found == false) {
			p = p->next;
			continue;//���ʲ��������г���
		}
		//������������������ҳ��ID�ĵ��ʳ�����+1
		FileNode* p1 = node->firstfile->head;
		while (p1) {
			id2times[p1->ID]+=p1->times;//����node���ĵ�p1�г��ֵĴ���
			p1 = p1->next;
		}
		p = p->next;
	}
	//������Ӵ�С����
	vector<pair<int, int>> id2times_vec(id2times.begin(), id2times.end());
	sort(id2times_vec.begin(), id2times_vec.end(), cmpByValueReverse);
	//ȡ��0��ǰ5���������5��ȡȫ��
	int len = id2times_vec.size() > 5 ? 5 : id2times_vec.size();
	vector<pair<int, int>> ret(id2times_vec.begin(), id2times_vec.begin() + len);
	return ret;
}

//ÿ����query1.txt��һ��
//���зִʲ���
//ѡ�������������
//����vector
//���������result
void runQuery(BalanceBinaryTree* tree) {
	string inputdir;
	getSubDir(inputdir, "\\");
	inputdir += "query1.txt";

	ifstream fin(inputdir.c_str());
	char s[500];//��ѯ���Ȳ��ᳬ��500�ɡ�����
	vector<vector<pair<int, int>>> rets;//��β�ѯ�Ľ����ÿ�α���Ϊһ��vector<pair>
	while (fin.getline(s,500)) {
		CharStringLink words;
		getInput(s, words);//��s���տո�ֿ��������ַ�������
		StringNode* node = words.head;
		while (node) {
			cout << node->str << endl;
			node = node->next;
		}
		vector<pair<int, int>> ret = query(tree, words);//����һ�β�ѯ�Ľ��
		rets.push_back(ret);
	}
	fin.close();
	//�����н��������ļ�
	outputQueryResult(rets);
}