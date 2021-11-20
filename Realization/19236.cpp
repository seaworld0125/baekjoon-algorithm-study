#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define F first
#define S second

int dy[] = {0, -1, -1, 0, 1, 1, 1, 0, -1}; // 반시계 방향[1~8] ↑, ↖, ←, ↙, ↓, ↘, →, ↗
int dx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};  

void fishMove(int (*map)[4], int (*dir)[4], vector<pair<int, int>> & fish_pos, pair<int, int> & shark_pos) {
    for(int i = 1; i < 17; i++) {
        int y = fish_pos[i].F; // y, x는 원래 좌표
        int x = fish_pos[i].S;

        if(y > -1 && x > -1) {
            for(int j = dir[y][x], count = 0; count < 8; j++, count++) { // j는 방향 인덱스
                int y_ = y + dy[j]; // 방향 좌표를 더해서 새로운 좌표 생성
                int x_ = x + dx[j];

                if(y_ >= 0 && x_ >= 0 && y_ < 4 && x_ < 4) if (shark_pos.F != y_ || shark_pos.S != x_) { // 새로운 좌표가 유효한 범위이고 상어가 없으면
                    fish_pos[map[y][x]] = {y_, x_};
                    fish_pos[map[y_][x_]] = {y, x};

                    dir[y][x] = j;

                    int tmp01 = map[y][x];
                    int tmp02 = dir[y][x];
                    
                    map[y][x] = map[y_][x_];
                    dir[y][x] = dir[y_][x_];

                    map[y_][x_] = tmp01;
                    dir[y_][x_] = tmp02;

                    break;
                }
                if(j == 8) j %= 8;
            }
        } 
    }
}

int searchMax(int y, int x, int ans, int (*prev_map)[4], int (*prev_dir)[4], vector<pair<int, int>> & fish_pos) {
    int map[4][4], dir[4][4]; 
    memcpy(map, prev_map, 16 * 4); 
    memcpy(dir, prev_dir, 16 * 4);

    int food_idx = prev_map[y][x]; 
    int shark_dir = prev_dir[y][x]; // 물고기 먹고 상어 방향바뀜
    pair<int, int> shark_pos = {y, x};

    vector<pair<int, int>> now_fish_pos(17);
    now_fish_pos.assign(fish_pos.begin(), fish_pos.end());
    now_fish_pos[food_idx].F = -1; // 잡아먹을 물고기 위치 정보 삭제
    now_fish_pos[food_idx].S = -1;

    ans += food_idx; // 물고기 번호 답에 더해줌
    map[y][x] = 0; // 물고기 잡아먹음
    dir[y][x] = 0;

    fishMove(map, dir, now_fish_pos, shark_pos); // 물고기들 이동

    queue<pair<int, int>> foodPos;
    int y_ = y;
    int x_ = x;
    for(int i = 0; i < 3; i++) { // 상어의 경로에 물고기가 최대 3마리까지 있을 수 있음
        y_ += dy[shark_dir];
        x_ += dx[shark_dir];

        if(y_ >= 0 && x_ >= 0 && y_ < 4 && x_ < 4 && map[y_][x_])
            foodPos.emplace(y_, x_);
    }

    int maxAns = -1, size = foodPos.size();
    for(int i = 0; i < size; i++) {
        auto pos = foodPos.front();
        foodPos.pop();

        maxAns = max(searchMax(pos.F, pos.S, ans, map, dir, now_fish_pos), maxAns); 
    }
    return max(ans, maxAns);
}

int main() {
    int map[4][4];
    int dir[4][4];
    vector<pair<int, int>> fishPos(17);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) {
            cin >> map[i][j] >> dir[i][j];
            
            fishPos[map[i][j]].F = i;
            fishPos[map[i][j]].S = j;
        }

    int ans = 0;
    cout << searchMax(0, 0, ans, map, dir, fishPos);
}