class Solution {
public:
    int findLucky(vector<int> &arr) {
        map<int, int> freq;
        for (int i = 0; i < arr.size(); i++) freq[arr[i]]++;
        int ans = -1;
        for (int i = 0; i < arr.size(); i++) {
            if (freq[arr[i]] == arr[i]) ans = max(ans, arr[i]);
        }
        return ans;
    }
};