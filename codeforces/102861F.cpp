#include <bits/stdc++.h>
using namespace std;

bool series_done = false;
bool left_series_win = false;
bool server_left = true;

struct player{
    int game_score = 0;
    int current_score = 0;
    bool series_winner = false;

    void reset(){
        current_score = 0;
    }

    void score(){
        current_score++;
    }
};

bool check_win(player p1, player p2){
    int win = max(p1.current_score, p2.current_score);
    int lose = min(p1.current_score, p2.current_score);
    return ((win >=5 and win >= lose+2) or (win >= 10));
}

void check_series_win(player p1, player p2){
    if (p1.game_score == 2){
        p1.series_winner = true;
        series_done = true;
        left_series_win = true;
    }else if (p2.game_score == 2){
        p2.series_winner = true;
        series_done = true;
    }
}

void announce(player left, player right){
    if (series_done){
        if (left_series_win)
            printf("%d (winner) - %d\n", left.game_score, right.game_score);
        else 
            printf("%d - %d (winner)\n", left.game_score, right.game_score);
    }else{
        if (server_left)
            printf("%d (%d*) - %d (%d)\n", left.game_score, left.current_score, right.game_score, right.current_score);
        else
            printf("%d (%d) - %d (%d*)\n", left.game_score, left.current_score, right.game_score, right.current_score);
    }
}

int main(){
    string game_events;
    cin >> game_events;
    
    player left, right;
    
    
    for (auto event: game_events){
        if (event == 'Q'){
            announce(left, right);
        }
        else{
            if (series_done) continue;

            if (
                (server_left and event == 'S') or 
                (not server_left and event == 'R')
            ){
                left.score();
                server_left = true;
            }else if (
                (not server_left and event == 'S') or
                (server_left and event == 'R')
            ){
                right.score();
                server_left = false;
            }

            if (check_win(left, right)){
                if (left.current_score > right.current_score){
                    left.game_score++;
                    server_left = true;
                }else{
                    right.game_score++;
                    server_left = false;
                }
                left.reset();
                right.reset();

                check_series_win(left, right);
            }
        }
    }
    return 0;
}