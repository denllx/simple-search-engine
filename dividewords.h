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
CharString subEnNum(CharString& content, int& start);//从某个位置开始的连续英文字符串（包括空格）
void FMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& forWords, 
		int& forCnt, 
		int& forSingleCnt);//正向最大匹配
void RMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& backWords, 
		int& backCnt, 
		int& backSingleCnt);//逆向最大匹配

#endif 