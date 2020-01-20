#include <iostream>
#include <vector>
#include <cassert>
#include "../utils.h"

using namespace std;

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

// Solution1. brute force
// time: o(n^3)
// space: o(n): set
//
// loop i, j, unique check (set)
// abcabcbb
// abc
// bca

// Solution2. sliding windows
// time: o(2n) : iterate by r, l
// space: o(n) : set 
// 
// set<char> visited
// l = 0, r = 0
// abcbcbb
//lr        v=a
// lr       v=a,b
// l r      v=a,b,c
// l  r     v=b,c
//  l r     v=b,c,a

// Soultion2-1. Sliding window Optimized(map for next index)
// time: o(n) : iterate by r
// map<char, int> next index
// if it exist, l = max(next index, l)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() < 1) return s.size();
        
        if (false) {
            // solution 2
            int maxl = 0;
            unordered_set<char> v;
            int l=0, r=0;
            while (l < s.size() && r < s.size()) {
                if (v.find(s[r]) == v.end()) {
                    maxl = max(maxl, r - l + 1);
                    v.insert(s[r++]);
                }
                else {
                    v.erase(s[l++]);
                }
            }

            return maxl;
        }
        else {
            // solution 2-1
            int n = s.size();
            int l=0, r=0, maxl=0;
            unordered_map<char, int> cache;
            while (l<n && r<n) {
                if (cache.find(s[r]) != cache.end()) {
                    l = max(cache[s[r]], l);
                }
                maxl = max(maxl, r - l + 1);
                cache[s[r]] = r + 1;
                r++;
            }
            
            return maxl;
        }
    }
};

int main()
{
    assert(Solution().lengthOfLongestSubstring("abcabcbb") == 3);
    assert(Solution().lengthOfLongestSubstring("aab") == 2);
    assert(Solution().lengthOfLongestSubstring("pwwkew") == 3);
    assert(Solution().lengthOfLongestSubstring("ohvhjdml") == 6);
    assert(Solution().lengthOfLongestSubstring("abba") == 2);
    return 0;
}