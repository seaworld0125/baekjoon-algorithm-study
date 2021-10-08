#include <iostream>
#include <utility>
#define endl '\n'
using namespace std;

int M, N;                       //목적지 (x,y) //맵 크기
char cost[101][101] = {0};      //비용

int m_x[2] = {0, 1};        //아래 오른쪽
int m_y[2] = {1, 0}; 

int func(int x, int y){
    if(x == M && y == N) return 0;

    int i, a = 0, cost1, cost2;
    bool p1f = false, p2f = false;
    pair<int, int> p1 = make_pair(-1, -1);
    pair<int, int> p2 = make_pair(-1, -1);
    int x1 = x+m_x[0], x2 = x+m_x[1];
    int y1 = y+m_y[0], y2 = y+m_y[1];
    
    if(cost[y][x] == '1') a = 1;

    if(x1 <= M && y1 <= N){
        p1 = make_pair(x1, y1); p1f=true;    
        cost1 = a + func(p1.first, p1.second);
    }
    if(x2 <= M && y2 <= N){
        p2 = make_pair(x2, y2); p2f=true;
        cost2 = a + func(p2.first, p2.second);
    }
    if(p1f && p2f){
        if(cost1 <= cost2) return cost1;
        else return cost2;
    }else if(p1f){
        return cost1;
    }else{
        return cost2;
    }
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            cin >> cost[i][j];
        }
    }  
    cout << func(1, 1);
}