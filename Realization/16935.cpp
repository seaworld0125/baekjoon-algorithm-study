#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N, M, R;
int now_n, now_m;
int ** map;
int ** tmp;
vector<int> r(1001);

void upDown() {
    for(int i = 0; i < now_m; i++)
        for(int j = 0; j < now_n; j++)
            tmp[j][i] = map[now_n - j - 1][i];
}
void leftRight() {
    for(int i = 0; i < now_n; i++)
        for(int j = 0; j < now_m; j++)
            tmp[i][j] = map[i][now_m - j - 1];
}
void rotateP90() {
    for(int i = 0; i < now_n; i++) 
        for(int j = 0; j < now_m; j++) 
            tmp[i][j] = map[now_m - 1 - j][i];
}
void groupRotateP90() {
    int n = now_n / 2;
    int m = now_m / 2;
    int dx[] = {m, 0, -m, 0};
    int dy[] = {0, n, 0, -n};
    int px[] = {0, m, m, 0};
    int py[] = {0, 0, n, n};

    for(int i = 0; i < 4; i++) {
        for(int j = py[i]; j < py[i] + n; j++) {
            for(int k = px[i]; k < px[i] + m; k++) {
                tmp[dy[i] + j][dx[i] + k] = map[j][k];
            }
        }
    }
}
void groupRotateM90() {
    int n = now_n / 2;
    int m = now_m / 2;
    int dx[] = {0, m, 0, -m};
    int dy[] = {n, 0, -n, 0};
    int px[] = {0, 0, m, m};
    int py[] = {0, n, n, 0};

    for(int i = 0; i < 4; i++) {
        for(int j = py[i]; j < py[i] + n; j++) {
            for(int k = px[i]; k < px[i] + m; k++) {
                tmp[dy[i] + j][dx[i] + k] = map[j][k];
            }
        }
    }
}
void getMemory(int n = now_n, int m = now_m) {
    tmp = new int * [n];
    for(int i = 0; i < n; i++) {
        tmp[i] = new int[m];
    }
}
void getRotateMemory(int n = now_n, int m = now_m) {
    tmp = new int * [m];
    for(int i = 0; i < m; i++) {
        tmp[i] = new int[n];
    }
    now_n = m;
    now_m = n;
}
void deleteMemory() {
    for(int i = 0; i < now_n; i++) 
        delete [] map[i];
    delete [] map;
}
void inputMap() {
    cin >> N >> M >> R;

    now_n = N;
    now_m = M;

    map = new int * [N];
    for(int i = 0; i < N; i++) {
        map[i] = new int[M];
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> map[i][j];

    for(int i = 0; i < R; i++)
        cin >> r[i];
}
void solve() {
    for(int i = 0; i < R; i++) {
        if(r[i] == 4) {
            for(int i = 0; i < 3; i++) {
                getRotateMemory();
                rotateP90();
                deleteMemory();
                map = tmp;
            }
            continue;
        }
        else if(r[i] == 3) {
            getRotateMemory();
            rotateP90();
        }
        else {
            getMemory();
            if(r[i] == 1) upDown();
            else if(r[i] == 2) leftRight();
            else if(r[i] == 5) groupRotateP90();
            else if(r[i] == 6) groupRotateM90();
        }
        deleteMemory();
        map = tmp;
    }
    for(int i = 0; i < now_n; i++) {
        for(int j = 0; j < now_m; j++) {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
int main() {
    inputMap();
    solve();
    deleteMemory();

    return 0;
}   