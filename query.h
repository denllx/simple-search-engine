#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <map>
#include "CharStringLink.h"
#include "inverted_file_index.h"
using namespace std;


/*
根据关键词返回文章ID
关键词出现总次数最多的优先出现
*/

//wordsTree是在倒排索引
//words是待查询的单词
//返回<ID,出现总次数>的列表（长度不超过5）
vector<pair<int, int>> query(BalanceBinaryTree* wordsTree,CharStringLink& words);

//获取一行输入，按照空格分割为关键词
void getInput(char* s,CharStringLink& words);

//将结果输出到result1.txt
void outputQueryResult(vector<vector<pair<int, int>>>& ret);

//将上述三步整合，对每行进行
void runQuery(BalanceBinaryTree* wordsTree);


#endif 