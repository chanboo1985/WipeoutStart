#include "zhCN.h"

//�������ַ���ת��cocos2dx������ʾ�������ַ���
string parseStr(const char *wordId)
{
	auto txt_map = txt_vec.at(0).asValueMap();
	string ret = txt_map.at(wordId).asString();
	return ret;
}