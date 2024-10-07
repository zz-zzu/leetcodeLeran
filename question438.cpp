//
// Created by Zhengz on 24-10-6.
//
//题目链接：https://leetcode.cn/problems/find-all-anagrams-in-a-string/?envType=study-plan-v2&envId=top-100-liked
#include<iostream>
#include <set>
#include<string>
#include <unordered_set>
using namespace std;

/*
 * 题目描述：滑动窗口的题目就是p长度的窗口，在s里面找到p字符串的异位，返回开头的下标
 * 解题思路：
 * 自己：就是滑动窗口，利用了string查找第一个某个字符出现的位置如果出现则删除，比较完之后看是否是创建的临时的temp是否位空
 * GPT的解决思路是将p和创建一个p长度的子串的窗口使用一个没有顺序的map 直接使用两个map来判断了
 * 官方题解：创建一个26个字母的数组来记录出现的频率。
 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        for(int i=0;i<(s.length()-p.length()+1);i++){
            string tempstr = s.substr(i,p.length());
            int length = p.length();
            string temp = p;
            for(int j=0;j<tempstr.length();j++) {
                if(tempstr.find_first_of(temp[j])!=string::npos) {
                    int index = tempstr.find_first_of(temp[j]);
                    tempstr.erase(index,length);
                    length--;
                }
                else {
                    break;
                }
            }
                if(length==0){
                    ans.push_back(i);
            }
        }
        return ans;
    }

    std::vector<int> findAnagrams_gpt(std::string s, std::string p) {
        std::vector<int> ans;
        if (s.length() < p.length()) return ans; // 确保 s 至少和 p 一样长
        std::unordered_map<char, int> pCount, sCount;
        // 初始化 p 的字符计数
        for (char c : p) {
            pCount[c]++;
        }
        // 初始化 s 的前 p.length() 个字符的计数
        for (int i = 0; i < p.length(); i++) {
            sCount[s[i]]++;
        }
        // 检查初始窗口是否为异位词
        if (pCount == sCount) {
            ans.push_back(0);
        }
        // 滑动窗口
        for (int i = p.length(); i < s.length(); i++) {
            sCount[s[i]]++; // 加入新的字符
            sCount[s[i - p.length()]]--; // 移除左侧字符
            // 如果左侧字符的计数为 0，则删除它
            if (sCount[s[i - p.length()]] == 0) {
                sCount.erase(s[i - p.length()]);
            }
            // 比较当前窗口的字符计数
            if (pCount == sCount) {
                ans.push_back(i - p.length() + 1);
            }
        }
        return ans;
    }

    vector<int> findAnagrams_official(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];//将26个字母映射到26个数字
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }

};

int main() {
    Solution s;
    vector<int> ans = s.findAnagrams("cbaebabacd","abc");
    cout<<ans[1]<<endl;
    return 0;
}