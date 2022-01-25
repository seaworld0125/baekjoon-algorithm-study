#include <iostream>
#include <vector>
using namespace std;

#define F first
#define S second

int R, C, T;
int originalMap[50][50];
vector<int> airCleanerPos;

void airCleaner() {
    int y = airCleanerPos[0];
    originalMap[y - 1][0] = 0;

    int i;
    for(i = y - 1; i - 1 >= 0; i--) originalMap[i][0] = originalMap[i - 1][0];
    for(i = 0; i + 1 < C; i++) originalMap[0][i] = originalMap[0][i + 1];
    for(i = 0; i + 1 <= y; i++) originalMap[i][C - 1] = originalMap[i + 1][C - 1];
    for(i = C - 1; i - 1 > 0; i--) originalMap[y][i] = originalMap[y][i - 1];
    originalMap[y][1] = 0;

    y = airCleanerPos[1];
    originalMap[y + 1][0] = 0;
    
    for(i = y + 1; i + 1 < R; i++) originalMap[i][0] = originalMap[i + 1][0];
    for(i = 0; i + 1 < C; i++) originalMap[R - 1][i] = originalMap[R - 1][i + 1];
    for(i = R - 1; i - 1 >= y; i--) originalMap[i][C - 1] = originalMap[i - 1][C - 1];
    for(i = C - 1; i - 1 > 0; i--) originalMap[y][i] = originalMap[y][i - 1];
    originalMap[y][1] = 0;
}

bool checkRange(int y, int x) {
    return x >= 0 && x < C && y >= 0 && y < R && originalMap[y][x] != -1;
}

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void spread() {
    vector<pair<pair<int, int>, int>> dustInfo;

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(originalMap[i][j] <= 0) continue;

            int spreadAmount = originalMap[i][j] / 5;
            int count = 0;

            for(int k = 0; k < 4; k++) {
                if(checkRange(dy[k] + i, dx[k] + j)) {
                    dustInfo.push_back({{dy[k] + i, dx[k] + j}, spreadAmount});
                    count++;
                }
            }
            originalMap[i][j] -= spreadAmount * count;
        }
    }

    for(int i = 0; i < dustInfo.size(); i++) {
        auto pos = dustInfo[i].F;
        int amount = dustInfo[i].S;

        originalMap[pos.F][pos.S] += amount;
    }
}

int main() {
    cin >> R >> C >> T;

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> originalMap[i][j];

            if(originalMap[i][j] == -1)
                airCleanerPos.emplace_back(i);
        }
    }

    for(int i = 0; i < T; i++) {
        spread();
        airCleaner();
    }

    int ans = 0;

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++) 
            ans += (originalMap[i][j] > 0 ? originalMap[i][j] : 0);
    
    cout << ans;
}