#pragma once
#include "../base_header.h"
namespace q388
{
int lengthLongestPath(string input) {
    /*
		除了第一个目录，必然已\n开头
		子目录必然已\n和若干和\t开头
		\t的个数代表着目录的层级
	*/
    int i = 0;
    int cur_len = 0;
    int max_len = 0;
    vector<string> st;
    while (i < input.length())
    {
        int level = 0;
        while (i < input.length() && input[i] == '\t')
        {
            ++level;
            i++;
        }

        while (st.size() > level)
        {
            cur_len -= (st.back().length() + (st.size() > 1 ? 1 : 0));
            st.pop_back();
        }

        auto pos = min(input.length(), input.find_first_of('\n', i));
        auto prex = input.substr(i, pos - i);
        cur_len += ((st.size() > 0 ? 1 : 0) + pos - i);
        st.push_back(prex);
        if (string::npos != prex.find('.'))
        {
            max_len = max(max_len, cur_len);
        }
        i = pos + 1;

    }

    return max_len;
}


void test()
{
    map<int, bool> vn;
    lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
}
}