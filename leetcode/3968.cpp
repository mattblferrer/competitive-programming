class Solution {
public:
    int maxDistance(string moves) {
        int n = moves.size();
        int x = 0, y = 0, max_d = 0, blanks = 0;
        for (int i = 0; i < n; i++) {
            if (moves[i] == 'U') y++;
            else if (moves[i] == 'D') y--;
            else if (moves[i] == 'L') x--;
            else if (moves[i] == 'R') x++;
            else blanks++;
        }
        if (x > 0) x += blanks;
        else if (x < 0) x -= blanks;
        else if (y > 0) y += blanks;
        else y -= blanks;
        return abs(x) + abs(y);
    }
}
