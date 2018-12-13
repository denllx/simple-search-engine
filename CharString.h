#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
using namespace std;

#define MAXLENGTH 20000

class CharString {
	char string[MAXLENGTH+2];
	int length;
public:
	int indexOf(const char* str,int pos=1)const ;//�ҳ�str�ӵ�pos��λ�����һ�γ��ֵ�λ��
	int indexOf(CharString& str,int pos=1) const;
	void substring(int start, int length,CharString& dst);//���±�start��ʼ������Ϊlength���ִ�������dst��
	void concat(const char* str);
	void concat(CharString str);
	void assign(const char* str);//��strΪ����ֵ
	void assign(const CharString& str);
	CharString(const CharString& str);
	CharString(const char* str);
	CharString() :length(0){}

	int size() const;//�����ַ������ȣ�������MAXLENGTH
	void append(char c);//��ĩβ�����ַ�
	char& operator[](int index);//����ĳ���ַ�������
	const char& get(int index) const;//����ĳ���ַ��Ŀ���
	bool empty();
	void clear();//����ַ���
	friend ostream& operator<<(ostream& out, const CharString& cstr);
	bool operator==(const CharString& str) const;
	bool operator<(const CharString& s) const;
	bool operator>(const CharString& s) const;
	bool operator!=(const CharString& str) const;
	bool operator==(char* s);
	bool operator<(char* s);
	bool operator>(char* s);
	bool operator!=(char* s);
	void trim();//ȥ�����˿հ��ַ�
	void replace(int start, int len,CharString& str);//����start��ʼ��Ϊlen���ַ�����str���
	void replace(int start, int len, const char* str);
	char* c_str();
};

#endif