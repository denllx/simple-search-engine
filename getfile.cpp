#include "getfile.h"
#include <direct.h>

using namespace std;

//path��input�ļ��о���·��
//files������inputĿ¼�µ��ļ�����·��
void getFiles(string path, vector<string>& files)
{
	//�ļ����  
	intptr_t hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))//����Ŀ¼���ݹ����
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else//������Ŀ¼��ֱ�Ӽ����б�
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//��ȡ��Ŀ¼�ľ���·����
//suffix�����·������\input,\dic
void getSubDir(string& subDir,string suffix) {
	char szModuleFilePath[MAX_PATH];
	char SaveResult[MAX_PATH];
	int n = GetModuleFileNameA(0, szModuleFilePath, MAX_PATH); //exe�ļ�·��
	szModuleFilePath[strrchr(szModuleFilePath, '\\') - szModuleFilePath + 1] = 0;//ȥ��.exe
	strcpy_s(SaveResult, szModuleFilePath);
	strcat_s(SaveResult, suffix.c_str());//�ڵ�ǰ·���������·��
	subDir = SaveResult;
}


//inputname:�����ļ���
//suffix:��׺��Ϊ.info��.txt
const char* getOutputName(const string& dir,int ID,const string& suffix) {
	CharString outputname = dir.c_str();
	//�½�output�ļ���
	outputname.concat("output\\");
	_mkdir(outputname.c_str());
	char numstr[10];
	itoa(ID, numstr, 10);
	outputname.concat(numstr);
	outputname.concat(suffix.c_str());
	return outputname.c_str();
}

//����inputname=xxxx/input/234.html
//����dir=xxxx
//num=234
void getprefix(const string& inputname, CharString& dir,int& num) {
	CharString str = inputname.c_str();
	int index1 = str.indexOf("input");
	int index2 = str.indexOf(".html");
	CharString valid;
	str.substring(index1 + 6, index2 - index1 - 5, valid);//���ֲ���
	CharString tmp;
	str.substring(1, index1 - 1, tmp);
	dir = tmp;
	num = atoi(valid.c_str());
}
