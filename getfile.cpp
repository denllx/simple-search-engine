#include "getfile.h"
#include <direct.h>

using namespace std;

//path是input文件夹绝对路径
//files是所有input目录下的文件绝对路径
void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))//是子目录：递归查找
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else//不是子目录：直接加入列表
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//获取子目录的绝对路径名
//suffix是相对路径，如\input,\dic
void getSubDir(string& subDir,string suffix) {
	char szModuleFilePath[MAX_PATH];
	char SaveResult[MAX_PATH];
	int n = GetModuleFileNameA(0, szModuleFilePath, MAX_PATH); //exe文件路径
	szModuleFilePath[strrchr(szModuleFilePath, '\\') - szModuleFilePath + 1] = 0;//去掉.exe
	strcpy_s(SaveResult, szModuleFilePath);
	strcat_s(SaveResult, suffix.c_str());//在当前路径后添加自路径
	subDir = SaveResult;
}


//inputname:输入文件名
//suffix:后缀，为.info或.txt
const char* getOutputName(const string& dir,int ID,const string& suffix) {
	CharString outputname = dir.c_str();
	//新建output文件夹
	outputname.concat("output\\");
	_mkdir(outputname.c_str());
	char numstr[10];
	itoa(ID, numstr, 10);
	outputname.concat(numstr);
	outputname.concat(suffix.c_str());
	return outputname.c_str();
}

//输入inputname=xxxx/input/234.html
//返回dir=xxxx
//num=234
void getprefix(const string& inputname, CharString& dir,int& num) {
	CharString str = inputname.c_str();
	int index1 = str.indexOf("input");
	int index2 = str.indexOf(".html");
	CharString valid;
	str.substring(index1 + 6, index2 - index1 - 5, valid);//数字部分
	CharString tmp;
	str.substring(1, index1 - 1, tmp);
	dir = tmp;
	num = atoi(valid.c_str());
}
