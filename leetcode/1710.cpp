#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), [](vector<int> a, vector<int> b) {
            return a[1] > b[1];
            });
        int ans = 0, boxes = 0;
        for (int i = 0; i < boxTypes.size(); i++) {
            int curr = min(boxTypes[i][0], truckSize - boxes);
            ans += curr * boxTypes[i][1];
            boxes += curr;
            if (boxes == truckSize) break;
        }
        return ans;
    }
};