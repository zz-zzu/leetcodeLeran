//
// Created by Zhengz on 24-10-6.
//
//题目链接：https://leetcode.cn/problems/longest-substring-without-repeating-characters/?envType=study-plan-v2&envId=top-100-liked
#include<iostream>
#include <set>
#include<string>
#include <unordered_set>
using namespace std;
/*
 * 题目描述：最长字串问题
 * 解题思路：核心思想就是一个index往右遍历，当没遇到一个新的值的时候检查之前是否出现如果出现修改计算length的start
 * 1:将子串设置为哈希表，key为字符，value为下标
 * 2:从左往右遍历，检查每一个字符是否在哈希表中如果在更新当前length(根据字符获得下标i-index),如果>maxlength,
 * 3:如果不在加入哈希表
 * =========
 * 官方题解的方式关键点在于使用是的滑动窗口的使用，以及使用set这个数据类型作为哈希表的数据类型
 *
 *
 */
class Solution {
public:
    //自己的写法
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> map;
        int len = 1, maxlen = 1;
        if (s.length() == 1) {
            return maxlen;
        }
        else if (s.length() == 0)
        {
            return 0;
        }
        map[s[0]] = 0;
        for (int i = 1; i < s.length(); i++) {
            auto  it = map.find(s[i]);
            if (it != map.end()) {
                len = i - it->second ;
                if(len > maxlen) {
                    maxlen = len;
                }
                //重复之前的map要删除
            }else {
                len++;
                if(len > maxlen) {
                    maxlen = len;
                }
            }
            map[s[i]] = i;
            //len++;
        }
        if(len > maxlen) {
            maxlen = len;
        }
        return maxlen;
    }
    //官方写法 使用了一个unordered_set,set是只允许出现不同的元素
    int lengthOfLongestSubstring_1(string s) {
        unordered_set<char> hash;
        int rk = -1 , n = s.length(),ans=0;
        for (int i = 0; i < s.length(); i++) {
            if (i != 0) {
                hash.erase(s[i]);
            }
            while(rk+1<n && !hash.count(s[rk+1])) {
                hash.insert(s[rk+1]);
                rk++;
            }
            ans = max(ans, rk-i+1);

        }
    }
    //评论区提交的一个利用map的解法
    int lengthOfLongestSubstring_2(string s) {
        unordered_map<char, int> map;
        int start = 0, end = 0,lenth = 0,ans = 0;
        while (end < s.length()) {
            char temp = s[end];
            //map.end()只是一个临界值 表示map的末尾
            if(map.find(temp) != map.end() && map[temp]>=start)
            {
                start = map[temp]+1;//修改左指针的取值
                lenth = end - start;//计算最新的length
            }
            map[temp] = end;//修改最新的当前char的下标志
            end++;
            lenth++;
            ans = max(ans, lenth);


        }
    }
};

int main() {
    Solution s;
    int len = s.lengthOfLongestSubstring("cbb");
    cout<<len<<endl;
    return 0;
}