#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

#define MAXSIZE 10000

template<typename T>
class Stack {
	T* base,*up;
	int stacksize;
public:
	Stack();
	void push(T e);
	void pop();
	T& top();
	bool empty();
	int size();
	~Stack();
};

template<typename T>
Stack<T>::Stack() {
	stacksize = MAXSIZE;
	base = nullptr;
	base = new T[stacksize];
	if (!base) {
		cout << "Õ»¿Õ¼ä·ÖÅäÊ§°Ü£¡";
		return;
	}
	up = base;
}

template<typename T>
Stack<T>::~Stack() {
	if (base) {
		delete [] base;
	}
}

template<typename T>
void Stack<T>::push(T e) {
	if (up- base >= stacksize) {
		cout << "Õ»ÒÑÂú,²»ÄÜÑ¹Õ»£¡";
		return;
	}
	*up++ = e;
}

template<typename T>
void Stack<T>::pop() {
	if (up == base) {
		cout << "Õ»ÒÑ¿Õ£¬²»ÄÜÍËÕ»£¡";
		return;
	}
	up--;
}

template<typename T>
T& Stack<T>::top() {
	return *(up - 1);
}

template<typename T>
bool Stack<T>::empty() {
	return up == base;
}

template<typename T>
int Stack<T>::size() {
	return up - base;
}

#endif