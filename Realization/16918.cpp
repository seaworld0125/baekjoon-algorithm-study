#include <iostream>
#include <vector>
using namespace std;

#define F first
#define S second

int R, C, N;
int map[201][201];

bool check(int y, int x, int phase) {
    return (y >= 0 && x >= 0 && y < R && x < C) && map[y][x] == phase;
}

int getNextPhase(int phase) {
    int phase_ = phase + 1; 
    if(phase_ == 3) phase_ = 1;
    return phase_;
}

int main() {
    cin >> R >> C >> N;

    int time = 1, phase = 1;
    // 0, 1
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            char tmp;
            cin >> tmp;

            if(tmp == '.') map[i][j] = 0;
            else map[i][j] = phase;
        }
    }
    phase++;

    // 반복
    while(time < N) {
        // 2 채우기
        for(int i = 0; i < R; i++)
            for(int j = 0; j < C; j++) 
                if(!map[i][j]) map[i][j] = phase;
                
        phase = getNextPhase(phase);
        
        time += 1;
        if(time >= N) break;     

        // 3 터뜨리기
        vector<pair<int, int>> v;
        int nextPhase = getNextPhase(phase);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                if(map[i][j] == nextPhase) { // 같이 터지는 다음 페이즈 폭탄이면 미리 터뜨림
                    if(check(i + 1, j, phase)
                    || check(i - 1, j, phase)
                    || check(i, j + 1, phase)
                    || check(i, j - 1, phase)) map[i][j] = 0;
                } // 이번 페이즈에 터지는 폭탄 위치 저장
                else if(map[i][j] == phase) v.emplace_back(i, j);
            }
        }
        for(int i = 0; i < v.size(); i++) map[v[i].first][v[i].second] = 0;
                    
        time += 1;
    }

    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << (map[i][j] ? 'O' : '.');
        }cout << endl;
    }
}