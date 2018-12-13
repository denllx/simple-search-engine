#include "extractinfo.h"
#include "Stack.h"
#include "regularization.h"
#include <string>


//在正文开始之前判断标题，时间，来源，正文开始
int judgeTypeBeforeMain(const CharString& labelstr) {
	//标题
	if (labelstr.indexOf("<h1")
		|| labelstr.indexOf("/h1>")
		|| labelstr.indexOf("h1/>")) {
		return Label::TITLE;
	}
	//时间
	if (labelstr.indexOf("post_time_source")
		|| labelstr.indexOf("ep-time")
		|| labelstr.indexOf("ptime")
		||labelstr.indexOf("class=\"time\"")) {
		return Label::TIME;
	}
	//来源
	if (labelstr.indexOf("id=\"ne_article_source\"")) {
		return Label::SOURCE;
	}
	//正文开始，在大部分网页中是post_text，小部分是endText或者endtext
	if (labelstr.indexOf("post_text")
		|| labelstr.indexOf("endText")
		|| labelstr.indexOf("end-text")) {
		return Label::BODY;
	}
	//其他：正文之外的无用信息
	return Label::NONSENSE;
}

//在正文内部判断标签类型，只需要识别有用的信息，别的统一归类为NONSENSE
int judgeTypeInMain(const CharString& labelstr) {
	//图片
	if (labelstr.indexOf("<img")) {
		return Label::IMG;
	}
	//换行符
	if (labelstr.indexOf("<br")) {
		return Label::BR;
	}
	//字体
	if (labelstr.indexOf("/font")
		|| labelstr.indexOf("<font>")) {//在异常网页中以<font>作为段落开头
		return Label::FONT;
	}
	if (labelstr.indexOf("/style")) {
		return Label::STYLE;
	}
	//加粗小标题
	if (labelstr.indexOf("<strong")
		|| labelstr.indexOf("strong>")) {
		return Label::STRONG;
	}
	//正文结束，一般以“责任编辑”出现为标志
	if (labelstr.indexOf("ep-editor")) {
		return Label::END;
	}
	//粗体文本
	if (labelstr.indexOf("<b>")
		|| labelstr.indexOf("</b>")) {
		return Label::B;
	}
	//列表
	if (labelstr.indexOf("<li>")
		|| labelstr.indexOf("</li>")) {
		return Label::LIST;
	}
	//post_text里的非正文部分
	if (labelstr.indexOf("/div>")
		|| labelstr.indexOf("<div")) {
		return Label::DIV;
	}
	if (labelstr.indexOf("<span")
		|| labelstr.indexOf("span>")) {
		return Label::SPAN;
	}
	//段落
	if (labelstr.indexOf("<p")
		|| labelstr.indexOf("p>")) {
		return Label::PARA;
	}
	//链接
	if (labelstr.indexOf("<a")) {
		return Label::LINK;
	}
	//斜体
	if (labelstr.indexOf("<i>")
		|| labelstr.indexOf("/i>")) {
		return Label::ITALIC;
	}

	return Label::NONSENSE;
}

//在正文内部的非正文部分，标签只需判断是否匹配
//若匹配，弹栈
//不匹配，弹栈再弹栈（因为这暗示一个开标签没有对应的比标签）
//对于本身象征开闭的标签如img,不予入栈
bool match(CharString& startlabel, CharString& endlabel) {
	//startlabel:<div...>或<i>
	//endlabel:<.../div>或</i>
	int startindex1 = startlabel.indexOf(" ");
	int startindex2 = startlabel.indexOf(">");
	int startindex;
	if (startindex1 == 0) startindex = startindex2;
	else if (startindex2 == 0) startindex = startindex1;
	else startindex = min(startindex1, startindex2);
	int endindex = endlabel.indexOf("/");
	CharString substart, subend;
	startlabel.substring(2, startindex - 2, substart);
	endlabel.substring(endindex + 1, endlabel.size() - 1 - endindex, subend);
	return substart == subend;
}

