#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
using namespace std;

#define MAXLENGTH 20000

class CharString {
	char string[MAXLENGTH+2];
	int length;
public:
	int indexOf(const char* str,int pos=1)const ;//找出str从第pos个位置起第一次出现的位置
	int indexOf(CharString& str,int pos=1) const;
	void substring(int start, int length,CharString& dst);//从下标start开始，长度为length的字串保存在dst中
	void concat(const char* str);
	void concat(CharString str);
	void assign(const char* str);//用str为自身赋值
	void assign(const CharString& str);
	CharString(const CharString& str);
	CharString(const char* str);
	CharString() :length(0){}

	int size() const;//返回字符串长度，不超过MAXLENGTH
	void append(char c);//在末尾增加字符
	char& operator[](int index);//返回某个字符的引用
	const char& get(int index) const;//返回某个字符的拷贝
	bool empty();
	void clear();//清空字符串
	friend ostream& operator<<(ostream& out, const CharString& cstr);
	bool operator==(const CharString& str) const;
	bool operator<(const CharString& s) const;
	bool operator>(const CharString& s) const;
	bool operator!=(const CharString& str) const;
	bool operator==(char* s);
	bool operator<(char* s);
	bool operator>(char* s);
	bool operator!=(char* s);
	void trim();//去掉两端空白字符
	void replace(int start, int len,CharString& str);//将从start开始长为len的字符串用str替代
	void replace(int start, int len, const char* str);
	char* c_str();
};

#endif