#ifndef __ZH_CN_H__
#define __ZH_CN_H__
#include <string>
#include <cocos2d.h>
USING_NS_CC;
using namespace std;

static ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("zhCN.xml");

string parseStr(const char *wordId);

#endif