// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Core.h"

extern "C" CORE_API int get_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	core c;
	char* words_new[10010];
	for (int i = 0; i < 10010; i++)
	{
		words_new[i] = (char*)malloc(2048 * sizeof(char));
	}
	int check = check_words(words, words_new, len);
	switch (check)
	{
	case 0:
		break;
	case -1:
		throw std::invalid_argument("Core: empty string in words");
		break;
	case -2:
		throw std::invalid_argument("Core: invalid char in words");
		break;
	case -3:
		throw std::invalid_argument("Core: too much words");
		break;
	case -4:
		throw std::invalid_argument("Core: not enough words");
		break;
	}
	return c.get_chain_word(words_new, len, result, head, tail, enable_loop);
}
extern "C" CORE_API int get_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	core c;
	//
	char* words_new[10010];
	for (int i = 0; i < 10010; i++)
	{
		words_new[i] = (char*)malloc(2048 * sizeof(char));
	}
	int check = check_words(words, words_new, len);
	switch (check)
	{
	case 0:
		break;
	case -1:
		throw std::invalid_argument("Core: empty string in words");
		break;
	case -2:
		throw std::invalid_argument("Core: invalid char in words");
		break;
	case -3:
		throw std::invalid_argument("Core: too much words");
		break;
	case -4:
		throw std::invalid_argument("Core: not enough words");
		break;
	}
	return c.get_chain_char(words_new, len, result, head, tail, enable_loop);
}
int check_words(char * words[], char* words_new[], int len)
{
	try
	{
		if (len > 10000)
			return -3; // too much words
		else if (len <= 1)
			return -4;
		for (int i = 0; i < len; i++)
		{
			int sl = strlen(words[i]);
			if (sl == 0)
				return -1; // empty string
			for (int j = 0; j < sl; j++)
			{
				if (!isalpha(words[i][j]))
					return -2; //invalid char
				else
				{
					words_new[i][j] = tolower(words[i][j]);
				}
			}
			words_new[i][sl] = '\0';
		}
		return 0;
	}
	catch (...)
	{
		throw std::runtime_error("Core: words invalid");
	}

}