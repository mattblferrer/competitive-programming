class Solution {
public:
    long long pickGifts(vector<int> &gifts, int k) {
        long long ans = 0;
        for (int i = 0; i < gifts.size(); i++) ans += gifts[i];
        priority_queue<int> gift_queue(gifts.begin(), gifts.end());
        for (int i = 0; i < k; i++) {
            int g = gift_queue.top();
            ans -= g;
            gift_queue.pop();
            gift_queue.push(floor(sqrt(g)));
            ans += floor(sqrt(g));
        }
        return ans;
    }
};