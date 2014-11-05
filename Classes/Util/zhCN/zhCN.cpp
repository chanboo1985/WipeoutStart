#include "zhCN.h"

//把中文字符串转成cocos2dx可以显示的中文字符串
string parseStr(const char *wordId)
{
	auto txt_map = txt_vec.at(0).asValueMap();
	string ret = txt_map.at(wordId).asString();
	return ret;
}