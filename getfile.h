/*
*获取input文件夹下所有html的文件名
*读入html文件中的html语句
*根据输入文件名求相应的输出文件名
*/

#ifndef GETFILE_H
#define GETFILE_H

#include <vector>
#include <iostream>
#include <io.h>
#include <direct.h>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include "CharString.h"

void getFiles(string path, vector<string>& files);
void getSubDir(string& subDir,string suffix);
void getprefix(const string& inputname, CharString& dir, int& num);
const char* getOutputName(const string& dir,int ID,const string& suffix);

#endif