class Solution {
public:
    int get_score(deque<char> sd) {
        int score = 0;
        for (int i = 0; i < sd.size() - 1; i++) {
            if (sd[i] == sd[i + 1]) score++;
        }
        return score;
    }

    int countRotations(string s, int k) {
        int n = s.size();
        int ans = 0;
        deque<char> sd(s.begin(), s.end());
        for (int i = 0; i < n; i++) {
            if (get_score(sd) == k) ans++;
            sd.push_back(sd[0]);
            sd.pop_front();
        }
        return ans;
    }
};