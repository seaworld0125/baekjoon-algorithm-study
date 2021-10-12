#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
#define endl '\n'

char map[12][6];

int px[4] = {-1, 0, 1, 0}; //왼아오위
int py[4] = {0, 1, 0, -1};

// sy = start y
// sx = start x
// sc = start char
bool BFS(int sy, int sx, char sc){
    bool visit[12][6];
    // 초기화 꼭 해라.........
    memset(visit, false, sizeof(visit));
    // y, x
    queue<pair<int, int>> q; 
    vector<pair<int, int>> v;

    q.push({sy, sx});
    v.push_back({sy, sx});
    visit[sy][sx] = true;
    
    while(!q.empty()){
        // vy = visit y
        // vx = visit x
        int vy = q.front().first, vx = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            // ty = temp y
            // tx = temp x
            int ty = vy + py[i], tx = vx + px[i];
            if(ty >= 0 && ty < 12 && tx >= 0 && tx < 6){
                if(!visit[ty][tx] && map[ty][tx] == sc){
                    q.push({ty, tx});
                    v.push_back({ty, tx});
                    visit[ty][tx] = true;
                }
            }
        }
    }
    int size = v.size();
    if(size > 3){
        for(int i = 0; i < size; i++){
            int ty = v[i].first, tx = v[i].second;
            map[ty][tx] = '.';
        }
        return true;
    }
    return false;
}
queue<char> que;
void gravity(){
    for(int j = 0; j < 6; j++){
        for(int i = 11; i >= 0; i--){
            if(map[i][j] == '.'){
                for(int k = i-1; k >= 0; k--){
                    if(map[k][j] != '.'){
                        que.push(map[k][j]);
                        map[k][j] = '.';
                    }
                }
                int size = que.size();
                for(int k = 0; k < size; k++, i--){
                    if(que.empty()) break;
                    map[i][j] = que.front();
                    que.pop();
                }
            }
        }
    }
}
void input(){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 6; j++){
            cin >> map[i][j];
        }
    }
}
void solve(){
    int answer = 0;
    input();
    while(1){
        // 폭발 발생 여부
        bool boom = false;
        for(int i = 11; i >= 0; i--){
            for(int j = 0; j < 6; j++){
                if(map[i][j] != '.'){
                    if(BFS(i, j, map[i][j])){
                        boom = true;
                    }
                }
            }
        }
        if(boom){
            answer++;
            gravity();
        }else{
            break;
        }
    }
    cout << answer;
}
int main(){
    solve();
}
