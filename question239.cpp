//
// Created by Zhengz on 24-10-8.
//
#include<iostream>
#include<vector>
using namespace std;

/*
 * 解题思路
 * 求k个最大值之后每移动一个大小的窗口，比较一下一下大小----》会出现新取值出现在之前的窗口之间
 * 下面全是官方的题解
 *
 */
class Solution {
public:
    /*方法一：优先队列
     *
     */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res,sub;
        int maxSub = nums[0];
        for(int i=0;i<k;i++) {
            sub.push_back(res[i]);
            if(nums[i]>maxSub) {
                maxSub = nums[i];
            }
        }
        for(int i=k;i<nums.size();i++) {


        }
    }
    /*评论区一个好理解的解法
     *疑问 是窗口的最左端的元素 且是最大的 且大于新入队的元素
     *1. 在窗口最左侧，左边无元素。2. 在窗口中间某个位置，按照入队规则，此时该位置左侧的所有元素必定已从递减队列中弹出。
     *最开始保证初始的队列是单调递减的。  队头（出 大）====队尾（入 小）
     *
     */
    vector<int> maxSlidingWindow_pinglun(vector<int>& nums, int k) {
        if(nums.size() == 0 || k == 0) return {};
        deque<int> deque;
        vector<int> res(nums.size() - k + 1);
        //i = 0-k+1 窗口（i---j）
        for(int j = 0, i = 1 - k; j < nums.size(); i++, j++) {
            // 删除 deque 中对应的 nums[i-1]
            if(i > 0 && deque.front() == nums[i - 1])
                deque.pop_front();
            // 保持 deque 递减
            while(!deque.empty() && deque.back() < nums[j])
                deque.pop_back();
            deque.push_back(nums[j]);
            // 记录窗口最大值
            if(i >= 0)
                res[i] = deque.front();
        }
        return res;
    }

    /*官方解法：方法一优先队列
     * 直接使用大根堆，当现在的队列的元素不在窗口中的时候直接出队
     */
    vector<int> maxSlidingWindow_official(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<int,int> q;//为index和value
        for(int i = 0; i < k; i++) {
            q.emplace(nums[i],i);//是一个创建元素的方法可以降低不必要的复制
        }
        vector<int> res = {q.top().first};
        for(int i = k; i < n; i++) {
            q.emplace(nums[i],i);
            while(q.top().second <= i - k) {
                q.pop();
            }
            res.push_back(q.top().first);
        }
    return res;
    }

    vector<int> maxSlidingWindow_official(vector<int>& nums, int k) {

    }

};



int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    Solution s;
    vector<int> ans = s.maxSlidingWindow(nums,3);
    cout<<ans[1]<<endl;
    return 0;
}
