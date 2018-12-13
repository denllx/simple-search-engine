#ifndef DIVIDEWORDS_H
#define DIVIDEWORDS_H
#include "CharStringLink.h"
#include "hashtable.h"
#include <vector>

void divideWords(CharString& content, 
							HashTable& dic,
							HashTable& stop,
							vector<CharString>& newWords,
							vector<CharString>& newStops,
							CharStringLink& result);
CharString subEnNum(CharString& content, int& start);//��ĳ��λ�ÿ�ʼ������Ӣ���ַ����������ո�
void FMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& forWords, 
		int& forCnt, 
		int& forSingleCnt);//�������ƥ��
void RMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& backWords, 
		int& backCnt, 
		int& backSingleCnt);//�������ƥ��

#endif 