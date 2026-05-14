#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](vector<int> a, vector<int> b) {
            return a[1] - a[0] > b[1] - b[0];
            });

        int left = -1, right = 2000000000;
        while (right - left > 1) {
            bool possible = true;
            int mid = midpoint(left, right);
            int curr = mid;
            for (int i = 0; i < tasks.size(); i++) {
                if (curr < tasks[i][1]) possible = false;
                curr -= tasks[i][0];
            }

            if (possible) right = mid;
            else left = mid;
        }
        return right;
    }
};