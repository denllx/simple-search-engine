/*
*����ҳ�н������ؼ���Ϣ
*/
#ifndef EXTRACTINFO_H
#define EXTRACTINFO_H

#include "CharString.h"
#include "getfile.h"

//html��ǩ
class Label {
public:
	int type;//��ǩ�����ͣ���������
	int pos;//��Ч�ı���ʼ��λ�ã������ڿ���ǩ����
	int line;//��ǩ���������������ж������Ƿ���ͬһ��
	CharString str;//��ǩ���ı��������ж�ƥ��
	static const int TITLE = 2;//����
	static const int SOURCE = 3;//��Դ
	static const int TIME = 4;//ʱ��
	static const int BODY = 5;//����
	static const int PARA = 6;//����
	static const int LINK = 7;//���ӣ����ڶ���������
	static const int NONSENSE = 8;//��ȫû��
	static const int IMG = 9;//ͼƬ�������<p>��ǩ�����Ϊ</p>����Ҫ�����ų�
	static const int BR = 10;//���з�����Ҫָ������
	static const int DIV = 11;//�������ĵ�DIV
	static const int SPAN = 12;//�������ĵ�span
	static const int END = 13;//���Ľ���
	static const int STRONG = 14;//�Ӵ�С����
	static const int FONT = 15;//����
	static const int B = 16;//�����ı�
	static const int STYLE = 17;//style sheet
	static const int OUTMAIN = 18;//�����Ŀ�ʼ�������ⲿ
	static const int ITALIC = 19;//б��
	static const int PARAM = 20;//����������գ���ָ������
	static const int TEXTAREA = 21;//textarea�Ŀ�ʼ�ͽ���
	static const int EMBED = 22;
	static const int VIDEOSOURCE = 23;//��Ƶ,���ڷ������г��֣���Ҫ���⴦��
	static const int NOTE = 24;//ע��
	static const int LIST = 25;//�б�
	Label(CharString& s,int t,int p,int l):str(s),type(t),pos(p),line(l){}
	Label(){}
	void changePos(int pos) { this->pos = pos; }
	void changeline(int line) { this->line = line; }
};

//���Źؼ���Ϣ
class NewsInfo {
public:
	CharString filename;
	CharString title;
	CharString source;
	CharString time;
	CharString body;//����
	NewsInfo(){}
	NewsInfo(const CharString& f,const CharString& tit,const CharString& s,
		const CharString& tim,const CharString& b):filename(f),title(tit),
		source(s),time(tim),body(b){}
	friend ostream& operator<<(ostream& out, const NewsInfo& n);
};

//���ļ���Ϊfilename���ļ�����ȡ�ؼ���Ϣ
//�洢��newsinfo�У��������output�ļ�
NewsInfo extractInfo(const string& filename);

int judgeTypeBeforeMain(const CharString& labelstr);//���Ŀ�ʼǰ��ǩ�ж�

int judgeTypeInMain(const CharString& labelstr);//�������жϱ�ǩ����

int judgeTypeBetweenMain(const CharString& labelstr);//�������жϱ�ǩ����

int judgeTypeInTextarea(const CharString& labelstr);//textarea���������ģ��жϱ�ǩ����

bool match(CharString& labelstart, CharString& labelend);//�жϿ��ձ�ǩ�Ƿ�ƥ��


#endif