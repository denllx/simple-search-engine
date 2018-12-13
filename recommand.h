#ifndef RECOMMAND_H
#define RECOMMAND_H
#include <string>
#include <vector>
#include <map>
#include "hashtable.h"
#include "BalanceBinaryTree.h"
#include "FileLink.h"

using namespace std;

vector<int> recommand(string& title,double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID);//根据标题返回推荐ID列表
vector<int> _recommand(int ID,double** score,int totalArticles,int totalWords);//根据ID返回推荐ID列表
double cossim(double** score, int col1, int col2,int lines);//计算score矩阵中指定两列的曼哈顿距离
void scoreMatrix(BalanceBinaryTree* tree, int totalArticles,double** score,int* id2wordnum);//返回每个文件的评分
void _scorematrix(WordNode* node, int totalArticles, double** score, int* id2wordnum,int& cnt);//不对用户公开的接口
double tfIdf(WordNode* word, FileNode* file,int totalArticles,int* id2wordnum);//计算tf-idf评分
void outputScoreMatrix(double** score,int totalArticles,int cnt);//打印评分矩阵
void runRecommand(double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID,map<int,CharString>& ID2title);//以上的组合
void outputRecommand(vector<vector<int>> ret,map<int,CharString>& ID2title);//将推荐文件输出到result2.txt，每个vector为一个文件的推荐结果

#endif 