class Solution {
public:
    int power_value(int k) {
        int ans = 0;
        while (k != 1) {
            if (k % 2 == 0) k /= 2;
            else k = 3 * k + 1;
            ans++;
        }
        return ans;
    }
    int getKth(int lo, int hi, int k) {
        assert(power_value(3) == 7);
        vector<pair<int, int>> arr;
        for (int i = lo; i <= hi; i++) arr.push_back({power_value(i), i});
        sort(arr.begin(), arr.end());
        return arr[k - 1].second;
    }
};