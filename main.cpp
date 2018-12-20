#include "news_system_ui.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QUrl>
#include <iostream>
#include <QWebEngineView>
#include "CharString.h"
#include "BalanceBinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include "FileLink.h"
#include "getfile.h"
#include "query.h"
#include "recommand.h"
#include <time.h>
#include <vector>
#include <map>
#include <QMovie>
#include <QLabel>
#include "screen.h"


using namespace std;


void teststring() {
	CharString s("hello");
	CharString s1("hello");
	CharString s2("h");
	CharString s3("hello world");
	cout << (s < s1) << endl;
	cout << (s < s2) << endl;
	cout << (s < s3) << endl;

}

void testdelete() {
	int* a = new int[5];
	for (int i = 0; i < 5; i++) a[i] = i;
	delete[] a;
	for (int i = 0; i < 5; i++) cout << a[i] << endl;
}


/*
void testll() {
	CharString s1("1"), s2("2"), s3("3"),s4("4");
	WordNode* l1 = new WordNode(s4);
	l1->left = new WordNode(s2);
	l1->left->left = new WordNode(s1);
	l1->left->right = new WordNode(s3);
	BalanceBinaryTree tree(l1);
	//4(2(1,3))
	cout << "before rotation:" << endl;
	cout << "root height=" <<l1->height << endl;
	cout << "root left height=" << l1->left->height << endl;
	//cout << "root right height=" << l1->right->height << endl;
	WordNode* ret=tree._ll(tree.root);
	//2(1,3(4))
	cout << ret->content << " " << ret->left->content << " " << ret->right->content<<" "<<ret->right->left->content<<endl;
	cout << "after rotation" << endl;
	cout << "root height=" << ret->height << endl;
	cout << "root left height=" << ret->left->height << endl;
	cout << "root right height=" << ret->right->height << endl;

}

void testrr() {
	CharString s1("1"), s2("2"), s3("3"), s4("4");
	WordNode* l1 = new WordNode(s1);
	l1->right = new WordNode(s3);
	l1->right->left = new WordNode(s2);
	l1->right->right = new WordNode(s4);
	BalanceBinaryTree tree(l1);
	WordNode* root = tree._rr(tree.root);
	cout << root->content << endl;
	cout << root->left->content << endl;
	cout << root->right->content << endl;
	cout << root->left->right->content << endl;
}
*/

/*void testinsert() {
	BalanceBinaryTree* tree=new BalanceBinaryTree;
	srand(13);
	for (int i = 0; i < 100; i++) {
		int num = rand()%100;
		char c[10];
		itoa(num, c, 10);
		CharString s(c);
		tree->insert(tree->root,s);
	}
	tree->inorderTraversal(tree->root);
}*/

void testequal() {
	CharString s1("18");
	CharString s2("26");
	cout << (s2 < s1) << endl;
}


void testvector() {
	map<int, int> maps;
	for (int i = 0; i < 10; i++) {
		maps.insert(pair<int, int>(i, i));
	}
	vector<pair<int, int>> times(maps.begin(), maps.end());
	cout << times.size() << endl;
	vector<pair<int, int>> copy(times.begin(), times.begin() + 5);
}

void testmap() {
	map<int, int> id2times;
	id2times.insert(pair<int, int>(0, 1));
	id2times.insert(pair<int, int>(100, 2));
	cout << id2times[100] << endl;
	id2times[1]++;
	id2times[100]++;
	cout << id2times[1] << endl;
	cout << id2times[100] << endl;
}

void hello(double** a) {
	a[0][0] = 0.3;
}

void testmalloc() {
	double** a = new double*[10];
	for (int i = 0; i < 10; i++) a[i] = new double[10];
	hello(a);
}
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Screen w;
	w.show();
	return a.exec();
}

