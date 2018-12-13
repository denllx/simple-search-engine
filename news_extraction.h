#ifndef NEWS_EXTRACTION
#define NEWS_EXTRACTION

#include "BalanceBinaryTree.h"
#include <map>

void newsExtraction(BalanceBinaryTree*& wordsTree,
					int*& id2wordnum,
					int& totalArticles,
					map<CharString,int>& title2ID,
					map<int,CharString>& ID2title);

#endif 