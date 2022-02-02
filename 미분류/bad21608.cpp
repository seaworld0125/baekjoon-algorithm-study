#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define PII pair<int,int>
#define F first
#define S second

#define LEN 21
#define MAX 441

int N;
int map[LEN][LEN];
int vacancyMap[LEN][LEN];
int likeMap[LEN][LEN];
vector<int> order(MAX);
vector<PII> pos(MAX, {-1, -1});
vector<vector<int>> relation(MAX, vector<int>(4));

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

void setting() {
    fill(map[0], map[0] + MAX, -1);
    fill(vacancyMap[0], vacancyMap[0] + MAX, 4);
    fill(likeMap[0], likeMap[0] + MAX, 0);
    
    for(int i = 1; i < N - 1; i++) {
        vacancyMap[0][i] = 3;
        vacancyMap[N - 1][i] = 3;
        vacancyMap[i][0] = 3;
        vacancyMap[i][N - 1] = 3;
    }
    vacancyMap[0][0] = 2;
    vacancyMap[0][N - 1] = 2;
    vacancyMap[N - 1][0] = 2;
    vacancyMap[N - 1][N - 1] = 2;

    // cout << "*******************SET*******************\n";
    // for(int j = 0; j < N; j++) {
    //     for(int k = 0; k < N; k++) {
    //         cout << vacancyMap[j][k] << ' ';
    //     }cout << '\n';
    // }
}

bool checkRange(int y, int x) {
    return (y < 0 || x < 0 || y >= N || x >= N);
}

void modVacancyMap(int y, int x) {
    vacancyMap[y][x] = -1;
    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(checkRange(y_, x_)) continue;

        vacancyMap[y_][x_] -= 1;
    }
}

void modLikeMap(int y, int x, int pref) {
    likeMap[y][x] = pref;
    if(!pref) return;

    for(int i = 0; i < 4; i++) {
        int y_ = y + dy[i];
        int x_ = x + dx[i];

        if(checkRange(y_, x_)) continue;

        int friendNum = map[y_][x_];
        if(friendNum == -1) continue;

        for(int j = 0; j < 4; j++) {
            if(relation[friendNum][j] == map[y][x]) {
                likeMap[y_][x_] += 1;
            }
        }
    }
}

int solution() {
    map[1][1] = order[0]; // 첫 번째 학생 앉히기
    pos[order[0]] = {1, 1};
    modVacancyMap(1, 1);

    for(int i = 1; i < N * N; i++) {
        int seats[LEN][LEN]; // 자리 선호도 맵
        fill(seats[0], seats[0] + MAX, 0);

        PII bestSeat = {-1, -1};
        int bestSeatPref = 0;
        for(int j = 0; j < 4; j++) { // 친한 친구와 가까운 자리를 고르는 작업
            int friendNum = relation[order[i]][j];
            auto friendPos = pos[friendNum];

            if(friendPos.F == -1) continue; // 좋아하는 친구 자리가 아직 정해지지 않았다면 넘어간다

            for(int k = 0; k < 4; k++) {
                int y = friendPos.F + dy[k];
                int x = friendPos.S + dx[k];

                if(checkRange(y, x) || map[y][x] != -1) continue;

                seats[y][x] += 1;
            }
        }
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                if(seats[j][k] > bestSeatPref) {
                    bestSeat = {j, k};
                    bestSeatPref = seats[j][k];
                }
                else if(seats[j][k] == bestSeatPref) { // 1번 조건을 만족하는 칸이 여러개인 경우
                    if(vacancyMap[j][k] > vacancyMap[bestSeat.F][bestSeat.S]) { // 주변 빈자리 비교
                        bestSeat.F = j;
                        bestSeat.S = k;
                    }
                    else if(vacancyMap[j][k] == vacancyMap[bestSeat.F][bestSeat.S]) { 
                        if(bestSeat.F > j) {
                            bestSeat.F = j;
                            bestSeat.S = k;
                        }
                        else if(bestSeat.F == j && bestSeat.S > k) {
                            bestSeat.S = k;
                        }
                    }
                    // if(order[i] == 7) {
                    //     cout << "\n";
                    //     cout << "y, x :" << j << ", " << k << endl; 
                    //     cout << "bestSeat :" << bestSeat.F << ", " << bestSeat.S << endl;
                    // }
                }
            }
        }
        // if(order[i] == 7) {
            // cout << "**********************************************\n";
            // for(int j = 0; j < N; j++) {
            //     for(int k = 0; k < N; k++) {
            //         cout << vacancyMap[j][k] << ' ';
            //     }cout << '\n';
            // }
        // }
        // if(!bestSeatPref) {
        //     int bestVacancy = -1;
        //     for(int j = 0; j < N; j++) {
        //         for(int k = 0; k < N; k++) {
        //             if(bestVacancy < vacancyMap[j][k]) {
        //                 bestVacancy = vacancyMap[j][k];
        //                 bestSeat = {j, k};
        //             }
        //         }
        //         if(bestVacancy == 4) break;
        //     }
        // }
        map[bestSeat.F][bestSeat.S] = order[i];
        pos[order[i]] = {bestSeat.F, bestSeat.S};
        modVacancyMap(bestSeat.F, bestSeat.S);
        modLikeMap(bestSeat.F, bestSeat.S, bestSeatPref);

        // cout << "----------------------------------------------\n";
        // cout << "order : " << order[i] << endl;
        // cout << "best y, x : " << bestSeat.F << ", " << bestSeat.S << endl;
        // cout << "?? : " << map[bestSeat.F][bestSeat.S] << endl;
        // for(int j = 0; j < N; j++) {
        //     for(int k = 0; k < N; k++) {
        //         if(map[j][k] == -1) cout << "  ";
        //         else cout << map[j][k] << ' ';
        //     }cout << '\n';
        // }
        // cout << "**********************************************\n";
        // for(int j = 0; j < N; j++) {
        //     for(int k = 0; k < N; k++) {
        //         if(likeMap[j][k] == 0) cout << "  ";
        //         else cout << likeMap[j][k] << ' ';
        //     }cout << '\n';
        // }
    }

    int ans = 0;
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < N; j++) 
            if(likeMap[i][j] >= 1) ans += (int)pow(10, (likeMap[i][j] - 1));

    cout << ans;
}

int main() {
    cin >> N;
    for(int i = 0; i < N * N; i++) {
        cin >> order[i];

        for(int j = 0; j < 4; j++)
            cin >> relation[order[i]][j];
    }
    setting();
    solution();
}