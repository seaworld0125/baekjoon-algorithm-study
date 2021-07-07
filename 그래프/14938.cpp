
//---->>>> BFS 로 풀고 보기좋게 실패
//---->>>> 간선에 가중치가 있어서 못 풀어요~

#include <iostream>
#include <algorithm>
#include <queue>
#define endl '\n'
using namespace std;

int item[101] = {0};
int cost[101][101];
int n, m, r;

int BFS(int pos){           
    int dist[101];   
    bool visit[101][101] = {0};
    int max_item = 0;
    dist[pos] = 0;    //이전 노드까지의 누적 거리 정보 저장
    
    queue<int> q;
    q.push(pos);

    while(!q.empty()){
        pos = q.front();   
        q.pop();
        max_item += item[pos];  //최대 아이템 +
        for(int i = 1; i <= n; i++){    //갈 수 있는 곳만 큐에 담기
            if(cost[pos][i] != -1 && !visit[pos][i] && dist[pos] + cost[pos][i] <= m){
                q.push(i);
                dist[i] = dist[pos] + cost[pos][i];  //거리 누적
                visit[pos][i] = true;
            }
        }
    }
    return max_item;
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> r;
    for(int i = 1; i <= n; i++){
        cin >> item[i];
    }
    for(int i = 0; i < 101; i++){
        for(int j = 0; j  <101; j++){
            cost[i][j] = -1;
        }
    }
    for(int i = 0; i < r; i++){ 
        int a, b, l;
        cin >> a >> b >> l;
        cost[a][b] = l;
        cost[b][a] = l;
    }

    int max_item = 0;
    for(int i = 1; i <= n; i++){
        max_item = max(BFS(i), max_item);
    }
    cout << max_item;
}