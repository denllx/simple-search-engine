#include <algorithm>
#include <iostream>
#include <sstream>
#include "query.h"
#include "getfile.h"
#include "CharStringLink.h"
#include "dividewords.h"

bool cmpByValueReverse(const pair<int, int>& p1, const pair<int, int>& p2) {
	return p1.second > p2.second;
}

//��ȡ�����һ�йؼ��ʣ��ִʣ��������ַ���������
void getInput(char* input,CharStringLink& words,HashTable& dic,HashTable& stop) {
	string word;
	stringstream ss(input);
	while (ss >> word) {
		CharString cs(word.c_str());
		vector<CharString> newwords, newstop;
		CharStringLink ret;
		divideWords(cs, dic, stop, newwords, newstop, ret);//�ִʽ��
		words.concat(ret);
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

//tree:��������
//words:����ѯ�����йؼ���
//���أ�ÿ��Ԫ����һ��(articleid,times)��pair����ʾ��Щ�ؼ���һ���ڸ������г��ֶ��ٴ�
//����times�Ӵ�С����
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
/*
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
		vector<pair<int, int>> ret = query(tree, words);//����һ�β�ѯ�Ľ��
		rets.push_back(ret);
	}
	fin.close();
	//�����н��������ļ�
	outputQueryResult(rets);
}
*/