#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hashtable.h"
#include "CharString.h"
#include <vector>
using namespace std;


void loadDictionary(string filename, HashTable& dic);//��ָ�����ļ������شʵ�

void initDictionary(HashTable& dic,HashTable& stop);//�������Ĵʿ�,ͣ�ôʿ�

void updateDictionary(vector<CharString>& newWords,vector<CharString>& newStops);//�ִ���Ϻ���´ʿ�

void update(const char* filename, vector<CharString>& newWords);

#endif 