#include <iostream>
#include <queue>
using namespace std;

// East West North South 
// dice
int ewns[4] = {0};
int top_ = 0;
int floor_ = 0;

// map
int pos_x[] = {0, 0, -1, 1};
int pos_y[] = {1, -1, 0, 0};
int map[20][20];
int N, M;

// x가 세로
int x, y;

int K;

queue<int> q;

void move_dice(int cmd){
    if(cmd == 1 || cmd == 2){
        cmd -= 1;
        int prev_tmp = ewns[cmd];
        ewns[cmd] = top_;
        top_ = ewns[(cmd == 0 ? 1 : 0)];
        ewns[(cmd == 0 ? 1 : 0)] = floor_;    
        floor_ = prev_tmp;
    }
    else{
        cmd -= 1;
        int prev_tmp = ewns[cmd];
        ewns[cmd] = top_;
        top_ = ewns[(cmd == 2 ? 3 : 2)];
        ewns[(cmd == 2 ? 3 : 2)] = floor_;    
        floor_ = prev_tmp;
    }
}
bool move_map(int cmd){
    cmd -= 1;
    int x_ = x + pos_x[cmd];
    int y_ = y + pos_y[cmd];
    if(x_ >= 0 && x_ < N && y_ >= 0 && y_ < M){
        x = x_;
        y = y_;
        return true;
    }
    return false;
}
void solve(){
    int size = q.size();
    for(int i = 0; i < size; i++){
        int cmd = q.front();
        q.pop();
        if(move_map(cmd)){
            move_dice(cmd);
            if(map[x][y] == 0){
                map[x][y] = floor_;
            }
            else{
                floor_ = map[x][y];
                map[x][y] = 0;
            }
            cout << top_ << endl;
        }
    }
}
int main(){
    cin >> N >> M >> x >> y >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
    for(int i = 0; i < K; i++){
        int cmd;
        cin >> cmd;
        q.push(cmd);
    }
    solve();
}