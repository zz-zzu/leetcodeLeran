//
// Created by Zhengz on 24-10-4.
//
#include<vector>
#include<iostream>
using namespace  std;
class Solution {
public:
    int trap_1(vector<int>& height) {
        //解法一：直接使用循环
        int left = 0, right = 0,area = 0;
        for( right = left + 1; right < height.size(); right++) {
            while(height[right] <  height[left]) {
                right++;
            }
            if(right>(left+1))
            {
                int gao = min(height[left],height[right]) ;
                for(int i = left+1  ; i <  right ; i++ ) {
                    area = (gao - height[i]) + area;
                }

                left = right ;
                right = left + 1;
            }


        }
        return area;

    }

    int trap_2(vector<int>& height)
    //采用单调栈的方法
    {
        stack<int> stk(height.size());
        while(stack)

    }

    int trap_3(vector<int>& height)
    //动态规划
    //关键点在于求左右的较大数组
    {
        int result=0;
        int length = height.size();
        if(length < 3)
            return 0;
        vector<int> left(length),right(length);
        left[0] = height[0];
        right[0] = height[length-1];
        for(int i = 1; i < height.size();i++) {
            left[i] = max(left[i-1],height[i]);
        }
        for(int i = height.size()-2; i >= 0; i--) {
            right[i] = max(right[i+1],height[i]);
        }
        for(int i = 0; i < height.size(); i++) {
            result = result + min(left[i],right[i])-height[i];
        }
        return result;


    }
};



int main() {

    vector<int> vec = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    Solution s;
    int ans = s.trap_3(vec);
    cout << ans << endl;


    return 0;
}