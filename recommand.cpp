#include <cmath>
#include "recommand.h"
#include "getfile.h"

vector<int> recommand(char* title,double** score,int totalArticles,int totalWords,map<CharString,int>& title2ID) {
	if (title2ID.find(title) == title2ID.end()) return vector<int>(0);
	return _recommand(title2ID[title], score, totalArticles, totalWords);
}

/*
	����ÿ�к͵�ID�еľ���
	ѡȡ��С��ǰ3�����
*/
vector<int> _recommand(int ID, double** score,int totalArticles,int totalWords) {
	vector<int> ret;
	//freopen("output.txt", "w", stdout);
	//�������ƶ�����3ƪ����
	double max1=-2, max2=-2, max3 = -2,max4=-2,max5=-2;
	int idx1 = -1, idx2 = -1, idx3 = -1,idx4=-1,idx5=-1;
	//�Ե�ǰÿƪ���£������������ƶ�
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

//�������ƶ�
double cossim(double** score, int col1, int col2,int lines) {//lines��score������
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
	tf[i][j]=�ĵ�j�е���i���ִ���/�ĵ�j���ܴ���
	idf[i][j]=���ļ�����+1��/���õ����ڶ���ƪ�ļ��г��ֹ�+1��
	score[i][j]=tf[i][j]*idf[i][j]
	iΪ���ʱ��������Ⱥ�˳��
	jΪ�ĵ����
*/
double tfIdf(WordNode* word, FileNode* file,int totalArticles,int* id2wordnum) {
	double idf = (1.0 + totalArticles) / (1.0 + word->articles);
	//cout << "����Ϊ" << word->content << ",����IDΪ" << file->ID << endl;
	//cout << "����" << totalArticles << " ƪ����,��" << word->articles << "ƪ�����г��ֹ�" << endl;
	//cout << "idf=" << idf << endl;
	//cout << "�����й���" << id2wordnum[file->ID] << "���ʣ��ôʳ���" << file->times << "��" << endl;
	double tf = (file->times+0.0) / (0.0+id2wordnum[file->ID]);
	//cout << "tf=" << tf << endl;
	//cout << endl;
	return idf * tf;
}

/*
	tree:�����ĵ�����	
	totalArticles:����������һ��Ϊ780
	score:�����,shape=(num_of_vocab,totalArticles)
	ʹ��tf-idf��������
	Ĭ���ĵ��ı���Ǵ�0��totalArticles-1��
*/
void scoreMatrix(BalanceBinaryTree* tree, int totalArticles, double** score,int* id2wordnum) {
	WordNode* root = tree->root;
	int cnt = 0;
	_scorematrix(root, totalArticles, score, id2wordnum, cnt);//�Ӹ��ڵ㿪ʼ���score���������score[0]
	//outputScoreMatrix(score, totalArticles, cnt);
}

//node�ǵ�ǰ�ĵ��ʽڵ�
//cnt��ʾnode��ƽ��������е�cnt�������ʵ��Ľڵ�
//cnt��score�е���iһ��
void _scorematrix(WordNode* node, int totalArticles, double** score, int* id2wordnum, int& cnt) {
	//��ǰ���score[cnt]
	//cnt++
	if (!node) return;
	FileNode* p = node->firstfile->head;
	while (p) {
		score[cnt][p->ID] = tfIdf(node, p, totalArticles, id2wordnum);
		p = p->next;
	}
	cnt++;
	//����������ʼ���score
	_scorematrix(node->left,totalArticles, score, id2wordnum, cnt);
	//����������ʼ���score
	_scorematrix(node->right, totalArticles, score, id2wordnum, cnt);
}

void outputScoreMatrix(double** score, int totalArticles, int totalWords) {
	//score:���־��� shape=(totalWords,totalArticles)
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

//���Ƽ������(id,����)��ʽ���
void outputRecommand(vector<vector<int>> ret,map<int,CharString>& ID2title) {
	string outputdir;
	getSubDir(outputdir, "\\");
	outputdir += "result2.txt";//������ض���result1.txt�ļ�
	//freopen(outputdir.c_str(), "w", stdout);
	const char* filename = outputdir.c_str();
	ofstream fout(filename);
	for (int i = 0, len = ret.size(); i < len; i++) {
		if (ret[i].empty()) {
			fout << "�����Ų������ݿ��У��޷��Ƽ���" << endl;
			continue;
		}
		for (int j = 0, len1 = ret[i].size(); j < len1; j++)
			fout << "("<<ret[i][j] << ","<<ID2title[ret[i][j]]<<")";
		fout << endl;
	}
	fout.close();
}