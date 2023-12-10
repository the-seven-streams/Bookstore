#include<bits/stdc++.h>
#include"Processtxt.hpp"
#ifndef CHECK_HPP
#define CHECK_HPP
//该文件是为了检查输入内容的合法性。
//所有的数字记作number，在之后的表示中将以N来简化。
//所以的字母记作letter，在之后的表示中将以L来简化。
//所有的符号记作symbol，在之后的表示中将以S来简化。
//所有的下划线记作underline，在之后的表示中将以U来简化。

void CheckNLU(char *);//该函数用于检查输入内容是否为数字、字母、下划线。
void CheckVisible(char *);//该函数用于检查输入内容是否为可见字符。
void CheckN(char *);//该函数用于检查输入内容是否为非负数。并且是否在int范围内。
void CheckEmpty(std::string);//该函数用于检查输入内容是否为空。
void CheckSize30(char *);//该函数用于检查输入内容是否超过30个字符。
void CheckSize60(char *);//该函数用于检查输入内容是否超过60个字符。
void CheckSize20(char *);//该函数用于检查输入内容是否超过20个字符。
void CheckSize10(char *);//该函数用于检查输入内容是否超过10个字符。
void CheckSize13(char *);//该函数用于检查输入内容是否超过13个字符。
void CheckVisibleNoQuotation(char *);//该函数用于检查输入内容是否为可见字符，且不包含双引号。
void CheckReal(char *);//该函数用于检查输入内容是否为非负实数。
void CheckRepeat(std::string);//该函数用于检查输入内容是否重复。
#endif