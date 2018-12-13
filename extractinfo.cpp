#include "extractinfo.h"
#include "Stack.h"
#include "regularization.h"
#include <string>


//�����Ŀ�ʼ֮ǰ�жϱ��⣬ʱ�䣬��Դ�����Ŀ�ʼ
int judgeTypeBeforeMain(const CharString& labelstr) {
	//����
	if (labelstr.indexOf("<h1")
		|| labelstr.indexOf("/h1>")
		|| labelstr.indexOf("h1/>")) {
		return Label::TITLE;
	}
	//ʱ��
	if (labelstr.indexOf("post_time_source")
		|| labelstr.indexOf("ep-time")
		|| labelstr.indexOf("ptime")
		||labelstr.indexOf("class=\"time\"")) {
		return Label::TIME;
	}
	//��Դ
	if (labelstr.indexOf("id=\"ne_article_source\"")) {
		return Label::SOURCE;
	}
	//���Ŀ�ʼ���ڴ󲿷���ҳ����post_text��С������endText����endtext
	if (labelstr.indexOf("post_text")
		|| labelstr.indexOf("endText")
		|| labelstr.indexOf("end-text")) {
		return Label::BODY;
	}
	//����������֮���������Ϣ
	return Label::NONSENSE;
}

//�������ڲ��жϱ�ǩ���ͣ�ֻ��Ҫʶ�����õ���Ϣ�����ͳһ����ΪNONSENSE
int judgeTypeInMain(const CharString& labelstr) {
	//ͼƬ
	if (labelstr.indexOf("<img")) {
		return Label::IMG;
	}
	//���з�
	if (labelstr.indexOf("<br")) {
		return Label::BR;
	}
	//����
	if (labelstr.indexOf("/font")
		|| labelstr.indexOf("<font>")) {//���쳣��ҳ����<font>��Ϊ���俪ͷ
		return Label::FONT;
	}
	if (labelstr.indexOf("/style")) {
		return Label::STYLE;
	}
	//�Ӵ�С����
	if (labelstr.indexOf("<strong")
		|| labelstr.indexOf("strong>")) {
		return Label::STRONG;
	}
	//���Ľ�����һ���ԡ����α༭������Ϊ��־
	if (labelstr.indexOf("ep-editor")) {
		return Label::END;
	}
	//�����ı�
	if (labelstr.indexOf("<b>")
		|| labelstr.indexOf("</b>")) {
		return Label::B;
	}
	//�б�
	if (labelstr.indexOf("<li>")
		|| labelstr.indexOf("</li>")) {
		return Label::LIST;
	}
	//post_text��ķ����Ĳ���
	if (labelstr.indexOf("/div>")
		|| labelstr.indexOf("<div")) {
		return Label::DIV;
	}
	if (labelstr.indexOf("<span")
		|| labelstr.indexOf("span>")) {
		return Label::SPAN;
	}
	//����
	if (labelstr.indexOf("<p")
		|| labelstr.indexOf("p>")) {
		return Label::PARA;
	}
	//����
	if (labelstr.indexOf("<a")) {
		return Label::LINK;
	}
	//б��
	if (labelstr.indexOf("<i>")
		|| labelstr.indexOf("/i>")) {
		return Label::ITALIC;
	}

	return Label::NONSENSE;
}

