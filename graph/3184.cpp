#include <iostream>
#include <queue>
using namespace std;

#define F first
#define S second

int R, C;
pair<int, int> answer = {0, 0};

char map[250][250];
bool visited[250][250];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

void BFS(int y, int x) {
    visited[y][x] = true;

    int sheep = 0;
    int wolf = 0;

    if(map[y][x] == 'o') 
        sheep++;
    else if(map[y][x] == 'v') 
        wolf++;

    queue<pair<int, int>> q;
    q.push({y, x});

    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop();

            for(int j = 0; j < 4; j++) {
                int y_ = pos.F + dy[j];
                int x_ = pos.S + dx[j];

                if(y_ >= 0 && y_ < R && x_ >= 0 && x_ < C && !visited[y_][x_]) {
                    visited[y_][x_] = true;
                    q.push({y_, x_});

                    if(map[y_][x_] == 'o') 
                        sheep++;
                    else if(map[y_][x_] == 'v')
                        wolf++;
                }
            }
        }
    }

    if(sheep > wolf)
        answer.F += sheep;
    else
        answer.S += wolf;
}

int main() {
    fill(visited[0], visited[0]+62500, false);

    cin >> R >> C;

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++) {
            cin >> map[i][j];
            
            if(map[i][j] == '#') 
                visited[i][j] = true;
        }

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++) 
            if(visited[i][j] == false) 
                BFS(i, j);
    
    cout << answer.F << ' ' << answer.S;
}