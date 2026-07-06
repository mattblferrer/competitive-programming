class Solution {
public:
    vector<string> topKFrequent(vector<string> &words, int k) {
        map<string, int> freq;
        for (int i = 0; i < words.size(); i++) freq[words[i]]++;
        vector<pair<string, int>> to_sort;
        for (auto pair : freq) to_sort.push_back(pair);
        sort(to_sort.begin(), to_sort.end(), [](auto a, auto b) {
            if (a.second == b.second) return a.first < b.first;
            else return a.second > b.second;
            });
        vector<string> ans;
        for (int i = 0; i < k; i++) ans.push_back(to_sort[i].first);
        return ans;
    }
};