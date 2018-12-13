#include "news_extraction.h"
#include "getfile.h"
#include "extractinfo.h"
#include "dictionary.h"
#include "dividewords.h"
#include <time.h>
#include <string>
#include "BalanceBinaryTree.h"

using namespace std;

void newsExtraction(BalanceBinaryTree*& wordsTree,
					int*& id2wordnum,
					int& totalArticles,
					map<CharString,int>& title2ID,
					map<int,CharString>& ID2title) {
	clock_t start = clock();
	HashTable dic(580000), stop(4000);
	initDictionary(dic, stop);//加载中文,标点,停止词库
	clock_t end = clock();
	cout << "加载词库共耗时" << (end - start) / CLOCKS_PER_SEC << "秒" << endl;

	string inputdir;
	getSubDir(inputdir, "\input");
	vector<string> files;
	getFiles(inputdir, files);
	vector<CharString> newWordsAll,newStopAll;
	int len = files.size();
	totalArticles = len;//文章总数
	id2wordnum = new int[len];//每个ID对应一个总词数
	for (int i = 0; i < len; i++) id2wordnum[i] = 0;
	CharString dir;//当前目录
	int ID;//文件编号
	for (int i =0; i <len; ++i) {
		CharStringLink divideResult;
		NewsInfo info;
		vector<CharString> newWords, newStop;//词库中新增的新词
		string s = files[i];
		//获取前缀和编号
		getprefix(files[i], dir, ID);
		//根据前缀、编号、后缀、output构建输出文件名
		const char* outnameInfo = getOutputName(dir.c_str(),ID, ".info");
		//freopen(outnameInfo, "w", stdout);
		ofstream fout(outnameInfo);
		info=extractInfo(s);//提取关键信息
		title2ID.insert(pair<CharString, int>(info.title, ID));//插入一条标题-ID映射
		ID2title.insert(pair<int, CharString>(ID, info.title));//插入一条ID-标题映射
		fout << info << endl;
		fout.close();

		divideWords(info.body, dic, stop, newWords, newStop,divideResult);
		id2wordnum[ID] = divideResult.size();//第ID篇文章的总词数
		const char* outnameTxt = getOutputName(dir.c_str(),ID, ".txt");
		//freopen(outnameTxt, "w", stdout);
		ofstream fout1(outnameTxt);
		fout << divideResult << endl;//输出分词结果到文件
		//freopen("CON", "w", stdout);//重定向到控制台
		fout.close();

		newWordsAll.insert(newWordsAll.end(), newWords.begin(), newWords.end());
		newStopAll.insert(newStopAll.end(), newStop.begin(), newStop.end());
		cout << "第" << (i + 1) << "篇文章解析完毕！ " << ID<<endl;

		//填充单词平衡二叉树
		for (StringNode* p = divideResult.head; p; p = p->next) {
			WordNode* ret=nullptr;
			//将新的单词节点插入平衡二叉树
			bool inserted=wordsTree->insert(wordsTree->root,ret, p->str);
			if (inserted) {//在二叉树中第一次出现
				//修改单词节点的属性
				ret->articles = 1;
				ret->times = 1;
				//新建文件节点、修改属性
				FileNode* file = new FileNode(ID, p->str);
				file->times++;
				//文件连到单词的文档链表中
				ret->insertFile(file);
			}
			else {//非新节点
				FileNode* tmp = NULL;
				bool exist = ret->searchFile(ID,tmp);
				if (!exist) {
					//该单词在本文档中第一次出现
					ret->articles++;
					ret->times++;
					FileNode* newfile = new FileNode(ID, p->str);
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
	}

	cout << "词汇输出完毕！" << endl;
	//wordsTree->inorderTraversal(wordsTree->root, sortNodeFile);
	//wordsTree->inorderTraversal(wordsTree->root,printNode);
	//同步词库更新结果到文件
	//updateDictionary(newWordsAll,newStopAll);
}