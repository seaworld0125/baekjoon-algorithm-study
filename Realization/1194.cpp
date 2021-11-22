#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 50
#define pii pair<int, int>
#define F first
#define S second

int N, M;
char map[MAX][MAX];
bool visit[MAX][MAX][1 << 6]; // f,e,d,c,b,a

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

pii my_pos;

bool if_have_key(int key, char door) {
    int result = key & (1 << (door - 'A'));
    return (result != 0 ? true : false);
}

int BFS(int sy, int sx) {
    queue<pair<pii, pii>> q; // {y, x} , {cnt, key}
    q.push({{sy, sx}, {0, 0}});
    visit[sy][sx][0] = true;

    while(!q.empty()) {
        int y = q.front().F.F;
        int x = q.front().F.S;
        int cnt = q.front().S.F;
        int key = q.front().S.S;
        q.pop();

        if(map[y][x] == '1') return cnt;

        for(int i = 0; i < 4; i++) {
            int y_ = y + dy[i];
            int x_ = x + dx[i];

            if(y_ < 0 || x_ < 0 || y_ >= N || x_ >= M || visit[y_][x_][key]) continue;

            if(map[y_][x_] == '.' || map[y_][x_] == '1' || map[y_][x_] == '0') {
                visit[y_][x_][key] = true;
                q.push({{y_, x_}, {cnt + 1, key}});
            }
            else if('a' <= map[y_][x_] && map[y_][x_] <= 'f') {
                int n_key = key | (1 << (map[y_][x_] - 'a'));
                visit[y_][x_][n_key] = true;
                q.push({{y_, x_}, {cnt + 1, n_key}});
            }
            else if('A' <= map[y_][x_] && map[y_][x_] <= 'F') {
                if(if_have_key(key, map[y_][x_])) {
                    visit[y_][x_][key] = true;
                    q.push({{y_, x_}, {cnt + 1, key}});
                }
            }
        }
    }
    return -1;
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
            
            if(map[i][j] == '0')
                my_pos = {i, j};
        }
    
    memset(visit, false, sizeof(visit));
    
    cout << BFS(my_pos.F, my_pos.S);
}