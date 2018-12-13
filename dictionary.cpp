#include "dictionary.h"
#include "getfile.h"
#include <vector>
#include <string>
using namespace std;

void loadDictionary(string filename, HashTable& dic) {
	ifstream infile;
	infile.open(filename.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������
	string s;
	while (infile >> s) {
		int len = s.size();
		char* copy = new char[len + 1];
		for (int i = 0; i < len; ++i) copy[i] = s[i];//���
		copy[len] = '\0';
		dic.insert(copy);
	}
	infile.close();//�ر��ļ�
}

void initDictionary(HashTable& dic,HashTable& stop) {
	//����ʿ�
	string dicdir;
	getSubDir(dicdir, "\dic");
	vector<string> files;
	getFiles(dicdir, files);

	cout << "��ʼ�������Ĵʿ�..." << endl;
	loadDictionary(files[0], dic);
	cout << "���Ĵʿ��������!��" <<dic.size()<<"���ʱ���¼"<< endl;

	cout << "��ʼ����ֹͣ�ʿ�..." << endl;
	loadDictionary(files[1], stop);
	cout << "ֹͣ�ʿ�������ϣ���" << stop.size() << "��ֹͣ�ʱ���¼" << endl;
	//������ʼ������...
}

void update(const char* filename, vector<CharString>& newWords) {
	freopen(filename, "a", stdout);
	for (auto newWord : newWords) cout << newWord << endl;
	freopen("CON", "w", stdout);//�ض��򵽿���̨
}

//�ִʽ������´�newWords��ӵ��ļ�
void updateDictionary(vector<CharString>& newWords,vector<CharString>& newStops) {
	string dicdir;
	getSubDir(dicdir, "\dic");
	vector<string> files;
	getFiles(dicdir, files);
	//�´�
	const char* dicname = files[0].c_str();
	update(dicname, newWords);
	//ͣ�ô�
	const char* stopname = files[1].c_str();
	update(stopname, newStops);
}