//正文开始后的非正文部分
int judgeTypeBetweenMain(const CharString& labelstr) {
	//自身包含开闭的标签
	if (labelstr.indexOf("<img")) {
		return Label::IMG;
	}
	if (labelstr.indexOf("<br/>")) {
		return Label::BR;
	}
	if (labelstr.indexOf("<link")) {
		return Label::LINK;
	}
	if (labelstr.indexOf("<param")) {
		return Label::PARAM;
	}
	if (labelstr.indexOf("<embed")) {
		return Label::EMBED;
	}
	if (labelstr.indexOf("<source")) {
		return Label::VIDEOSOURCE;
	}
	//需要直接跳过：标签
	if (labelstr.indexOf("<!-")) {
		return Label::NOTE;
	}
	//-----文本性质的转移-----
	if (labelstr.indexOf("end-text")
		|| labelstr.indexOf("endText")) {
		return Label::BODY;
	}
	if (labelstr.indexOf("ep-editor")) {
		return Label::END;
	}
	//textarea
	if (labelstr.indexOf("textarea")) {
		return Label::TEXTAREA;
	}
	return Label::OUTMAIN;
}

//textarea内部标签类型判断
//只需判断<p></p>之间的内容和</textarea>结束标志
int judgeTypeInTextarea(const CharString& labelstr) {
	if (labelstr.indexOf("<p")
		|| labelstr.indexOf("p>")
		||labelstr.indexOf("pre>")) {
		return Label::PARA;
	}
	if (labelstr.indexOf("textarea")) {
		return Label::TEXTAREA;//textarea结束
	}
	return Label::NONSENSE;

}



