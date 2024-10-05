//
// Created by Zhengz on 24-10-4.
//
#include<vector>
#include<iostream>
using namespace  std;
class Solution {
public:
    int trap_1(vector<int>& height) {
        /*解法一：直接使用双指针 更好理解的看动态规划法（3）
         * 即使用left和right两个指针动态的记录动态规划里面的取值
         *
         */
        int left = 0, right = height.size()-1,
            leftmax = height[left],rightmax = height[right],
                ans = 0;
        left++;
        right--;
        while(left < right) {
            leftmax = max(leftmax,height[left]);
            rightmax = max(rightmax,height[right]);
            if(height[left] < height[right]) {
                ans += (leftmax - height[left]);
                left++;
            } else {
                ans += (rightmax - height[right]);
                right--;
            }
        }
        return ans;

    }

    int trap_2(vector<int>& height)
    /*采用单调栈的方法
    1:单调栈存储的是下标，何为单调栈就是取值是单调递减的
    2:找可以积水的地方即当前的i取值如果比栈顶元素大（这样就保证了右侧）则可能形成积水，由于是单调递减的栈则保证了左侧
    3:但是其实这里计算的是栈顶元素 的下一个元素获得的体积其实也就是相应的每一层的体积
    */
    {
        stack<int> stk;//初始化的时候不需要给定大小
        int i = 0,ans = 0,top = 0,left = 0,weight = 0,high = 0;
        for(i = 0 ; i < height.size(); ++i) {
            while(!stk.empty() && height[stk.top()] < height[i]) {
                //可能会出现多次弹栈，但是面积是一行一行算的所以要计算weight
                top = stk.top();
                stk.pop();
                if(stk.empty())
                    break;//当仅有一个元素的时候也要结束
                left = stk.top();
                weight = i - left -1;
                high = min(height[i],height[left]) - height[top];//就相当于计算的是height[top]这一个位置的积水量
                ans = ans + weight*high;
            }
            stk.push(i);
        }
    return ans;
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
    int ans = s.trap_1(vec);
    cout << ans << endl;
    return 0;
}