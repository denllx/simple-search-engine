#include "CharString.h"


CharString::CharString(const char* str) {
	int i = 1;
	while (i<=MAXLENGTH&&str[i-1] != '\0') {
		string[i] = str[i-1];
		i++;
	}
	string[i] = '\0';
	length = i-1;
}

void CharString::assign(const char* str) {
	*this = str;
}

CharString::CharString(const CharString& str) {
	int i = 1;
	while (str.string[i] != '\0') {
		string[i] = str.string[i];
		i++;
	}
	string[i] = '\0';
	length = str.length;
}

void CharString::assign(const CharString& str) {
	*this = str;
}

char& CharString::operator[](int index) {
	//输入范围由上层调用者控制，无需检查
	return string[index];
}

void CharString::append(char c) {
	if (length == MAXLENGTH) {
		return;
	}
	string[++length] = c;
	string[length + 1] = '\0';
}

void CharString::concat(const char* str) {
	for (int i = 1; str[i-1] != '\0'; ++i) {
		this->append(str[i-1]);
	}
}

void CharString::concat(CharString str) {
	for (int i = 1; i <= str.size(); ++i) {
		append(str[i]);
	}
}

//查找从pos开始第一次出现str的位置，若不存在返回0
int CharString::indexOf(const char* str,int pos) const{
	CharString cstr(str);
	return indexOf(cstr, pos);
}

int CharString::indexOf(CharString& str,int pos) const{
	//构建失效函数表
	if (str.empty()) {
		return 0;
	}
	int* next = new int[str.size()+1];//1 to str.size()
	int j = 1,k=0,m=str.size();
	next[1] = 0;
	while (j < m) {
		if (k == 0 || str[j] == str[k]) {
			{
				++j;
				++k;
				next[j] = k;
			}
		}
		else {
			k = next[k];
		}
	}
	int i = pos,  n = length;
	j = 1;
	while (i <= n && j <= m) {
		if (j == 0 || string[i] == str[j]) {
			++i;
			++j;
		}
		else {
			j = next[j];
		}
	}
	delete[] next;
	if (j > m) {
		return i - m;//匹配成功
	}
	else {
		return 0;
	}
	
}

void CharString::substring(int start, int len, CharString& dst) {
	dst = "";
	if (start > length || len < 1) {
		return;
	}
	for (int i = start; i < start + len && i <= length; ++i) {
		dst.append(string[i]);
	}
	
}

ostream& operator<<(ostream& out, const CharString& str) {
	for (int i = 1; i <= str.size(); ++i) out << str.string[i];
	return out;
}

bool CharString::operator==(const CharString& s) const{
	if (length != s.size()) return false;
	for (int i = 1; i <= length; ++i) {
		if (string[i] != s.get(i)) {
			return false;
		}
	}
	return true;
}

bool CharString::operator==(char* s) {
	if (length != strlen(s)) return false;
	for (int i = 1; i <= length; i++) {
		if (string[i] != s[i - 1]) return false;
	}
	return true;
}

//字典序比较2个单词
bool CharString::operator<(const CharString& s) const{
	int len1 = this->size();
	int len2 = s.size();
	int minlen = len1 < len2 ? len1 : len2;
	for (int i = 1; i <= minlen; i++) {
		if (this->string[i] < s.get(i)) return true;
		else if (this->string[i] > s.get(i)) return false;
	}
	return len1 < len2;
}

bool CharString::operator<(char* s) {
	int len1 = this->size();
	int len2 = strlen(s);
	int minlen = len1 < len2 ? len1 : len2;
	for (int i = 1; i <= minlen; i++) {
		if (this->string[i] < s[i-1]) return true;
		else if (this->string[i] > s[i-1]) return false;
	}
	return len1 < len2;
}
bool CharString::operator>(const CharString& s) const{
	int len1 = this->size();
	int len2 = s.size();
	int minlen = len1 < len2 ? len1 : len2;
	for (int i = 1; i <= minlen; i++) {
		if (this->string[i] > s.get(i)) return true;
		else if (this->string[i] < s.get(i)) return false;
	}
	return len1 > len2;
}

bool CharString::operator>(char* s) {
	int len1 = this->size();
	int len2 = strlen(s);
	int minlen = len1 < len2 ? len1 : len2;
	for (int i = 1; i <= minlen; i++) {
		if (this->string[i] > s[i - 1]) return true;
		else if (this->string[i] < s[i - 1]) return false;
	}
	return len1 > len2;
}

bool CharString::operator!=(const CharString& s) const{
	return !(operator==(s));
}

bool CharString::operator!=(char* s) {
	return !(operator==(s));
}

int CharString::size() const{
	return length;
}

void CharString::clear() {
	memset(string, 0, sizeof(char)*(1+length));
	length = 0;
}

bool CharString::empty() {
	return length == 0;
}

bool isBlank(char c) {
	return c == ' '||c == '\n'||c == '\t';
}

void CharString::trim() {
	int head = 1, tail = length;
	while (head <= length&& isBlank(string[head])) {
		head++;
	}
	while (tail >= 1 && isBlank(string[tail])) {
		tail--;
	}
	length = tail - head + 1;
	for (int i = 1; i <= length; ++i) {
		string[i] = string[head+i-1];
	}
	//含占位符&nbsp;和&nbsp;|的视为空字符串
	while (int idx = indexOf("&nbsp;")) {
		//截取从[1,idx]到[idx+len,length]
		int len = string[idx + 6] == '|' ? 7 : 6;//"&nbsp"或"$&nbsp|"
		CharString s1, s2;
		substring(1, idx - 1, s1);
		substring(idx + len, length - idx - len + 1,s2);
		s1.concat(s2);
		this->assign(s1);
	}
}

//字符串从下标start开始长度为len的字符串被str替代
//超出原长度则截取
void CharString::replace(int start, int len, CharString& str) {
	if (start < 1 && len<0) return;
	//[1,start-1]   [start+len,length]
	CharString s1, s2;
	substring(1, start - 1, s1);
	substring(start + len, length - start - len + 1, s2);
	s1.concat(str);
	s1.concat(s2);
	this->assign(s1);
}

void CharString::replace(int start, int len,const char* c) {
	CharString str(c);
	replace(start, len, str);
}

//返回只读字符串
char* CharString::c_str() {
	if (length == 0) return NULL;
	return string+1;
}

const char& CharString::get(int index) const{
	return string[index];
}



