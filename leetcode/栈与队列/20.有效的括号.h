#pragma once
#include "../base_header.h"

/*
	难度：简单
	判断一个包含"[]"、"()"、"{}"这三种括号的表达式是否有效

	单种括号可以用计数法取匹配， (()())()(())， 用一个变量记录左括号数量与右括号数量之差
	如果差为0，说明存在一个右括号无法与左括号匹配，则返回false，
	遍历完所有括号后如果不为0，说明有左括号无法匹配，返回false

	但是对于三种括号，无法使用计数法，因为计数法无法判断括号混合的情况：[(])
	因为计数法只是表象，并不是本质，本质是出现一个右括号时，立刻匹配一个左括号，将两者“消去”
	对于任意的一种右括号，它必须立刻与最近的未被消去的左括号匹配，否则表达式无效
	可以用一个栈来储存左括号，未匹配就入栈，匹配（“消去”）就出栈
*/
bool isValid(string str) 
{
	auto get_left_of = [](char c)
		{
			switch (c)
			{
			case '}': return '{';
			case ')': return '(';
				return '[';
			};
		};
	stack<char> left;
	for (char c : str) 
	{
		// 左括号直接入栈
		if (c == '(' || c == '{' || c == '[') 
		{
			left.push(c);
		}
		else 
		{
			// 右括号与栈顶匹配，匹配则出栈，不匹配，说明表达式无效
			if (!left.empty() && get_left_of(c) == left.top()) 
			{
				left.pop();
			}
			else 
			{
				return false;
			}
		}
	}
	// 是否所有的左括号都被匹配了
	return left.empty();
}