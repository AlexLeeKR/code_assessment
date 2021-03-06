#include <iostream>
#include <cassert>

#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

/**
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

//Solution1. sort and compare to find lmost diff rmost diff
//time: o(nlogn) = o(n) + o(nlogn) + o(n)
//space: o(n)

//Solution2. using stack.
//time: o(n) = o(n) + o(n)
//space: o(n) = stack
// From bottom, find num against order and set min index
1 3 2 5
s: 1
s: 1 3
s: 1 2      l = 1(v: 3)
s: 1 2 5
// From top, findn um against order and set max index
1 3 2 5
s: 5
s: 5 2
s: 5 3      r = 2(v: 2)
s: 5 3 1

//Solution3. without extra space. set min(left->right), max(right->left) if not sorted. And find when unsorted started from min, max
// time: o(n) : n + n + n + n
// space: o(1)
1. find minv which against order
2. find maxv which against order
3. find lmost which bigger than minv
4. find rmost which smaller than maxv

1 3 2 5
min: 0(v: 1), max: 3(v: 5)

1 3 2 5
  l (1 < 3)
1 3 2 5
    r (5 > 2)
 
3 1 4 7 5
min: 1(v: 1), max: 3(v: 7)

3 1 4 7 5
l (1 < 3)
3 1 4 7 5
        r (7 > 5)


*/
class Solution {
public:
    int findUnsortedSubarray_sort(vector<int>& nums) {
        vector<int> ordered(nums.begin(), nums.end());
        sort(ordered.begin(), ordered.end());
        
        auto l = -1, r = -1;
        for (int i=0; i<nums.size(); ++i) {
            if (l == -1 && ordered[i] != nums[i]) {
                l = i;
            }
            auto j = nums.size() - 1 - i;
            if (r == -1 && ordered[j] != nums[j]) {
                r = j;
            }
            if (l != -1 && r != -1) break;
        }
        
        return (l == r) ? 0 : r - l + 1;
    }
    
    int findUnsortedSubarray_stack(vector<int>& nums) {
        stack<int> s;
        int l = nums.size();
        for (int i=0; i<nums.size(); ++i) {
            while (!s.empty() && nums[i] < nums[s.top()]) {
                l = min(l, s.top());
                s.pop();
            }
            s.push(i);
        }
        while (!s.empty()) s.pop();
        
        int r = -1;
        for (int i=nums.size()-1; i>=0; --i) {
            while (!s.empty() && nums[i] > nums[s.top()]) {
                r = max(r, s.top());
                s.pop();
            }
            s.push(i);
        }
        
        return (r - l > 0) ? r - l + 1 : 0;
    }
    
    int findUnsortedSubarray_nospace(vector<int>& nums) {
        int n = nums.size();
        int minv = INT_MAX;
        int maxv = INT_MIN;
        
        for (int i=1; i<n; ++i) {
            if (nums[i] < nums[i-1]) {
                minv = min(minv, nums[i]);
            }
        }
        for (int i=n-2; i>=0; --i) {
            if (nums[i] > nums[i+1]) {
                maxv = max(maxv, nums[i]);
            }
        }
        
        int l = 0;
        for (; l<n; ++l) {
            if (minv < nums[l]) break;
        }
        
        int r = n-1;
        for (; r>=0; --r) {
            if (maxv > nums[r]) break;
        }

        return (r > l) ? r - l + 1 : 0;
    }
    
    int findUnsortedSubarray(vector<int>& nums) {
        //return findUnsortedSubarray_sort(nums);
        //return findUnsortedSubarray_stack(nums);
        return findUnsortedSubarray_nospace(nums);
    }
};

int main()
{
    auto input1_1 = vector<int> {2, 6, 4, 8, 10, 9, 15};
    assert(Solution().findUnsortedSubarray(input1_1)
        == (5));

    return 0;
}