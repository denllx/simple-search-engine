#include "dividewords.h"
#include "getfile.h"

//��start��ʼ��Ѱ��������֡�Ӣ���ַ���
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

//��end��ʼ��ǰ����֡�Ӣ�Ĵ�
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

//�������ƥ��
void FMM(CharString& content,
		HashTable& dic,
		HashTable& stop,
		CharStringLink& forWords, 
		int& forCnt, 
		int& forSingleCnt)//�������ƥ��
{
	int len = content.size();
	int i = 1;
	while (i <= len) {
		char c = content[i];
		if (c == '\n' || c == ' ' || c == '\t') {
			++i;
			continue;//���з�
		}
		CharString tmp;
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')) {//Ӣ��
			CharString tmp = subEnNum(content, i);
			forWords.add(tmp);
			forCnt++;
			continue;
		}
		else if (c >= '0'&&c <= '9') {//����
			CharString tmp = subEnNum(content, i);
			forWords.add(tmp);
			forCnt++;
			continue;
		}

		bool found;
		content.substring(i, 1, tmp);
		char* tc1 = tmp.c_str();
		stop.find(tc1, found);//Ӣ��ֹͣ��,��������
		if (found) {
			i++;
			continue;
		}

		int j;
		for (j = 0; j < 15; j++) {//����
			//�ж�[i,i+length-1]�Ƿ��ڴʿ���
			int length = 16 - j;//���������������ַ�����
			content.substring(i, length * 2, tmp);//һ�����������ֽ�
			char* tmpc = tmp.c_str();
			bool found;
			dic.find(tmpc, found);
			if (found) {//���뵽�ִʽ��
				forWords.add(tmp);
				forCnt++;
				i += 2 * length;
				break;
			}
			int index = stop.find(tmpc, found);
			if (found) {//ֹͣ�ʣ�����
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

//�������ƥ��
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
			continue;//���з�
		}
		CharString tmp;
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')) {//Ӣ��
			CharString tmp = subEnNumReverse(content, i);
			backWords.insert(tmp);
			backCnt++;
			continue;
		}
		else if (c >= '0'&&c <= '9') {//����
			CharString tmp = subEnNumReverse(content, i);
			backWords.insert(tmp);
			backCnt++;
			continue;
		}

		bool found;
		content.substring(i, 1, tmp);
		char* tc1 = tmp.c_str();
		stop.find(tc1, found);//Ӣ��ֹͣ��,��������
		if (found) {
			i--;
			continue;
		}

		int j;
		for (j = 0; j < 15; j++) {//����
			//�ж�[i-length+1,i]�Ƿ��ڴʿ���
			int length = 16 - j;
			content.substring(i - length * 2 + 1, length * 2, tmp);//һ�����������ֽ�
			char* tmpc = tmp.c_str();
			bool found;
			dic.find(tmpc, found);
			if (found) {//���뵽�ִʽ��
				backWords.insert(tmp);
				backCnt++;
				i -= 2 * length;
				break;
			}
			int index = stop.find(tmpc, found);
			if (found) {//ֹͣ�ʣ�����
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


//content:���� dic:���Ĵʿ��ϣ�� 
//���أ��ִʽ�����洢���ַ���������
//newWords���¼���ʿ�Ĵ�
//newStop���¼���ͣ�ôʿ�Ĵ�
//�ִʷ�����˫�����ƥ��
void divideWords(CharString& content, 
						HashTable& dic,
						HashTable& stop,
						vector<CharString>& newWords,
						vector<CharString>& newStop,
						CharStringLink& result) {
	CharStringLink* forWords = new CharStringLink; 
	CharStringLink* backWords=new CharStringLink;//��������ִʽ��
	int forCnt=0, backCnt=0;//������ִ�����
	int forSingleCnt = 0, backSingleCnt = 0;//������������
	int forSingleCntDic = 0, backSingleCntDic = 0;//�������ڴʿ��г��ֵĵ�������
	int i = 1;
	int len = content.size();
	//˫�����ƥ��
	FMM(content,dic,stop,*forWords, forCnt, forSingleCnt);
	RMM(content,dic,stop,*backWords, backCnt, backSingleCnt);

	//���������������ѡһ
	if (forCnt > backCnt) {
		result = *backWords;
		delete forWords;
	}
	else if (forCnt < backCnt) {
		result = *forWords;//ѡ�����ٵ�
		delete backWords;
	}
	else {
		if (forSingleCnt > backSingleCnt) {
			result = *backWords;
			delete forWords;
		}
		else if (forSingleCnt < backSingleCnt) {
			result = *forWords;//ѡ�������ٵ�
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
				result = *forWords;//ѡ�ڴʿ��еĵ��ֶ��
				delete backWords;
			}
			else {
				result = *backWords;
				delete forWords;
			}
		}
	}
}