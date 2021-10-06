#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int map[1000][1000];

void solve() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int L = 0, T = 0;
            if(i >= 0 && j-1 >= 0) L = map[i][j-1];
            if(i-1 >= 0 && j >= 0) T = map[i-1][j]; 
            map[i][j] = max(L, T) + map[i][j];
        }
    }
}
int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> map[i][j];

    solve();
    cout << map[N-1][M-1];
}