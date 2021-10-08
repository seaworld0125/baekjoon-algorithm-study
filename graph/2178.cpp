#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;

int N, M, map[101][101], dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0}, ans = 1;
bool rec[101][101];

void BFS() {
    queue<pair<int, int>> q; 
    q.push({0,0});
    rec[0][0] = true;
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            auto pos = q.front(); q.pop();
            if(pos.first == N-1 && pos.second == M-1) return;
            for(int j = 0; j < 4; j++) {
                int y = pos.first + dy[j], x = pos.second + dx[j];
                if(y >= 0 && y < N && x >= 0 && x < M && !rec[y][x] && map[y][x] == 1) {
                    rec[y][x] = true;
                    q.push({y, x});
                } 
            }
        } ans++;
    }
}
int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            scanf("%1d", &map[i][j]);
        }
    }
    BFS();
    cout << ans;
}

