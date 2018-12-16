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
	������ҳ���߳���
*/

class Extractor :public QThread {
	Q_OBJECT

public:
	Screen* father;

	explicit Extractor(Screen* parent) :
		QThread(parent) {
		father = parent;//����ָ���������ָ�룬�Է��ؽ������
	}

	virtual void run() Q_DECL_OVERRIDE {
		clock_t start = clock();
		HashTable dic(580000), stop(4000);
		initDictionary(dic, stop);//��������,���,ֹͣ�ʿ�
		clock_t end = clock();
		cout << "���شʿ⹲��ʱ" << (end - start) / CLOCKS_PER_SEC << "��" << endl;

		string inputdir;
		getSubDir(inputdir, "\input");
		vector<string> files;
		getFiles(inputdir, files);
		vector<CharString> newWordsAll, newStopAll;
		int len = files.size();
		father->totalArticles = len;//��������
		father->id2wordnum = new int[len];//ÿ��ID��Ӧһ���ܴ���
		for (int i = 0; i < len; i++) father->id2wordnum[i] = 0;
		CharString dir;//��ǰĿ¼
		int ID;//�ļ����
		for (int i = 0; i < len; ++i) {
			CharStringLink divideResult;
			NewsInfo info;
			vector<CharString> newWords, newStop;//�ʿ����������´�
			string s = files[i];
			//��ȡǰ׺�ͱ��
			getprefix(files[i], dir, ID);
			//����ǰ׺����š���׺��output��������ļ���
			const char* outnameInfo = getOutputName(dir.c_str(), ID, ".info");
			//freopen(outnameInfo, "w", stdout);
			ofstream fout(outnameInfo);
			info = extractInfo(s);//��ȡ�ؼ���Ϣ
			father->title2ID.insert(pair<CharString, int>(info.title, ID));//����һ������-IDӳ��
			father->ID2title.insert(pair<int, CharString>(ID, info.title));//����һ��ID-����ӳ��
			fout << info << endl;
			fout.close();

			divideWords(info.body, dic, stop, newWords, newStop, divideResult);
			father->id2wordnum[ID] = divideResult.size();//��IDƪ���µ��ܴ���
			const char* outnameTxt = getOutputName(dir.c_str(), ID, ".txt");
			//freopen(outnameTxt, "w", stdout);
			ofstream fout1(outnameTxt);
			fout << divideResult << endl;//����ִʽ�����ļ�
			//freopen("CON", "w", stdout);//�ض��򵽿���̨
			fout.close();

			newWordsAll.insert(newWordsAll.end(), newWords.begin(), newWords.end());
			newStopAll.insert(newStopAll.end(), newStop.begin(), newStop.end());
			cout << "��" << (i + 1) << "ƪ���½�����ϣ� " << ID << endl;
			emit extracted(int((i + 1)*100/len));
			//��䵥��ƽ�������
			for (StringNode* p = divideResult.head; p; p = p->next) {
				WordNode* ret = nullptr;
				//���µĵ��ʽڵ����ƽ�������
				bool inserted = father->tree->insert(father->tree->root, ret, p->str);
				if (inserted) {//�ڶ������е�һ�γ���
					//�޸ĵ��ʽڵ������
					ret->articles = 1;
					ret->times = 1;
					//�½��ļ��ڵ㡢�޸�����
					FileNode* file = new FileNode(ID, p->str);
					file->times++;
					//�ļ��������ʵ��ĵ�������
					ret->insertFile(file);
				}
				else {//���½ڵ�
					FileNode* tmp = NULL;
					bool exist = ret->searchFile(ID, tmp);
					if (!exist) {
						//�õ����ڱ��ĵ��е�һ�γ���
						ret->articles++;
						ret->times++;
						FileNode* newfile = new FileNode(ID, p->str);
						newfile->times++;
						ret->insertFile(newfile);
					}
					else {
						//���ĵ��Ѿ����ڵ��ʵ��ĵ�������
						ret->times++;
						tmp->times++;
					}
				}
			}
		}
		father->totalWords = father->tree->size();
		father->score = new double*[father->totalWords];
		for (int i = 0; i < father->totalWords; i++) {
			father->score[i] = new double[father->totalArticles];
			for (int j = 0; j < father->totalArticles; j++) father->score[i][j] = 0;
		}//shape=(�ܴ�������������) 

		scoreMatrix(father->tree, father->totalArticles, father->score, father->id2wordnum);//ͨ������������������-�������ֱ�
		emit extracted(-1);//�������
		cout << "�ʻ������ϣ�" << endl;
	}

signals:
	void extracted(int value);//һƪ���½������,valueΪ�ѽ�����ɵ���������
};
#endif 