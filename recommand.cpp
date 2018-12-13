#include <cmath>
#include "recommand.h"
#include "getfile.h"

vector<int> recommand(char* title,double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID) {
	if (title2ID.find(title) == title2ID.end()) return vector<int>(0);
	return _recommand(title2ID[title], score, totalArticles, totalWords);
}

/*
	计算每列和第ID列的距离
	选取最小的前3个输出
*/
vector<int> _recommand(int ID, double** score,int totalArticles,int totalWords) {
	vector<int> ret;
	//freopen("output.txt", "w", stdout);
	//余弦相似度最大的3篇文章
	double max1=-2, max2=-2, max3 = -2,max4=-2,max5=-2;
	int idx1 = -1, idx2 = -1, idx3 = -1,idx4=-1,idx5=-1;
	//对当前每篇文章，计算余弦相似度
	for (int i = 0; i < totalArticles; i++) {
		if (i == ID) continue;
		double tmpcos = cossim(score, ID, i, totalWords);
		if (tmpcos > max1) {
			max1 = tmpcos;
			idx1 = i;
		}
		else if (tmpcos > max2) {
			max2 = tmpcos;
			idx2 = i;
		}
		else if (tmpcos > max3) {
			max3 = tmpcos;
			idx3 = i;
		}
		else if (tmpcos > max4) {
			max4 = tmpcos;
			idx4 = i;
		}
		else if (tmpcos > max5) {
			max5 = tmpcos;
			idx5 = i;
		}
	}
	if (idx1 != -1) ret.push_back(idx1);
	if (idx2 != -1) ret.push_back(idx2);
	if (idx3 != -1) ret.push_back(idx3);
	if (idx4 != -1) ret.push_back(idx4);
	if (idx5 != -1) ret.push_back(idx5);
	return ret;
}

//余弦相似度
double cossim(double** score, int col1, int col2,int lines) {//lines是score的行数
	double sq1 = 0, sq2 = 0;
	double cos = 0;
	for (int i = 0; i < lines; i++) {
		cos += score[i][col1] * score[i][col2];
		sq1 += score[i][col1] * score[i][col1];
		sq2 += score[i][col2] * score[i][col2];
	}
	return (cos+0.0) / (sqrt(sq1)*sqrt(sq2)+0.0);
}

/*
	tf[i][j]=文档j中单词i出现次数/文档j中总词数
	idf[i][j]=（文件总数+1）/（该单词在多少篇文件中出现过+1）
	score[i][j]=tf[i][j]*idf[i][j]
	i为单词被遍历的先后顺序
	j为文档编号
*/
double tfIdf(WordNode* word, FileNode* file,int totalArticles,int* id2wordnum) {
	double idf = (1.0 + totalArticles) / (1.0 + word->articles);
	//cout << "词语为" << word->content << ",文章ID为" << file->ID << endl;
	//cout << "共有" << totalArticles << " 篇文章,在" << word->articles << "篇文章中出现过" << endl;
	//cout << "idf=" << idf << endl;
	//cout << "文章中共有" << id2wordnum[file->ID] << "个词，该词出现" << file->times << "次" << endl;
	double tf = (file->times+0.0) / (0.0+id2wordnum[file->ID]);
	//cout << "tf=" << tf << endl;
	//cout << endl;
	return idf * tf;
}

/*
	tree:倒排文档索引	
	totalArticles:总文章数，一般为780
	score:待填充,shape=(num_of_vocab,totalArticles)
	使用tf-idf进行评分
	默认文档的编号是从0到totalArticles-1的
*/
void scoreMatrix(BalanceBinaryTree* tree, int totalArticles, double** score,int* id2wordnum) {
	WordNode* root = tree->root;
	int cnt = 0;
	_scorematrix(root, totalArticles, score, id2wordnum, cnt);//从根节点开始填充score，即先填充score[0]
	//outputScoreMatrix(score, totalArticles, cnt);
}

//node是当前的单词节点
//cnt表示node是平衡二叉树中第cnt个被访问到的节点
//cnt和score中的行i一致
void _scorematrix(WordNode* node, int totalArticles, double** score, int* id2wordnum, int& cnt) {
	//当前填充score[cnt]
	//cnt++
	if (!node) return;
	FileNode* p = node->firstfile->head;
	while (p) {
		score[cnt][p->ID] = tfIdf(node, p, totalArticles, id2wordnum);
		p = p->next;
	}
	cnt++;
	//从左子树开始填充score
	_scorematrix(node->left,totalArticles, score, id2wordnum, cnt);
	//从右子树开始填充score
	_scorematrix(node->right, totalArticles, score, id2wordnum, cnt);
}

void outputScoreMatrix(double** score, int totalArticles, int totalWords) {
	//score:评分矩阵 shape=(totalWords,totalArticles)
	for (int i = 0; i < totalWords; i++) {
		for (int j = 0; j < totalArticles; j++) {
			if (score[i][j] != 0) {
				cout << i<<" "<<j<<" "<<score[i][j] << " "<<endl;
			}
		}
		cout << endl;
	}
}


void runRecommand(double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID,map<int,CharString>& ID2title) {
	string inputdir;
	getSubDir(inputdir, "\\");
	inputdir += "query2.txt";
	//freopen(inputdir.c_str(), "r", stdin);
	ifstream fin(inputdir.c_str());
	char title[100];

	vector<vector<int>> ret;
	while (fin.getline(title,100)) {
		vector<int> tmp = recommand(title, score, totalArticles, totalWords,title2ID);
		ret.push_back(tmp);
	}
	fin.close();
	outputRecommand(ret,ID2title);
	
}

//将推荐结果以(id,标题)形式输出
void outputRecommand(vector<vector<int>> ret,map<int,CharString>& ID2title) {
	string outputdir;
	getSubDir(outputdir, "\\");
	outputdir += "result2.txt";//将输出重定向到result1.txt文件
	//freopen(outputdir.c_str(), "w", stdout);
	const char* filename = outputdir.c_str();
	ofstream fout(filename);
	for (int i = 0, len = ret.size(); i < len; i++) {
		if (ret[i].empty()) {
			fout << "该新闻不在数据库中，无法推荐！" << endl;
			continue;
		}
		for (int j = 0, len1 = ret[i].size(); j < len1; j++)
			fout << "("<<ret[i][j] << ","<<ID2title[ret[i][j]]<<")";
		fout << endl;
	}
	fout.close();
}