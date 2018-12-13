#include "dividewords.h"
#include "getfile.h"

//从start开始，寻找最长的数字、英文字符串
CharString subEnNum(CharString& content, int& start) {
	int len = content.size();
	int oldstart = start;
	while (start <= len) {
		char c = content[start];
		if ((c >= 'A'&&c <= 'Z')
			|| (c >= 'a'&&c <= 'z')
			|| c == ' '
			|| c == '-'
			|| c == '.'
			||(c>='0'&&c<='9')) {
			start++;
		}
		else {
			break;
		}
	}
	CharString result;
	content.substring(oldstart, start-oldstart,result);
	return result;
}

//从end开始向前最长数字、英文串
CharString subEnNumReverse(CharString& content, int& end) {
	int len = content.size();
	int oldend=end;
	while (end >= 1) {
		char c = content[end];
		if ((c >= 'A'&&c <= 'Z')
			|| (c >= 'a'&&c <= 'z')
			|| c == ' '
			|| c == '-'
			|| c == '.'
			|| (c >= '0'&&c <= '9')) {
			--end;
		}
		else {
			break;
		}
	}
	CharString result;
	content.substring(end+1,oldend -end, result);
	return result;
}

//正向最大匹配
void FMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& forWords, 
		int& forCnt, 
		int& forSingleCnt)//正向最大匹配
{
	int len = content.size();
	int i = 1;
	while (i <= len) {
		char c = content[i];
		if (c == '\n' || c == ' ' || c == '\t') {
			++i;
			continue;//换行符
		}
		CharString tmp;
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')) {//英文
			CharString tmp = subEnNum(content, i);
			forWords.add(tmp);
			forCnt++;
			continue;
		}
		else if (c >= '0'&&c <= '9') {//数字
			CharString tmp = subEnNum(content, i);
			forWords.add(tmp);
			forCnt++;
			continue;
		}

		bool found;
		content.substring(i, 1, tmp);
		char* tc1 = tmp.c_str();
		stop.find(tc1, found);//英文停止词,包括标点等
		if (found) {
			i++;
			continue;
		}

		int j;
		for (j = 0; j < 15; j++) {//中文
			//判断[i,i+length-1]是否在词库中
			int length = 16 - j;//汉字字数，而非字符个数
			content.substring(i, length * 2, tmp);//一个汉字两个字节
			char* tmpc = tmp.c_str();
			bool found;
			dic.find(tmpc, found);
			if (found) {//加入到分词结果
				forWords.add(tmp);
				forCnt++;
				i += 2 * length;
				break;
			}
			int index = stop.find(tmpc, found);
			if (found) {//停止词，舍弃
				i += 2 * length;
				break;
			}
		}
		if (j == 15) {
			content.substring(i, 2, tmp);
			char* tmpc = tmp.c_str();
			int index = stop.find(tmpc, found);
			if (!found) {
				forWords.add(tmp);
				forCnt++;
				forSingleCnt++;
			}
			i += 2;
		}
	}
}

//逆向最大匹配
void RMM(CharString& content,
		HashTable& dic,
		HashTable& stop, 
		CharStringLink& backWords, 
		int& backCnt, 
		int& backSingleCnt) {
	int len = content.size();
	int i = len;
	while (i >= 1) {
		char c = content[i];
		if (c == '\n' || c == ' ' || c == '\t') {
			--i;
			continue;//换行符
		}
		CharString tmp;
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')) {//英文
			CharString tmp = subEnNumReverse(content, i);
			backWords.insert(tmp);
			backCnt++;
			continue;
		}
		else if (c >= '0'&&c <= '9') {//数字
			CharString tmp = subEnNumReverse(content, i);
			backWords.insert(tmp);
			backCnt++;
			continue;
		}

		bool found;
		content.substring(i, 1, tmp);
		char* tc1 = tmp.c_str();
		stop.find(tc1, found);//英文停止词,包括标点等
		if (found) {
			i--;
			continue;
		}

		int j;
		for (j = 0; j < 15; j++) {//中文
			//判断[i-length+1,i]是否在词库中
			int length = 16 - j;
			content.substring(i - length * 2 + 1, length * 2, tmp);//一个汉字两个字节
			char* tmpc = tmp.c_str();
			bool found;
			dic.find(tmpc, found);
			if (found) {//加入到分词结果
				backWords.insert(tmp);
				backCnt++;
				i -= 2 * length;
				break;
			}
			int index = stop.find(tmpc, found);
			if (found) {//停止词，舍弃
				i -= 2 * length;
				break;
			}
		}
		if (j == 15) {
			content.substring(i - 1, 2, tmp);
			char* tmpc = tmp.c_str();
			int index = stop.find(tmpc, found);
			if (!found) {
				backWords.insert(tmp);
				backCnt++;
				backSingleCnt++;
			}
			i -= 2;

		}
	}
}


//content:正文 dic:中文词库哈希表 
//返回：分词结果，存储在字符串链表中
//newWords：新加入词库的词
//newStop：新加入停用词库的词
//分词方法：双向最大匹配
void divideWords(CharString& content, 
						HashTable& dic,
						HashTable& stop,
						vector<CharString>& newWords,
						vector<CharString>& newStop,
						CharStringLink& result) {
	CharStringLink* forWords = new CharStringLink; 
	CharStringLink* backWords=new CharStringLink;//正、反向分词结果
	int forCnt=0, backCnt=0;//正反向分词数量
	int forSingleCnt = 0, backSingleCnt = 0;//正反向单字数量
	int forSingleCntDic = 0, backSingleCntDic = 0;//正反向在词库中出现的单字数量
	int i = 1;
	int len = content.size();
	//双向最大匹配
	FMM(content,dic,stop,*forWords, forCnt, forSingleCnt);
	RMM(content,dic,stop,*backWords, backCnt, backSingleCnt);

	//从正向和逆向结果中选一
	if (forCnt > backCnt) {
		result = *backWords;
		delete forWords;
	}
	else if (forCnt < backCnt) {
		result = *forWords;//选词数少的
		delete backWords;
	}
	else {
		if (forSingleCnt > backSingleCnt) {
			result = *backWords;
			delete forWords;
		}
		else if (forSingleCnt < backSingleCnt) {
			result = *forWords;//选单字数少的
			delete backWords;
		}
		else {
			StringNode* pFor = forWords->head;
			StringNode* pBack = backWords->head;
			while (pFor) {
				bool foundFor, foundBack;
				char* forWord = pFor->str.c_str();
				if (strlen(forWord) == 2) {
					dic.find(pFor->str.c_str(), foundFor);
					if (foundFor) forSingleCntDic++;
				}
				char* backWord = pBack->str.c_str();
				if (strlen(backWord) == 2) {
					dic.find(pBack->str.c_str(), foundBack);
					if (foundBack) backSingleCntDic++;
				}
				pFor = pFor->next;
				pBack = pBack->next;
			}
			if (forSingleCnt > backSingleCntDic) {
				result = *forWords;//选在词库中的单字多的
				delete backWords;
			}
			else {
				result = *backWords;
				delete forWords;
			}
		}
	}
}