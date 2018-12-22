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
	�߳���
	��ɽ����ִʵĶ��롢�ֵ�Ķ��롢ƽ��������Ĺ��������ƶȾ���ļ���
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
		//����ʿ�
		father->dic.setcapacity(580000);
		father->stop.setcapacity(4000);
		initDictionary(father->dic, father->stop);

		//���������ĵ�
		string inputdir;
		getSubDir(inputdir, "\input");
		vector<string> files;
		getFiles(inputdir, files);
		int len = files.size();
		father->totalArticles = len;//��������
		father->id2wordnum = new int[len];//ÿ��ID��Ӧһ���ܴ���
		for (int i = 0; i < len; i++) father->id2wordnum[i] = 0;
		CharString dir;//��ǰĿ¼
		int ID;//�ļ����
		string title;
		char word[40];//��.txt���뵥��
		int numwords;//��ƪ���µ�������

		for (int i = 0; i < len; ++i) {
			string s = files[i];
			//��ȡǰ׺�ͱ��
			getprefix(files[i], dir, ID);
			const char* outnameInfo = getOutputName(dir.c_str(), ID, ".info");

			//��.info�ļ��ж�ȡ����
			ifstream fin(outnameInfo);
			//fin.getline(title, 50);
			getline(fin, title);
			father->title2ID.insert(pair<CharString, int>(title.c_str(), ID));//����һ������-IDӳ��
			father->ID2title.insert(pair<int, CharString>(ID, title.c_str()));//����һ��ID-����ӳ��
			fin.close();

			//��.txt�ж�ȡ���ʣ�����ƽ�������
			const char* outnameTxt = getOutputName(dir.c_str(), ID, ".txt");
			ifstream fin1(outnameTxt);
			numwords = 0;
			while (!fin1.eof()) {
				fin1 >> word;
				numwords++;
				//���µĵ��ʽڵ����ƽ�������
				WordNode* ret = nullptr;//����λ��
				bool inserted = father->tree->insert(father->tree->root, ret, word);
				if (inserted) {//�ڶ������е�һ�γ���
					//�޸ĵ��ʽڵ������
					ret->articles = 1;
					ret->times = 1;
					//�½��ļ��ڵ㡢�޸�����
					FileNode* file = new FileNode(ID, word);
					file->times++;
					//�ļ��������ʵ��ĵ�������
					ret->insertFile(file);
				}
				else {//���½ڵ�
					FileNode* tmp = NULL;
					bool exist = ret->searchFile(ID, tmp);//�õ����Ƿ����ĵ��е�һ�γ���
					if (!exist) {
						ret->articles++;
						ret->times++;
						FileNode* newfile = new FileNode(ID, word);
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
			fin1.close();
			father->id2wordnum[ID] = numwords;
			emit extracted(int((i + 1) * 50 / len));
		}

		father->totalWords = father->tree->size();//�ܴ�����Լ43��

		/*
		//��ʼ�����־���
		father->score = new double*[father->totalWords];
		for (int i = 0; i < father->totalWords; i++) {
			father->score[i] = new double[father->totalArticles];
			for (int j = 0; j < father->totalArticles; j++) father->score[i][j] = 0;
		}//shape=(�ܴ�������������) 
		//�������־���
		scoreMatrix(father->tree, father->totalArticles, father->score, father->id2wordnum);//ͨ������������������-�������ֱ�*/

		//��ȡ���ƶȾ���
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

		emit extracted(-1);//�������
		cout << "�ʻ������ϣ�" << endl;
	}

signals:
	void extracted(int value);//һƪ���½������,valueΪ�ѽ�����ɵ���������
};
#endif 