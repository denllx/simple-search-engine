#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <iostream>
#include <QThread>
#include "screen.h"
#include "hashtable.h"
#include "dictionary.h"
#include "getfile.h"
#include "CharStringLink.h"
#include "extractinfo.h"
#include "dividewords.h"
#include "FileLink.h"
#include "BalanceBinaryTree.h"
#include "recommand.h"

/*
	线程类
	完成解析分词的读入、字典的读入、平衡二叉树的构建、相似度矩阵的计算
*/

class Extractor :public QThread {
	Q_OBJECT

public:
	Screen* father;

	explicit Extractor(Screen* parent) :
		QThread(parent) {
		father = parent;//保存指向父亲组件的指针，以返回解析结果
	}

	virtual void run() Q_DECL_OVERRIDE {
		//载入词库
		father->dic.setcapacity(580000);
		father->stop.setcapacity(4000);
		initDictionary(father->dic, father->stop);

		//构建倒排文档
		string inputdir;
		getSubDir(inputdir, "\input");
		vector<string> files;
		getFiles(inputdir, files);
		int len = files.size();
		father->totalArticles = len;//文章总数
		father->id2wordnum = new int[len];//每个ID对应一个总词数
		for (int i = 0; i < len; i++) father->id2wordnum[i] = 0;
		CharString dir;//当前目录
		int ID;//文件编号
		string title;
		char word[40];//从.txt读入单词
		int numwords;//单篇文章单词总数

		for (int i = 0; i < len; ++i) {
			string s = files[i];
			//获取前缀和编号
			getprefix(files[i], dir, ID);
			const char* outnameInfo = getOutputName(dir.c_str(), ID, ".info");

			//从.info文件中读取标题
			ifstream fin(outnameInfo);
			//fin.getline(title, 50);
			getline(fin, title);
			father->title2ID.insert(pair<CharString, int>(title.c_str(), ID));//插入一条标题-ID映射
			father->ID2title.insert(pair<int, CharString>(ID, title.c_str()));//插入一条ID-标题映射
			fin.close();

			//从.txt中读取单词，建立平衡二叉树
			const char* outnameTxt = getOutputName(dir.c_str(), ID, ".txt");
			ifstream fin1(outnameTxt);
			numwords = 0;
			while (!fin1.eof()) {
				fin1 >> word;
				numwords++;
				//将新的单词节点插入平衡二叉树
				WordNode* ret = nullptr;//插入位置
				bool inserted = father->tree->insert(father->tree->root, ret, word);
				if (inserted) {//在二叉树中第一次出现
					//修改单词节点的属性
					ret->articles = 1;
					ret->times = 1;
					//新建文件节点、修改属性
					FileNode* file = new FileNode(ID, word);
					file->times++;
					//文件连到单词的文档链表中
					ret->insertFile(file);
				}
				else {//非新节点
					FileNode* tmp = NULL;
					bool exist = ret->searchFile(ID, tmp);//该单词是否在文档中第一次出现
					if (!exist) {
						ret->articles++;
						ret->times++;
						FileNode* newfile = new FileNode(ID, word);
						newfile->times++;
						ret->insertFile(newfile);
					}
					else {
						//该文档已经存在单词的文档链表中
						ret->times++;
						tmp->times++;
					}

				}
			}
			fin1.close();
			father->id2wordnum[ID] = numwords;
			emit extracted(int((i + 1) * 50 / len));
		}

		father->totalWords = father->tree->size();//总词数，约43万

		/*
		//初始化评分矩阵
		father->score = new double*[father->totalWords];
		for (int i = 0; i < father->totalWords; i++) {
			father->score[i] = new double[father->totalArticles];
			for (int j = 0; j < father->totalArticles; j++) father->score[i][j] = 0;
		}//shape=(总词数，总文章数) 
		//计算评分矩阵
		scoreMatrix(father->tree, father->totalArticles, father->score, father->id2wordnum);//通过倒排索引构建文章-单词评分表*/

		//读取相似度矩阵
		father->sim = new double*[father->totalArticles];
		for (int i = 0; i < father->totalArticles; i++) {
			father->sim[i] = new double[father->totalArticles];
			emit(extracted(50 + int(25 * (i + 1) / father->totalArticles)));

		}
		//readsimMatrix(father->sim, father->totalArticles);
		string subdir;
		getSubDir(subdir, "\output");
		subdir += "\\sim.txt";
		ifstream fin(subdir);
		for (int i = 0; i < father->totalArticles; i++) {
			for (int j = 0; j < father->totalArticles; j++) {
				fin >> father->sim[i][j];
				emit(extracted(75 + int(25 * (i + 1) / father->totalArticles)));
			}
		}
		fin.close();

		emit extracted(-1);//解析完毕
		cout << "词汇输出完毕！" << endl;
	}

signals:
	void extracted(int value);//一篇文章解析完毕,value为已解析完成的文章总数
};
#endif 