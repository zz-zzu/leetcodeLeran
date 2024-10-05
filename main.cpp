#include <iostream>
#include <map>
#include <algorithm>
#include <ranges>
#include<set>
#include<unordered_set>
#include<vector>
using namespace  std;

// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     return 0;
// }





class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = 0,area = 0;
        for( right = left + 1; right < height.size(); right++) {
            while(height[right]< height[left]) {
                right++;
            }
            for(int i = left ; i < left + right ; i++ ) {
                area = height[left] - height[i] + area;
            }
            left = right +1;
            right = left + 1;

        }
        return area;

    }
};

int main(){
    std::vector<int> nums ;
    //int nums[] = {-1, 0, 1,2,-1,-4};
    nums.push_back(4); //[0,3,7,2,5,8,4,6,0,1] 1,8,6,2,5,4,8,3,7]
    nums.push_back(2);
    nums.push_back(0);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(5);
    //nums.push_back(8);
   // nums.push_back(3);
    //nums.push_back(7);
    //nums.push_back(1);

    Solution s;
    int result;
    //vector<vector<int> >
    result = s.trap(nums);

    /*for(size_t i = 0; i < result.size();i++) {
        vector<int> temp = result[i];
        for(size_t j = 0; j< temp.size();j++) {
            cout<<temp[j]<<" ";
        }
        cout<<endl;
    }*/
    cout<< result <<endl;
    //cout<<nums[0]<<" "<<nums[1]<<" "<<nums[2]<<endl;

}