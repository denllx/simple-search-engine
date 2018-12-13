#include "regularization.h"
#include <regex>

//�淶������
void titleRegularize(CharString& str) {
	//ȥ���Ҳ���'_'��ͷ�ġ�_�������š�֮�������
	int i = str.size();
	while (i >= 1 && str[i] != '_') {
		i--;
	}
	CharString tmp;
	str.substring(1,i-1, tmp);
	str = tmp;
}

//��ȡʱ��
void timeRegularize(CharString& str) {
	//���ַ�������ȡ����yyyy-mm-dd hh:mm::ss��ģʽ
	regex re("(\\d{4})-(0\\d{1}|1[0-2])-(0\\d{1}|[12]\\d{1}|3[01])\\s(0\\d{1}|1\\d{1}|2[0-3]):[0-5]\\d{1}:([0-5]\\d{1})");
	regex resimple("(\\d{4})-(0\\d{1}|1[0-2])-(0\\d{1}|[12]\\d{1}|3[01])");
	smatch result,simpleresult;
	string s;
	for (int i = 1; i <= str.size(); ++i) {
		s += str[i];
	}
	regex_search(s, result, re);
	string resultstr = result[0];
	if (!resultstr.empty())str = resultstr.c_str();
	else {
		regex_search(s, simpleresult, resimple);
		string simpleresultstr = simpleresult[0];
		str = simpleresultstr.c_str();
	}
}

//�Ӱ���ʱ����ַ�������ȡ���ܴ��ڵ���Դ��׺
//���磺2018-10-14 07:57:57����Դ: <a id="ne_article_source" href="http://www.eeo.com.cn/" target="_blank" rel="nofollow">���ù۲챨</a>(����)        
CharString extractSourceSuffix(CharString& timeStr) {
	CharString result;
	int index = timeStr.indexOf("/a>");
	if (index == 0) return result;
	int start = index + 3;//��׺��ʼλ��
	int length = timeStr.size() - start + 1;//��׺��start��ʼ����size����
	if (length == 0) return result;//���ַ���
	timeStr.substring(start, length, result);//result="(����)"
	return result;
}

//���ı�����Ƕ��html����ת��Ϊ�ַ���
//����ֻ������&gtһ��
void translate(CharString& str) {
	//&gt; -> >
	while (int idx = str.indexOf("&gt;")) {
		//��&gt;�滻Ϊ>
		str.replace(idx, 4, ">");
	}
}