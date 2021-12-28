#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define PII pair<int, int>
#define F first
#define S second

int N, M, D;
bool map[16][15];
bool map_test[16][15]; // 복사 맵
vector<int> sub_permutation;

struct EnemyInfo {
    bool null;
    int x;
    int y;
    int dist;

    EnemyInfo(bool n = true, int x = -1, int y = -1, int d = -1) : null(n), x(x), y(y), dist(d) {};
};

int can_shoot(PII a, PII b) {
    int dist = abs(a.F - b.F) + abs(a.S - b.S);
    if(D >= dist)
        return dist;
    else return 0;
}

EnemyInfo find_enemy(PII archer) {
    EnemyInfo enemy_info;

    for(int i = N-1; i >= 0; i--)
        for(int j = 0; j < M; j++)
            if(map_test[i][j]) {
                int dist = 0;
                if(dist = can_shoot(archer, {i, j})) {
                    if(enemy_info.null) {
                        enemy_info.null = false;
                        enemy_info.y = i;
                        enemy_info.x = j;
                        enemy_info.dist = dist;
                    } 
                    else {
                        if(enemy_info.dist > dist) {
                            enemy_info.y = i;
                            enemy_info.x = j;
                            enemy_info.dist = dist;
                        }
                        else if(enemy_info.dist == dist) {
                            if(enemy_info.x > j) {
                                enemy_info.y = i;
                                enemy_info.x = j;
                            }
                        }
                    }
                }
            }
    return enemy_info;
}

int enemy_move() {
    int count = 0;
    for(int i = N-1; i >= 0; i--)
        for(int j = 0; j < M; j++)
            if(map_test[i][j]) {
                if(i + 1 < N) {
                    map_test[i + 1][j] = true;
                    count++;
                } 
                map_test[i][j] = false;
            }
    return count;
}

int simulation(int enemy_count) {
    memcpy(map_test, map, sizeof(map_test));

    vector<pair<int, int>> archer_pos; // 궁수 위치
    for(int i = 0; i < M; i++)
        if(sub_permutation[i])
            archer_pos.emplace_back(N, i);
    
    int kill_count = 0;

    while(enemy_count > 0) {
        vector<EnemyInfo> target(3);
        for(int i = 0; i < 3; i++) // 궁수 순회
            target[i] = find_enemy(archer_pos[i]);
            
        for(int i = 0; i < 3; i++) // 타켓 순회
            if(!target[i].null)
                if(map_test[target[i].y][target[i].x]) {
                    kill_count++;
                    map_test[target[i].y][target[i].x] = false;
                }
        // 적 움직임
        enemy_count = enemy_move();
    }
    return kill_count;
}

int main() {
    cin >> N >> M >> D;

    int enemy_count = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
            if(map[i][j]) enemy_count++;
        }

    for(int i = 0; i < M; i++) {
        if(i >= M-3)
            sub_permutation.emplace_back(1);
        else
            sub_permutation.emplace_back(0);
    }

    int ans = 0;
    do
    {
        ans = max(simulation(enemy_count), ans);
    } while (next_permutation(sub_permutation.begin(), sub_permutation.end()));
    
    cout << ans;
}