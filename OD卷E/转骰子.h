#pragma once
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
/*
	123456
	563421
	653412
	125643
	126534
	431256
	342156
*/

namespace q3
{
template<char C>
void roll(std::string& str) {}


template<>
void roll<'L'>(std::string& str)
{
	std::swap(str[0], str[4]);
	std::swap(str[1], str[5]);
	std::swap(str[4], str[5]);
}

template<>
void roll<'R'>(std::string& str)
{
	std::swap(str[0], str[4]);
	std::swap(str[1], str[5]);
	std::swap(str[0], str[1]);
}

template<>
void roll<'F'>(std::string& str)
{
	std::swap(str[2], str[4]);
	std::swap(str[3], str[5]);
	std::swap(str[4], str[5]);
}

template<>
void roll<'B'>(std::string& str)
{
	std::swap(str[2], str[4]);
	std::swap(str[3], str[5]);
	std::swap(str[2], str[3]);
}

template<>
void roll<'A'>(std::string& str)
{
	std::swap(str[0], str[2]);
	std::swap(str[1], str[3]);
	std::swap(str[0], str[1]);
}

template<>
void roll<'C'>(std::string& str)
{
	std::swap(str[0], str[2]);
	std::swap(str[1], str[3]);
	std::swap(str[2], str[3]);
}

std::string roolrols(const std::string& str)
{
	std::string base{ "123456" };

	for (auto el : str)
	{
		switch (el)
		{
		case 'L':roll<'L'>(base); break;
		case 'R':roll<'R'>(base); break;
		case 'F':roll<'F'>(base); break;
		case 'B':roll<'B'>(base); break;
		case 'A':roll<'A'>(base); break;
		case 'C':roll<'C'>(base); break;
		}
	}

	return base;
}

void test()
{
	std::cout << roolrols("LR") << std::endl;
	std::cout << roolrols("FCR") << std::endl;
}
}