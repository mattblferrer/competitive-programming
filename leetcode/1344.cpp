class Solution {
public:
    double angleClock(int hour, int minutes) {
        if (hour == 12) hour = 0;
        double h_angle = hour * 30 + minutes * 0.5;
        double m_angle = minutes * 6;
        double final_angle = abs(h_angle - m_angle);
        return min(final_angle, 360 - final_angle);
    }
};