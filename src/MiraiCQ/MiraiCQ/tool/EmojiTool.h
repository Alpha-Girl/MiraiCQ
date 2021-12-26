#pragma once

#include <string>

class EmojiTool
{
public:
	/*
	* ���������ַ����е� emoji תΪ cq emoji ��
	* ����`str`��Ҫת�����ַ���
	* ����ֵ��ת������ַ���
	*/
	static std::string escape_cq_emoji(const std::string& str);
	/*
	* ���������ַ����е� cq emoji �� תΪ emoji 
	* ����`str`��Ҫת�����ַ���
	* ����ֵ��ת������ַ���
	*/
	static std::string unescape_cq_emoji(const std::string& str);

private:
	EmojiTool();
};

