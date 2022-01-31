#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define Y first
#define X second

int R, C;
char map[51][51];
bool visited[51][51];

pair<int, int> start, goal;
vector<pair<int, int>> water;

int dy[] = {0,0,1,-1};
int dx[] = {1,-1,0,0};

bool checkRange(int y, int x) {
    return !(y < 0 || x < 0 || y >= R || x >= C) && (map[y][x] != 'X');
}

void flood() {
    int size = water.size();
    for(int i = 0; i < size; i++) {
        auto pos = water[i];
        
        for(int j = 0; j < 4; j++) {
            int y = pos.Y + dy[j];
            int x = pos.X + dx[j];

            if(checkRange(y, x) && map[y][x] != 'D' && map[y][x] != '*') {
                map[y][x] = '*';
                water.emplace_back(y, x);
            }
        }
    }
}

int customBfs() {
    queue<pair<int, int>> q;
    q.emplace(start.Y, start.X);
    visited[start.Y][start.X] = true;
    int count = -1;

    while(!q.empty()) {
        count++;
        int size = q.size();

        flood();
        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            for(int j = 0; j < 4; j++) {
                int y = pos.Y + dy[j];
                int x = pos.X + dx[j];

                if(checkRange(y, x) && map[y][x] != '*' && !visited[y][x]) {
                    if(map[y][x] == 'D') return count + 1;
                    visited[y][x] = true;
                    q.emplace(y, x);
                }
            }
        }
    }
    return -1;
}

int main() {
    cin >> R >> C;

    fill(visited[0], visited[0] + 2601, false);

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'D') {
                goal.Y = i;
                goal.X = j;
            }
            else if(map[i][j] == 'S') {
                start.Y = i;
                start.X = j;
            }
            else if(map[i][j] == '*') {
                water.emplace_back(i, j);
            }
        }

    int ans = customBfs();
    if(ans >= 0) cout << ans;
    else cout << "KAKTUS";
}