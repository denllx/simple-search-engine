/*
*从网页中解析出关键信息
*/
#ifndef EXTRACTINFO_H
#define EXTRACTINFO_H

#include "CharString.h"
#include "getfile.h"

//html标签
class Label {
public:
	int type;//标签的类型：以下五种
	int pos;//有效文本开始的位置，仅对于开标签设置
	int line;//标签所在行数，用于判定开闭是否在同一行
	CharString str;//标签的文本，用于判断匹配
	static const int TITLE = 2;//标题
	static const int SOURCE = 3;//来源
	static const int TIME = 4;//时间
	static const int BODY = 5;//正文
	static const int PARA = 6;//段落
	static const int LINK = 7;//链接，仅在段落中有用
	static const int NONSENSE = 8;//完全没用
	static const int IMG = 9;//图片，会跟在<p>标签后被误解为</p>，需要单独排除
	static const int BR = 10;//换行符，需要指定跳过
	static const int DIV = 11;//不是正文的DIV
	static const int SPAN = 12;//不是正文的span
	static const int END = 13;//正文结束
	static const int STRONG = 14;//加粗小标题
	static const int FONT = 15;//字体
	static const int B = 16;//粗体文本
	static const int STYLE = 17;//style sheet
	static const int OUTMAIN = 18;//在正文开始后正文外部
	static const int ITALIC = 19;//斜体
	static const int PARAM = 20;//自身包含开闭，需指定跳过
	static const int TEXTAREA = 21;//textarea的开始和结束
	static const int EMBED = 22;
	static const int VIDEOSOURCE = 23;//视频,常在非正文中出现，需要特殊处理
	static const int NOTE = 24;//注释
	static const int LIST = 25;//列表
	Label(CharString& s,int t,int p,int l):str(s),type(t),pos(p),line(l){}
	Label(){}
	void changePos(int pos) { this->pos = pos; }
	void changeline(int line) { this->line = line; }
};

//新闻关键信息
class NewsInfo {
public:
	CharString filename;
	CharString title;
	CharString source;
	CharString time;
	CharString body;//正文
	NewsInfo(){}
	NewsInfo(const CharString& f,const CharString& tit,const CharString& s,
		const CharString& tim,const CharString& b):filename(f),title(tit),
		source(s),time(tim),body(b){}
	friend ostream& operator<<(ostream& out, const NewsInfo& n);
};

//从文件名为filename的文件中提取关键信息
//存储到newsinfo中，并输出到output文件
NewsInfo extractInfo(const string& filename);

int judgeTypeBeforeMain(const CharString& labelstr);//正文开始前标签判断

int judgeTypeInMain(const CharString& labelstr);//正文中判断标签类型

int judgeTypeBetweenMain(const CharString& labelstr);//非正文判断标签类型

int judgeTypeInTextarea(const CharString& labelstr);//textarea（特殊正文）判断标签类型

bool match(CharString& labelstart, CharString& labelend);//判断开闭标签是否匹配


#endif