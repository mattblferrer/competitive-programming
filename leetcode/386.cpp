class Solution {
public:
    vector<int> ans;
    void traverse(int n, int limit) {
        if (n > limit) return;

        int start;
        if (n == 0) start = 1;
        else {
            start = 0;
            ans.push_back(n);
        }
        for (int i = start; i < 10; i++) {
            traverse(n * 10 + i, limit);
        }
    }
    vector<int> lexicalOrder(int n) {
        traverse(0, n);
        return ans;
    }
};