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

//获取输入的一行关键词，分词，保存在字符串链表中
void getInput(char* input,CharStringLink& words,HashTable& dic,HashTable& stop) {
	string word;
	stringstream ss(input);
	while (ss >> word) {
		CharString cs(word.c_str());
		vector<CharString> newwords, newstop;
		CharStringLink ret;
		divideWords(cs, dic, stop, newwords, newstop, ret);//分词结果
		words.concat(ret);
	}
}	

//TODO：输出多行查询
//将单次查询的结果保存在result1.txt
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

//tree:倒排索引
//words:待查询的所有关键词
//返回：每个元素是一个(articleid,times)的pair，表示这些关键词一共在该文章中出现多少次
//按照times从大到小排序
vector<pair<int, int>> query(BalanceBinaryTree* tree,CharStringLink& words) {
	map<int, int> id2times;//key为网页的ID，value为所有关键字出现的总次数
	StringNode* p = words.head;
	while (p) {
		WordNode* node = NULL;
		bool found = tree->search(p->str, node);
		if (found == false) {
			p = p->next;
			continue;//单词不在新闻中出现
		}
		//将单词链表中所有网页的ID的单词出现数+1
		FileNode* p1 = node->firstfile->head;
		while (p1) {
			id2times[p1->ID]+=p1->times;//单词node在文档p1中出现的次数
			p1 = p1->next;
		}
		p = p->next;
	}
	//将数组从大到小排序
	vector<pair<int, int>> id2times_vec(id2times.begin(), id2times.end());
	sort(id2times_vec.begin(), id2times_vec.end(), cmpByValueReverse);
	//取非0的前5，如果不足5个取全部
	int len = id2times_vec.size() > 5 ? 5 : id2times_vec.size();
	vector<pair<int, int>> ret(id2times_vec.begin(), id2times_vec.begin() + len);
	return ret;
}

//每读入query1.txt的一行
//进行分词操作
//选出最大的五个新闻
//加入vector
//最终输出到result
/*
void runQuery(BalanceBinaryTree* tree) {
	string inputdir;
	getSubDir(inputdir, "\\");
	inputdir += "query1.txt";

	ifstream fin(inputdir.c_str());
	char s[500];//查询长度不会超过500吧。。。
	vector<vector<pair<int, int>>> rets;//多次查询的结果，每次保存为一个vector<pair>
	while (fin.getline(s,500)) {
		CharStringLink words;
		getInput(s, words);//将s按照空格分开，返回字符串链表
		StringNode* node = words.head;
		vector<pair<int, int>> ret = query(tree, words);//计算一次查询的结果
		rets.push_back(ret);
	}
	fin.close();
	//将所有结果输出到文件
	outputQueryResult(rets);
}
*/