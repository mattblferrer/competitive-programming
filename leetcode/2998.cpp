class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        set<int> seen;
        queue<pair<int, int>> q;
        q.push({x, 0});
        while (!q.empty()) {
            auto pair = q.front();
            q.pop();
            int k = pair.first, op = pair.second;
            if (seen.count(k)) continue;
            seen.insert(k);
            if (k == y) return op;
            if (k % 11 == 0) q.push({k / 11, op + 1});
            if (k % 5 == 0) q.push({k / 5, op + 1});
            q.push({k - 1, op + 1});
            q.push({k + 1, op + 1});
        }
        return -1;
    }
};