//�������ڲ��ķ����Ĳ��֣���ǩֻ���ж��Ƿ�ƥ��
//��ƥ�䣬��ջ
//��ƥ�䣬��ջ�ٵ�ջ����Ϊ�ⰵʾһ������ǩû�ж�Ӧ�ıȱ�ǩ��
//���ڱ����������յı�ǩ��img,������ջ
bool match(CharString& startlabel, CharString& endlabel) {
	//startlabel:<div...>��<i>
	//endlabel:<.../div>��</i>
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

//���Ŀ�ʼ��ķ����Ĳ���
int judgeTypeBetweenMain(const CharString& labelstr) {
	//����������յı�ǩ
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
	//��Ҫֱ����������ǩ
	if (labelstr.indexOf("<!-")) {
		return Label::NOTE;
	}
	//-----�ı����ʵ�ת��-----
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

//textarea�ڲ���ǩ�����ж�
//ֻ���ж�<p></p>֮������ݺ�</textarea>������־
int judgeTypeInTextarea(const CharString& labelstr) {
	if (labelstr.indexOf("<p")
		|| labelstr.indexOf("p>")
		||labelstr.indexOf("pre>")) {
		return Label::PARA;
	}
	if (labelstr.indexOf("textarea")) {
		return Label::TEXTAREA;//textarea����
	}
	return Label::NONSENSE;

}



//����html�ļ������ؼ���Ϣ������NewsInfo���з��أ����������Ӧ�ļ���
NewsInfo extractInfo(const string& filename) {
	CharString content, lastcontent;//���ж��룬��������һ�е�����
	CharString title, time, source, body;
	Stack<Label> sLabel;
	const int INMAIN = 0, INTEXTAREA = 1, OUTOFMAIN = 2;//�����ڲ���textarea�ڲ����������ڲ��������Ŀ�ʼ��
	bool mainStart = false;//�����Ƿ�ʼ
	int mainStatus = OUTOFMAIN;
	bool inPara = false;//�����ڲ������ɸ�����
	CharString tmp;

	ifstream infile;
	infile.open(filename.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
	string s;
	int cnt = 0;
	int end = 0;
	while (getline(infile, s))
	{
		end = 0;//�Ƿ񵽴����Ľ�����
		cnt++;
		if (cnt == 859) {
			cout << "";
		}
		content.assign(s.c_str());
		for (int i = 1; i <= content.size(); ++i) {
			if (content[i] != '<')  continue;
			int index = content.indexOf(">", i);
			CharString labelstr;//��ǩ�е��ı��������б��ǩ��type��status
			content.substring(i, index - i + 1, labelstr);
			//�жϱ�ǩ����
			int slashIndex = labelstr.indexOf("</") + labelstr.indexOf("/>");
			int type;

			if (slashIndex == 0) {//����ǩ
				if (!mainStart) {//���Ŀ�ʼǰ
					type = judgeTypeBeforeMain(labelstr);
					if (type == Label::BODY) {
						mainStart = true;//���Ŀ�ʼ�����½��������ڲ�
						mainStatus = INMAIN;
					}
					if (type == Label::NONSENSE) continue;
				}
				else if (mainStatus == INMAIN) {//������
					type = judgeTypeInMain(labelstr);
					//------�ı����ʵ�ת��------
					if (type == Label::END) {//���Ľ���
						end = 1;
					}
					else if (type == Label::DIV) {//���Ŀ�ʼ��ķ����Ĳ��ֵĿ�ʼ
						mainStatus = OUTOFMAIN;
						inPara = false;
						sLabel.push(Label(labelstr, Label::OUTMAIN, index + 1, cnt));
						continue;
					}
					else if (type == Label::PARA) inPara = true;//���俪ʼ
					//------�ı������Ե��ж�-------
					else if (type == Label::NONSENSE) {//�����е�û�ö���:��ջ����ǩ����ʼλ���޸ĵ���ǰλ�ã���ʾ֮ǰ���ַ���������Ч��
						//if (inPara) {
						if (!sLabel.empty()) {
							sLabel.top().changeline(cnt);
							sLabel.top().changePos(index + 1);
						}
						//}
						continue;
					}
					else if ((type == Label::LINK) && !inPara) continue;//���ڶ����ڵ����ӡ��б��޳�
					if (!sLabel.empty()&&inPara&&
						(type == Label::LINK 
						|| type == Label::B 
						|| type == Label::FONT
						||type==Label::STRONG)){//������λ�ڱ�ǩ֮�������
						int start = sLabel.top().pos;
						int line = sLabel.top().line;
						if (line + 2 > cnt) {
							if (line + 1 == cnt) start = 1;//����ǩ����һ�У��ı��ͱձ�ǩ��ͬһ��
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
				else if (mainStatus == OUTOFMAIN) {//���Ŀ�ʼ���Է�end-text��ͷ�ķ����Ĳ���
					type = judgeTypeBetweenMain(labelstr);
					//-----�ı����ʵ�ת��-----
					if (type == Label::TEXTAREA) {
						mainStatus = INTEXTAREA;
					}
					else if (type == Label::END) {
						end = 1;
					}
					//����������ջ�ע��
					else if (type == Label::LINK
							||type==Label::NOTE
							||type==Label::VIDEOSOURCE) continue;//����ջ��typeȫ��OUTMAIN,��ʶ�䲻��������
				}
				else {//mainstatus=intextarea
					type = judgeTypeInTextarea(labelstr);
					if (type == Label::NONSENSE) continue;
				}
				sLabel.push(Label(labelstr, type, index + 1, cnt));
			}
			else {//�ձ�ǩ
				if (!mainStart) {//������δ��ʼ�������Ǳ��⡢ʱ�䡢��Դ
					type = judgeTypeBeforeMain(labelstr);
					if (type == Label::TITLE) {//����
						if (!sLabel.empty()) {
							int start = sLabel.top().pos;
							int length = i - start;
							content.substring(start, length, title);
							sLabel.pop();
						}
					}
					else if (!sLabel.empty()) {
						int toptype = sLabel.top().type;
						if (toptype == Label::SOURCE) {//��Դ
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line != cnt) start = 1;
							int length = i - start;
							content.substring(start, length, source);
							sLabel.pop();
						}
						if (toptype == Label::TIME) {//ʱ��
							int start = sLabel.top().pos;
							int line = sLabel.top().line;
							if (line != cnt) start = 1;
							int length = i - start;
							content.substring(start, length, time);
							CharString sourceSuffix = extractSourceSuffix(time);//���ܴ��ڵ���Դ��׺���羭�ù۲챨��������
							timeRegularize(time);
							if (!sourceSuffix.empty()) source.concat(sourceSuffix);
							sLabel.pop();
						}
					}
				}
				else if (mainStatus == INMAIN) {//���Ĳ���
					type = judgeTypeInMain(labelstr);
					//-------�ı���Ч��-------
					if (type == Label::IMG 
						|| type == Label::BR 
						|| (type == Label::DIV&&inPara) 
						|| type == Label::SPAN
						|| type == Label::STYLE) {//�����ı�
						if (!sLabel.empty()) {
							sLabel.top().changePos(index + 1);
							sLabel.top().changeline(cnt);
							continue;
						}
					}
					else if ((type == Label::STRONG 
							|| type == Label::B 
							|| type == Label::ITALIC)
							||type==Label::LIST) {//�����ı���С����/����/б��/�б�
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
					else if (!sLabel.empty()) {//�޷��ж��Ƿ����õıձ�ǩ
						int toptype = sLabel.top().type;
						if (toptype == Label::PARA) {//����Ŀ�ʼ
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
				else if (mainStatus == OUTOFMAIN) {//�����ڷ����Ĳ���
					type = judgeTypeBetweenMain(labelstr);
					//-----�ı����ʵ�ת��-----
					if (type == Label::END) {//���Ŀ����������У�Ҳ�����ڷ������н���
						end = 1;
					}
					//�����������
					else if (type == Label::BR 
							|| type == Label::IMG 
							|| type == Label::PARAM
							||type==Label::EMBED
							||type==Label::NOTE) continue;
					if (!sLabel.empty()) {
						bool isMatch = match(sLabel.top().str, labelstr);
						//��ջ
						sLabel.pop();
						if (!isMatch) sLabel.pop();//�п��ޱգ��ٴε�ջ
						if (!sLabel.empty() && sLabel.top().type != Label::OUTMAIN) {//���½��������ڲ�
							mainStatus = INMAIN;
						}
					}
				}
				else {//mainstatus=intextarea
					type = judgeTypeInTextarea(labelstr);
					//�ı����ʵ�ת��
					if (type == Label::TEXTAREA) mainStatus = OUTOFMAIN;
					//�ı���Ч��
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
		lastcontent.assign(content);//��¼��һ�����ݣ���ֹ���ݷ�ɢ�ڲ�ͬ��
	}
	infile.close();             //�ر��ļ�������
	if (source.empty()) source = "��Դδ֪";
	if (time.empty()) time = "ʱ��δ֪";
	NewsInfo info(filename.c_str(), title, source, time, body);
	return info;
}

ostream& operator<<(ostream& out, const NewsInfo& info) {
	out << info.title << endl << info.source << endl << info.time << endl << info.body << endl;
	return out;
}