class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> valid;
        for (int d = 1; d <= 9; d++) {
            for (int start = 1; start <= 10 - d; start++) {
                string curr = "";
                for (int i = 0; i < d; i++) curr += start + i + '0';
                valid.push_back(stoi(curr));
            }
        }
        sort(valid.begin(), valid.end());
        vector<int> ans;
        for (int i = 0; i < valid.size(); i++) {
            if ((low <= valid[i]) && (valid[i] <= high)) ans.push_back(valid[i]);
        }
        return ans;
    }
};