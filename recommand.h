#ifndef RECOMMAND_H
#define RECOMMAND_H
#include <string>
#include <vector>
#include <map>
#include "hashtable.h"
#include "BalanceBinaryTree.h"
#include "FileLink.h"

using namespace std;

vector<int> recommand(string& title,double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID);//���ݱ��ⷵ���Ƽ�ID�б�
vector<int> _recommand(int ID,double** score,int totalArticles,int totalWords);//����ID�����Ƽ�ID�б�
double cossim(double** score, int col1, int col2,int lines);//����score������ָ�����е������پ���
void scoreMatrix(BalanceBinaryTree* tree, int totalArticles,double** score,int* id2wordnum);//����ÿ���ļ�������
void _scorematrix(WordNode* node, int totalArticles, double** score, int* id2wordnum,int& cnt);//�����û������Ľӿ�
double tfIdf(WordNode* word, FileNode* file,int totalArticles,int* id2wordnum);//����tf-idf����
void outputScoreMatrix(double** score,int totalArticles,int cnt);//��ӡ���־���
void runRecommand(double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID,map<int,CharString>& ID2title);//���ϵ����
void outputRecommand(vector<vector<int>> ret,map<int,CharString>& ID2title);//���Ƽ��ļ������result2.txt��ÿ��vectorΪһ���ļ����Ƽ����

#endif 