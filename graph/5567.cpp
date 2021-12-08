#include <iostream>
using namespace std;

bool rel[501][501]; // [본인][친구] 와의 관계
bool invite[501] = {false};
int ans = 0;

int main() {
    fill(rel[0], rel[0] + 250000, false);

    int n, m;
    cin >> n;
    cin >> m;

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        rel[a][b] = true;
        rel[b][a] = true;
    }

    for(int i = 2; i <= n; i++) {
        if(rel[1][i]) {
            invite[i] = true;

            for(int j = 2; j <= n; j++) 
                if(rel[i][j])
                    invite[j] = true; 
        }
    }

    for(int i = 2; i <= n; i++)
        if(invite[i])
            ans++;

    cout << ans;
}