#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int map[50][50];
int N, L, R;

int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};

// 한 개의 연합 생성
bool bfs(bool visited[][50], int y = 0, int x = 0) {
    visited[y][x] = true;

    queue<pair<int, int>> q;
    q.push({y, x});

    vector<pair<int, int>> v;
    v.emplace_back(y, x);

    int population = map[y][x];
    int nations = 1;

    while(!q.empty()) {
        auto pos = q.front();
        q.pop();

        for(int i = 0; i < 4; i++) {
            int y_ = pos.first + dy[i];
            int x_ = pos.second + dx[i];

            if(x_ >= 0 && x_ < N && y_ >= 0 && y_ < N) {
                if(!visited[y_][x_]) {
                    int sub = map[y_][x_] - map[pos.first][pos.second];
                    if(sub < 0) 
                        sub *= -1;

                    if(sub >= L && sub <= R) {
                        q.push({y_, x_});
                        v.emplace_back(y_, x_);
                        visited[y_][x_] = true;

                        population += map[y_][x_];
                        nations++;
                    }
                }
            }
        }
    }

    if(nations == 1) return false;
    else if(nations > 1) {
        population = population / nations;
        for(int i = 0; i < v.size(); i++)
            map[v[i].first][v[i].second] = population;
            
        return true;
    }
}
    
int main() {
    cin >> N >> L >> R;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> map[i][j];

    int ans = 0;
    while(1) {
        bool if_move = false;

        bool visited[50][50];
        fill(visited[0], visited[0]+2500, false);

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++) 
                if(!visited[i][j]) {
                    if(!if_move)
                        if_move = bfs(visited, i, j);
                    else 
                        bfs(visited, i, j);
                }

        if(if_move) ans++; 
        else break;
    }
    cout << ans;
}   

// 1.04