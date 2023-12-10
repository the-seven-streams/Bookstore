#include <bits/stdc++.h>
#ifndef PROCESSTXT_HPP
#define PROCESSTXT_HPP
// 处理文件信息。以空格为标志返回第一个词。删除行首、行末空格。
std::string ProcessTxt(std::string &);
// 处理关键词，以竖线为标志，返回第一个词。删除行首、行末空格。
std::string ProcessKey(std::string &);
#endif