#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define F first
#define S second

int n, m; // 세로 가로
int map[500][500];
int pcount = 0, parea = 0; 

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

int BFS(int y, int x) {
    queue<pair<int, int>> q;
    q.emplace(y, x);
    map[y][x] = 0;

    int area = 1;
    pcount++;

    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {
                int y_ = pos.F + dy[i];
                int x_ = pos.S + dx[i];

                if(x_ >= 0 && x_ < m && y_ >= 0 && y_ < n && map[y_][x_]) {
                    q.emplace(y_, x_);
                    map[y_][x_] = 0;
                    area++;
                }
            }
        }
    }
    return area;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> map[i][j];
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(map[i][j])
                parea = max(parea, BFS(i, j));

    cout << pcount << endl << parea;
}