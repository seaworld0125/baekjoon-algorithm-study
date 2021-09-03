#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 1e9

// 걷기 1초 후에 : x-1 , x+1
// 순간이동 0초 후에 : 2*x

int N;
int K;
int start;
int goal;

// * - + 방문 여부 저장
bool visited[100001];

int BFS(){
    queue<int> q;
    q.push(start);

    while(!q.empty()){
        int pos = q.front();
        q.pop();

        if(pos == goal){
            return sec;
        }

        if(pos > 0 && !visited[pos*2]){  //...
            visited[pos*2] = true;
            q.push(pos*2);
        }
        if(!visited[pos-1]){
            visited[pos-1] = true;
            q.push(pos-1);
        }
        if(!visited[pos+1]){
            visited[pos+1] = true;
            q.push(pos+1);
        }
    }
    int time = INF;
    int time1 = INF;
    int time2 = INF;
    return min(time, min(time1, time2));
}

void solve(){
    memset(visited, false, sizeof(visited));
    if(N > K){
        start = K;
        goal = N;
    }
    else if(N < K){
        start = N;
        goal = K;
    }
    visited[start] = true;
    visited[start] = true;
    visited[start] = true;

    cout << BFS(start, 0);
}

int main(){
    cin >> N >> K;
    solve();
}