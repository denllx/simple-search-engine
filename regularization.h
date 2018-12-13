/*
	对标签中的文本进行规范化
*/

#ifndef REGULARIZATION_H
#define REGULARIZATION_H

#include "CharString.h"

void titleRegularize(CharString& str);
void timeRegularize(CharString& str);
CharString extractSourceSuffix(CharString& time);
void translate(CharString& str);

#endif