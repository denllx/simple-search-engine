#include "dictionary.h"
#include "getfile.h"
#include <vector>
#include <string>
using namespace std;

void loadDictionary(string filename, HashTable& dic) {
	ifstream infile;
	infile.open(filename.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
	string s;
	while (infile >> s) {
		int len = s.size();
		char* copy = new char[len + 1];
		for (int i = 0; i < len; ++i) copy[i] = s[i];//深拷贝
		copy[len] = '\0';
		dic.insert(copy);
	}
	infile.close();//关闭文件
}

void initDictionary(HashTable& dic,HashTable& stop) {
	//载入词库
	string dicdir;
	getSubDir(dicdir, "\dic");
	vector<string> files;
	getFiles(dicdir, files);

	cout << "开始载入中文词库..." << endl;
	loadDictionary(files[0], dic);
	cout << "中文词库载入完毕!共" <<dic.size()<<"个词被收录"<< endl;

	cout << "开始载入停止词库..." << endl;
	loadDictionary(files[1], stop);
	cout << "停止词库载入完毕！共" << stop.size() << "个停止词被收录" << endl;
	//其他初始化操作...
}

void update(const char* filename, vector<CharString>& newWords) {
	freopen(filename, "a", stdout);
	for (auto newWord : newWords) cout << newWord << endl;
	freopen("CON", "w", stdout);//重定向到控制台
}

//分词结束后将新词newWords添加到文件
void updateDictionary(vector<CharString>& newWords,vector<CharString>& newStops) {
	string dicdir;
	getSubDir(dicdir, "\dic");
	vector<string> files;
	getFiles(dicdir, files);
	//新词
	const char* dicname = files[0].c_str();
	update(dicname, newWords);
	//停用词
	const char* stopname = files[1].c_str();
	update(stopname, newStops);
}