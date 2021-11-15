#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 1e9

vector<vector<int>> v(20001);
bool visit[20001] = {false};

int N, M;

void BFS() {
    queue<int> q;
    q.emplace(1);
    visit[1] = true;

    int pos;
    int dist = -1;
    int count;

    while(!q.empty()) {
        pos = INF;
        dist++;
        count = q.size();

        for(int i = 0; i < count; i++) {
            int p = q.front(); q.pop();
            pos = min(pos, p);

            for(int j = 0; j < v[p].size(); j++) {
                int tmp = v[p][j];
                if(!visit[tmp]) {
                    visit[tmp] = true;
                    q.emplace(tmp);
                }
            }
        }
    }

    cout << pos << ' ' << dist << ' ' << count;
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        int A_i, B_i;

        cin >> A_i >> B_i;

        v[A_i].emplace_back(B_i);
        v[B_i].emplace_back(A_i);
    }
    
    BFS();
}