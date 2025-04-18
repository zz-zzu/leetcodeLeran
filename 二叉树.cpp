//
// Created by Zhengz on 25-4-6.
//使用ACM模式 创建二叉树 并实现 二叉树的遍历
//分别是广度优先的层序遍历（迭代） 和深度优先的前序、中序（递归）
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//先序和中序建树
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        this->preorder = preorder;
        for (int i = 0; i < inorder.size(); i++)
            dic[inorder[i]] = i;
        return recur(0, 0, inorder.size() - 1);
    }

private:
    vector<int> preorder;
    unordered_map<int, int> dic;

    TreeNode* recur(int root, int left, int right) {
        if (left > right) return nullptr;
        TreeNode* node = new TreeNode(preorder[root]);
        int i = dic[preorder[root]];
        node->left = recur(root + 1, left, i - 1);
        node->right = recur(root + (i - left) + 1, i + 1, right);
        return node;
    }
};

// 修复后的层序打印函数
void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(root);
    vector<string> result;

    while (!q.empty()) {
        int levelSize = q.size();
        vector<string> level;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            if (node) {
                level.push_back(to_string(node->val));
                q.push(node->left);
                q.push(node->right);
            } else {
                level.push_back("null");
                // 不再为null节点添加子节点
            }
        }

        // 检查当前层是否全为null
        bool allNull = true;
        for (const string& val : level) {
            if (val != "null") {
                allNull = false;
                break;
            }
        }

        if (!allNull) {
            for (const string& val : level) {
                result.push_back(val);
            }
        }
    }

    // 去除末尾多余的null
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ",";
        cout << result[i];
    }
    cout << "]" << endl;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 递归的二叉树中序遍历
class SolutionInorderTraversal {
    public:
    void inorder(TreeNode* root,vector<int>& result) {
        if(root == nullptr)
            return ;
        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right,result);
    }

    vector<int> inorderTraverser(TreeNode* root) {
        vector<int> result;
        inorder(root,result);
        return result;
    }

};

//迭代的方法实现的层序遍历
class QueTravSolution {
public:
    vector<int> QueOrder(TreeNode* root) {
        if (root==nullptr) return vector<int>();
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();//一个size就是一层 和 右视图那题
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                result.push_back(node->val);
            }
        }
        return result;
    }
};

class QueTravSolutionLenth {
public:
    int QueOrderLenth(TreeNode* root) {
        if (root==nullptr) return 0;
        int result=0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();//一个size就是一层 和 右视图那题
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                // result.push_back(node->val);
            }
            result = result+1;
        }
        return result;
    }
};

class SolutionLenth {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

class Solution543 {
    //求二叉树的直径
public:
    int ans;
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        ans = max(ans, left + right + 1);
        return max(right, left);
    }


    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        maxDepth(root);
        return ans-1;
    }
};

//将有序数组转化为平衡二叉搜索树
class Solution108 {
    public:
    TreeNode* ConstructBST(vector<int>& nums,int left,int right) {
        if(left==right){
            return nullptr;
        }
        int mid = left + (right - left) / 2;
        return new TreeNode(nums[mid],ConstructBST(nums, left, mid),ConstructBST(nums,mid+1,right));
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return  ConstructBST(nums,0,nums.size());






    }

};

//验证是否为二叉搜索树(通过递归的遍历将二叉树变为有序数组 然后再判断)
class Solution98 {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
    }
private:
    bool isValidBSTHelper(TreeNode* root, long minVal, long maxVal) {
        if (root == nullptr) {
            return true;  // 空树是有效的BST
        }
        // 当前节点的值必须在 minVal 和 maxVal 之间
        if (root->val <= minVal || root->val >= maxVal) {
            return false;
        }
        // 递归判断左子树和右子树
        return isValidBSTHelper(root->left, minVal, root->val) &&
               isValidBSTHelper(root->right, root->val, maxVal);
    }
};

// 二叉搜索树第k小的数 转化为有序数组再进行判断
class Solution230 {
    public:
    vector<int> result;
    int kthSmallest(TreeNode* root, int k) {
        vector<int> nums=inorder(root,result);
        return nums[k-1];
    }
private:
    vector<int> inorder(TreeNode*root,vector<int> &result) {
        if (root == nullptr) return vector<int>();

        TreeNode*node = root;
        inorder(node->left,result);
        result.push_back(node->val);
        inorder(node->right,result);
        return result;
    }
};

//二叉树转化为链表 类似于头插法
class Solution114 {
    public:
        void flatten(TreeNode* root) {
            TreeNode* node = nullptr; // 初始化为 nullptr
            flattenTree(root, node);  // 递归展开树
        }

        void flattenTree(TreeNode* root, TreeNode*& node) {
            if (root == nullptr) return;

            // 处理右子树
            flattenTree(root->right, node);
            // 处理左子树
            flattenTree(root->left, node);

            // 当前节点展开处理
            root->right = node;
            root->left = nullptr;
            node = root;  // 更新当前节点为根节点
        }
    };

// 路径总和III
class Solution437 {
private:
    void dfs(TreeNode* root, unordered_map<long long, int>& preSum, long long targetSum, long long sum, int& count) {
        if (root == nullptr) return;
        // 更新当前路径和
        sum += root->val;
        // 如果当前的 sum - targetSum 存在，说明有一条路径的和等于 targetSum
        if (preSum.find(sum - targetSum) != preSum.end()) {
            count += preSum[sum - targetSum];
        }
        // 更新当前路径和出现的次数
        preSum[sum]++;
        // 遍历左子树和右子树
        dfs(root->left, preSum, targetSum, sum, count);
        dfs(root->right, preSum, targetSum, sum, count);
        // 回溯：恢复当前路径的和出现次数
        preSum[sum]--;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> preSum;
        preSum[0] = 1;  // 假设路径和为 0 出现过一次
        int count = 0;
        dfs(root, preSum, targetSum, 0, count);
        return count;
    }
};


int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    Solution s;
    TreeNode* root = s.buildTree(preorder, inorder);
    printTree(root);  // 输出: [3,9,20,null,null,15,7]

    SolutionInorderTraversal s1;
    vector<int> resultInorder =  s1.inorderTraverser(root);
    for (int i = 0; i < resultInorder.size(); ++i) {
        cout << resultInorder[i] << " ";
    }
    cout << endl;

    QueTravSolution s2;
    vector<int> resultTrav =  s2.QueOrder(root);
    int size = resultTrav.size();
    cout << size <<endl;
    for (int i = 0; i < resultTrav.size(); ++i) {
        cout << resultTrav[i] << " ";
    }

    QueTravSolutionLenth s3;
    cout<<s3.QueOrderLenth(root)<<endl;

    SolutionLenth s4;
    cout<< s4.maxDepth(root)<<endl;

    deleteTree(root);
    return 0;
}