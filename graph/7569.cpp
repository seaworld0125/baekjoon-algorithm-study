#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

// 상자 가로
int M;
// 상자 세로
int N;
// 상자 높이
int H;

int box[101][101][101];
bool visited[101][101][101];

int dx[] = {-1, 0, 1, 0}; //왼 위 오 아
int dy[] = {0, -1, 0, 1};
int dz[] = {-1, 1}; //위 아래

queue<pair<int, pair<int, int>>> q;

int BFS(){
    int day = 0;

    while(!q.empty()){
        int size = q.size();

        bool ripen = false;
        for(int d = 0; d < size; d++){
            pair<int, pair<int, int>> p = q.front();
            q.pop();
            int vz = p.first;
            int vy = p.second.first;
            int vx = p.second.second;
            // 상하좌우
            for(int i = 0; i < 4; i++){
                int ty = vy+dy[i];
                int tx = vx+dx[i];
                if(ty >= 0 && ty < N && tx >= 0 && tx < M && !visited[vz][ty][tx] && box[vz][ty][tx] == 0){
                    q.push({vz, {ty, tx}});
                    box[vz][ty][tx] = 1;
                    ripen = true;
                }
            }// 위아래
            for(int i = 0; i < 2; i++){
                int tz = vz+dz[i];
                if(tz >= 0 && tz < H && !visited[tz][vy][vx] && box[tz][vy][vx] == 0){
                    q.push({tz, {vy, vx}});
                    box[tz][vy][vx] = 1;
                    ripen = true;
                }
            }
        }
        if(ripen) day++;
    }
    return day;
}

int input(){
    cin >> M >> N >> H;

    // 익은, 안익은 토마토 개수
    int ripen = 0;
    int noRipen = 0;

    for(int i = 0; i < H; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < M; k++){
                cin >> box[i][j][k];
                // 익은 토마토는 바로 BFS 큐에 푸쉬
                if(box[i][j][k] == 1){
                    q.push({i, {j, k}});
                    visited[i][j][k] = true;
                    ripen++;
                }
                else if(box[i][j][k] == 0)
                    noRipen++;
            }
        }
    } 
    //안익은 토마토가 없다면
    if(!noRipen){
        return 1;
    }//익은 토마토가 없다면
    else if(ripen == 0){
        return 2;
    }
    else{
        return 3;
    }
}

// solve
int main(){
    int situation = input();
    if(situation == 1){
        cout << 0;
        return 0;
    }
    else if(situation == 2){
        cout << -1;
        return 0;
    }
    else{
        int day = BFS();        

        for(int i = 0; i < H; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < M; k++){
                    // 안익은 토마토 검사
                    if(box[i][j][k] == 0){
                        cout << -1;
                        return 0;
                    }
                }
            }
        }
        cout << day;
    }
    return 0;
}