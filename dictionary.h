#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hashtable.h"
#include "CharString.h"
#include <vector>
using namespace std;


void loadDictionary(string filename, HashTable& dic);//从指定的文件名加载词典

void initDictionary(HashTable& dic,HashTable& stop);//导入中文词库,停用词库

void updateDictionary(vector<CharString>& newWords,vector<CharString>& newStops);//分词完毕后更新词库

void update(const char* filename, vector<CharString>& newWords);

#endif 