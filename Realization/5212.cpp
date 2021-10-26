#include <iostream>

using namespace std;

int main() {
    int x1 = 12, x2 = 0;
    int y1 = 12, y2 = 0;

    int R, C;

    char map[12][12];

    cin >> R >> C;
    
    // 맵을 채움
    for(int i = 0; i < 12; i++) {
        if(i == 0 || i > R) 
            for(int j = 0; j < 12; j++) 
                map[i][j] = '.';
        else
            for(int j = 0; j < 12; j++) {
                if(j == 0 || j > C)
                    map[i][j] = '.';
                else 
                    cin >> map[i][j];
            }
    }

    // 섬 조사
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            if(map[i][j] == 'X') {
                // 주변 조사
                int seas = 0;
                if(map[i-1][j] == '.') seas++;
                if(map[i+1][j] == '.') seas++;
                if(map[i][j+1] == '.') seas++;
                if(map[i][j-1] == '.') seas++;

                if(seas >= 3) map[i][j] = 'o';
                else {
                    // 출력 맵 사이즈 업데이트
                    if(i < y1) y1 = i;
                    if(i > y2) y2 = i;
                    if(j < x1) x1 = j;
                    if(j > x2) x2 = j;
                }
            }
        }
    }

    // 답 출력
    for(int i = y1; i <= y2; i++) {
        for(int j = x1; j <= x2; j++) {
            if(map[i][j] == 'o') 
                cout << '.';
            else 
                cout << map[i][j];
        }
        cout << endl;
    }
}

// 43