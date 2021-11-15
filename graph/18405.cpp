#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;

#define F first
#define S second
#define pii pair<int, int>
#define INF 1e9

int N, K, time, X, Y;

int map[201][201];
queue<pii> space;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

void spread(int y, int x, bool infection[][201]) {
    int virus = INF;
    pii pos;

    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(y_ >= 0 && x_ >= 0 && y_ < N && x_ < N && map[y_][x_] && !infection[y_][x_]) {
            virus = min(virus, map[y_][x_]);
            pos.F = y_;
            pos.S = x_;
        }
    }

    if(virus != INF && !infection[pos.F][pos.S]) {
        map[y][x] = virus;
        infection[y][x] = true;
    }
    else
        space.emplace(y, x);
}

int main() {
    cin >> N >> K;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
            
            if(!map[i][j])
                space.emplace(i, j);
        }

    cin >> time >> X >> Y;

    for(int i = 0; i < time; i++) {
        bool infection[201][201];
        fill(infection[0], infection[0]+40401, false);

        int size = space.size();
        for(int j = 0; j < size; j++) {
            auto pos = space.front();
            space.pop();

            spread(pos.F, pos.S, infection);
        }
    }

    cout << map[X-1][Y-1] << endl;
}