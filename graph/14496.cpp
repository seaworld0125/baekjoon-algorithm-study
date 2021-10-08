#include <iostream>
#include <queue>
#include <vector>
#define end '\n'
using namespace std;

int a, b, N, M;
bool visited[1001] = {false};
vector<int> v[1001];

int BFS(){
    int SIZE, dis = -1;
    bool endFlag = false;
    queue<int> q;
    q.push(a);
    while(!q.empty() && !endFlag){
        SIZE = q.size();
        for(int i = 0; i < SIZE; i++){
            int now = q.front();
            if(now == b){//목표 지점이라면
                endFlag = true;
                break;
            } 
            visited[now] = true;
            q.pop();
            for(int i = 0; i < v[now].size(); i++){//연결된 노드 탐색
                if(!visited[v[now][i]]){           //방문한 적 없는 노드라면
                    q.push(v[now][i]);
                }
            }
        }
        dis++;
    }
    if(endFlag) return dis;
    else return -1;
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> a >> b;
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int c, d;
        cin >> c >> d;
        v[c].push_back(d);
        v[d].push_back(c);
    }
    cout << BFS();
}