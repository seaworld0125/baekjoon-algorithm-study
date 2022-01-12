#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define F first
#define S second

int N, M;
bool map[1000][1000];
int dist_map[1000][1000];

int goalDist = 1e9;
bool hasGoal = false;

vector<pair<int, int>> wall_pos;
vector<int> wall_dist;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

bool checkRange(int y, int x) {
    if(y >= N || y < 0 || x >= M || x < 0) return false;
    return true;
}

void pre_bfs(int y, int x, bool isStart) {
    bool visited[1000][1000];
    fill(visited[0], visited[0] + (N * 1000), false);

    queue<pair<int, int>> q;
    q.emplace(y, x);
    visited[y][x] = true;

    int dist = 0;
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            if(pos.F == N-1 && pos.S == M-1 && isStart) {
                if(!hasGoal) hasGoal = true;
                goalDist = min(goalDist, (dist + 1));
            }
            else if(map[pos.F][pos.S] && isStart) {
                dist_map[pos.F][pos.S] = dist;
            }
            else if(map[pos.F][pos.S] && !isStart) {
                if(dist_map[pos.F][pos.S] >= 0) {
                    if(!hasGoal) hasGoal = true;
                    goalDist = min(goalDist, (dist_map[pos.F][pos.S] + dist + 1));
                }
            }
            else {
                for(int j = 0; j < 4; j++) {
                    int y_ = pos.F + dy[j];
                    int x_ = pos.S + dx[j];

                    if(checkRange(y_, x_) && !visited[y_][x_]) {
                        visited[y_][x_] = true;
                        q.emplace(y_, x_);
                    }
                }
            }
        }
        dist++;
    }
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char tmp;
            cin >> tmp;
            if((tmp - '0') == 1) map[i][j] = true;
            else map[i][j] = false;
            dist_map[i][j] = -1;
        }
    }

    if(N-1 == 0 && M-1 == 0) {
        cout << 1;
    }
    else {
        pre_bfs(0, 0, true);
        pre_bfs(N-1, M-1, false);
        cout << (hasGoal ? goalDist : -1);
    }
}