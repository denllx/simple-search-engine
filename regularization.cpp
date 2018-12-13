#include "regularization.h"
#include <regex>

//规范化标题
void titleRegularize(CharString& str) {
	//去掉右侧以'_'开头的“_网易新闻”之类的字样
	int i = str.size();
	while (i >= 1 && str[i] != '_') {
		i--;
	}
	CharString tmp;
	str.substring(1,i-1, tmp);
	str = tmp;
}

//提取时间
void timeRegularize(CharString& str) {
	//从字符串中提取符合yyyy-mm-dd hh:mm::ss的模式
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

//从包含时间的字符串中提取可能存在的来源后缀
//例如：2018-10-14 07:57:57　来源: <a id="ne_article_source" href="http://www.eeo.com.cn/" target="_blank" rel="nofollow">经济观察报</a>(北京)        
CharString extractSourceSuffix(CharString& timeStr) {
	CharString result;
	int index = timeStr.indexOf("/a>");
	if (index == 0) return result;
	int start = index + 3;//后缀开始位置
	int length = timeStr.size() - start + 1;//后缀从start开始，到size结束
	if (length == 0) return result;//空字符串
	timeStr.substring(start, length, result);//result="(北京)"
	return result;
}

//将文本中内嵌的html语言转换为字符串
//现在只遇到了&gt一种
void translate(CharString& str) {
	//&gt; -> >
	while (int idx = str.indexOf("&gt;")) {
		//将&gt;替换为>
		str.replace(idx, 4, ">");
	}
}