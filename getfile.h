/*
*��ȡinput�ļ���������html���ļ���
*����html�ļ��е�html���
*���������ļ�������Ӧ������ļ���
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