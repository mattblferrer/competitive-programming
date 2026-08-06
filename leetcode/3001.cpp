class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        if (a == e) {  // rook row
            if ((a == c) && ((b < d) == (d < f))) return 2;
            return 1;
        }
        if (b == f) {  // rook column
            if ((b == d) && ((a < c) == (c < e))) return 2;
            return 1;
        }
        if ((c - d) == (e - f)) {  // bishop diagonal
            if (((a - b) == (c - d)) && ((c < a) == (a < e))) return 2;
            return 1;
        }
        if ((c + d) == (e + f)) {  // bishop antidiagonal
            if (((a + b) == (c + d)) && ((c < a) == (a < e))) return 2;
            return 1;
        }
        return 2;
    }
};