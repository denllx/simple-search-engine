#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <map>
#include "CharStringLink.h"
#include "inverted_file_index.h"
using namespace std;


/*
���ݹؼ��ʷ�������ID
�ؼ��ʳ����ܴ����������ȳ���
*/

//wordsTree���ڵ�������
//words�Ǵ���ѯ�ĵ���
//����<ID,�����ܴ���>���б����Ȳ�����5��
vector<pair<int, int>> query(BalanceBinaryTree* wordsTree,CharStringLink& words);

//��ȡһ�����룬���տո�ָ�Ϊ�ؼ���
void getInput(char* s,CharStringLink& words);

//����������result1.txt
void outputQueryResult(vector<vector<pair<int, int>>>& ret);

//�������������ϣ���ÿ�н���
void runQuery(BalanceBinaryTree* wordsTree);


#endif 