//读入html文件，将关键信息保存在NewsInfo类中返回，并输出到对应文件名
NewsInfo extractInfo(const string& filename) {
	CharString content, lastcontent;//逐行读入，并缓存上一行的内容
	CharString title, time, source, body;
	Stack<Label> sLabel;
	const int INMAIN = 0, INTEXTAREA = 1, OUTOFMAIN = 2;//正文内部；textarea内部；非正文内部但在正文开始后
	bool mainStart = false;//正文是否开始
	int mainStatus = OUTOFMAIN;
	bool inPara = false;//正文内部有若干个段落
	CharString tmp;

	ifstream infile;
	infile.open(filename.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	string s;
	int cnt = 0;
	int end = 0;
	while (getline(infile, s))
	{
		end = 0;//是否到达正文结束处
		cnt++;
		if (cnt == 859) {
			cout << "";
		}
		content.assign(s.c_str());
		for (int i = 1; i <= content.size(); ++i) {
			if (content[i] != '<')  continue;
			int index = content.indexOf(">", i);
			CharString labelstr;//标签中的文本，用于判别标签的type和status
			content.substring(i, index - i + 1, labelstr);
			//判断标签开闭
			int slashIndex = labelstr.indexOf("</") + labelstr.indexOf("/>");
			int type;

			if (slashIndex == 0) {//开标签
				if (!mainStart) {//正文开始前
					type = judgeTypeBeforeMain(labelstr);
					if (type == Label::BODY) {
						mainStart = true;//正文开始或重新进入正文内部
						mainStatus = INMAIN;
					}
					if (type == Label::NONSENSE) continue;
				}
				else if (mainStatus == INMAIN) {//正文中
					type = judgeTypeInMain(labelstr);
					//------文本性质的转变------
					if (type == Label::END) {//正文结束
						end = 1;
					}
					else if (type == Label::DIV) {//正文开始后的非正文部分的开始
						mainStatus = OUTOFMAIN;
						inPara = false;
						sLabel.push(Label(labelstr, Label::OUTMAIN, index + 1, cnt));
						continue;
					}
					else if (type == Label::PARA) inPara = true;//段落开始
					//------文本有用性的判断-------
					else if (type == Label::NONSENSE) {//正文中的没用段落:将栈顶标签的起始位置修改到当前位置，表示之前的字符串都是无效的
						//if (inPara) {
						if (!sLabel.empty()) {
							sLabel.top().changeline(cnt);
							sLabel.top().changePos(index + 1);
						}
						//}
						continue;
					}
					else if ((type == Label::LINK) && !inPara) continue;//不在段落内的链接、列表被剔除
					if (!sLabel.empty()&&inPara&&
						(type == Label::LINK 
						|| type == Label::B 
						|| type == Label::FONT
						||type==Label::STRONG)){//段落内位于标签之间的文字
						int start = sLabel.top().pos;
						int line = sLabel.top().line;
						if (line + 2 > cnt) {
							if (line + 1 == cnt) start = 1;//开标签在上一行，文本和闭标签在同一行
							int length = i - start;
							CharString tmp;
							content.substring(start, length, tmp);
							tmp.trim();
							translate(tmp);
							body.concat(tmp);
						}
						else {
							body.concat(lastcontent);
						}
					}
				}
				else if (mainStatus == OUTOFMAIN) {//正文开始后以非end-text开头的非正文部分
					type = judgeTypeBetweenMain(labelstr);
					//-----文本性质的转换-----
					if (type == Label::TEXTAREA) {
						mainStatus = INTEXTAREA;
					}
					else if (type == Label::END) {
						end = 1;
					}
					//自身包含开闭或注释
					else if (type == Label::LINK
							||type==Label::NOTE
							||type==Label::VIDEOSOURCE) continue;//能入栈的type全是OUTMAIN,标识其不属于正文
				}
				else {//mainstatus=intextarea
					type = judgeTypeInTextarea(labelstr);
					if (type == Label::NONSENSE) continue;
				}
				sLabel.push(Label(labelstr, type, index + 1, cnt));
			}
			else {//闭标签
				if (!mainStart) {//正文尚未开始，可能是标题、时间、来源
					type = judgeTypeBeforeMain(labelstr);
					if (type == Label::TITLE) {//标题
						if (!sLabel.empty()) {
							int start = sLabel.top().pos;
							int length = i - start;
							content.substring(start, length, title);
							sLabel.pop();
						}
					}
					else if (!sLabel.empty()) {
						int toptype = sLabel.top().type;
						if (toptype == Label::SOURCE) {//来源
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line != cnt) start = 1;
							int length = i - start;
							content.substring(start, length, source);
							sLabel.pop();
						}
						if (toptype == Label::TIME) {//时间
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line != cnt) start = 1;
							int length = i - start;
							content.substring(start, length, time);
							CharString sourceSuffix = extractSourceSuffix(time);//可能存在的来源后缀，如经济观察报（北京）
							timeRegularize(time);
							if (!sourceSuffix.empty()) source.concat(sourceSuffix);
							sLabel.pop();
						}
					}
				}
				else if (mainStatus == INMAIN) {//正文部分
					type = judgeTypeInMain(labelstr);
					//-------文本有效性-------
					if (type == Label::IMG 
						|| type == Label::BR 
						|| (type == Label::DIV&&inPara) 
						|| type == Label::SPAN
						|| type == Label::STYLE) {//无用文本
						if (!sLabel.empty()) {
							sLabel.top().changePos(index + 1);
							sLabel.top().changeline(cnt);
							continue;
						}
					}
					else if ((type == Label::STRONG 
							|| type == Label::B 
							|| type == Label::ITALIC)
							||type==Label::LIST) {//有用文本：小标题/粗体/斜体/列表
						if (!sLabel.empty()) {
							int start = sLabel.top().pos;
							int length = i - start;
							CharString tmp;
							content.substring(start, length, tmp);
							tmp.trim();
							translate(tmp);
							if (!tmp.empty()) {
								body.concat(tmp);
								body.concat("\n");
							}
							sLabel.pop();
							if (inPara && !sLabel.empty()) {
								sLabel.top().changePos(index + 1);
								sLabel.top().changeline(cnt);
							}
						}
					}
					else if (!sLabel.empty()) {//无法判断是否有用的闭标签
						int toptype = sLabel.top().type;
						if (toptype == Label::PARA) {//段落的开始
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line + 2 > cnt) {
								if (line != cnt) start = 1;
								int length = i - start;
								CharString tmp;
								content.substring(start, length, tmp);
								tmp.trim();
								translate(tmp);
								body.concat(tmp);
							}
							else {
								lastcontent.trim();
								translate(lastcontent);
								body.concat(lastcontent);
							}
							if (type == Label::PARA) {
								inPara = false;
								if (i != start) body.append('\n');
							}
							sLabel.pop();
							if (!sLabel.empty()) {
								sLabel.top().changeline(cnt);
								sLabel.top().changePos(index + 1);
							}
						}
						if (toptype == Label::LINK&&!sLabel.empty()) {
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line + 2 > cnt) {
								if (line != cnt) start = 1;
								int length = i - start;
								CharString tmp;
								content.substring(start, length, tmp);
								tmp.trim();
								translate(tmp);
								body.concat(tmp);
							}
							else {
								lastcontent.trim();
								body.concat(lastcontent);
							}
							sLabel.pop();
							if (!sLabel.empty()) {
								sLabel.top().changePos(index + 1);
								sLabel.top().changeline(cnt);
							}
						}
						if (toptype == Label::FONT) {
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line + 2 > cnt) {
								if (line != cnt) start = 1;
								int length = i - start;
								CharString tmp;
								content.substring(start, length, tmp);
								tmp.trim();
								translate(tmp);
								body.concat(tmp);
							}
							else {
								lastcontent.trim();
								translate(tmp);
								body.concat(lastcontent);
							}
							sLabel.pop();
							sLabel.top().changePos(index + 1);
							sLabel.top().changeline(cnt);
						}
					}

				}
				else if (mainStatus == OUTOFMAIN) {//正文内非正文部分
					type = judgeTypeBetweenMain(labelstr);
					//-----文本性质的转移-----
					if (type == Label::END) {//正文可能在正文中，也可能在非正文中结束
						end = 1;
					}
					//自身包含开闭
					else if (type == Label::BR 
							|| type == Label::IMG 
							|| type == Label::PARAM
							||type==Label::EMBED
							||type==Label::NOTE) continue;
					if (!sLabel.empty()) {
						bool isMatch = match(sLabel.top().str, labelstr);
						//弹栈
						sLabel.pop();
						if (!isMatch) sLabel.pop();//有开无闭，再次弹栈
						if (!sLabel.empty() && sLabel.top().type != Label::OUTMAIN) {//重新进入正文内部
							mainStatus = INMAIN;
						}
					}
				}
				else {//mainstatus=intextarea
					type = judgeTypeInTextarea(labelstr);
					//文本性质的转移
					if (type == Label::TEXTAREA) mainStatus = OUTOFMAIN;
					//文本有效性
					else if (type == Label::PARA) {
						int start = sLabel.top().pos;
						int line = sLabel.top().line;
						if (line + 2 > cnt) {
							if (line != cnt) start = 1;
							int length = i - start;
							CharString tmp;
							content.substring(start, length, tmp);
							tmp.trim();
							translate(tmp);
							body.concat(tmp);
							if (!tmp.empty()) body.concat("\n");
						}
						else {
							lastcontent.trim();
							translate(tmp);
							body.concat(lastcontent);
							if (!lastcontent.empty()) body.concat("\n");
						}
						sLabel.pop();
						sLabel.top().changePos(index + 1);
						sLabel.top().changeline(cnt);
					}

				}
			}
		}
		if (end) break;
		lastcontent.assign(content);//记录上一行内容，防止内容分散在不同行
	}
	infile.close();             //关闭文件输入流
	if (source.empty()) source = "来源未知";
	if (time.empty()) time = "时间未知";
	NewsInfo info(filename.c_str(), title, source, time, body);
	return info;
}

ostream& operator<<(ostream& out, const NewsInfo& info) {
	out << info.title << endl << info.source << endl << info.time << endl << info.body << endl;
	return out;
}