#include <iostream>
#include <cstring>
using namespace std;

int N, M, K;
int R, C;

int note[40][40];

int ** rotate(int ** arr, int R, int C) {
    int ** tmp = new int * [C];
    for(int i = 0; i < C; i++)
        tmp[i] = new int [R];

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            tmp[j][R-i-1] = arr[i][j];

    for(int i = 0; i < R; i++)
        delete[] arr[i];
    delete[] arr;
        
    return tmp;
}

bool can_stick(int ** sticker, int R, int C) {
    for(int i = 0; i <= N-R; i++) { 
        for(int j = 0; j <= M-C; j++) {

            bool fail = false;
            for(int k = 0; k < R && !fail; k++)
                for(int l = 0; l < C && !fail; l++)
                    if(note[i+k][j+l] + sticker[k][l] > 1)
                        fail = true;
            
            if(!fail) {
                for(int k = 0; k < R; k++)
                    for(int l = 0; l < C; l++)
                        note[i+k][j+l] += sticker[k][l];
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> N >> M >> K;

    fill(note[0], note[0]+1600, 0);
    
    for(int i = 0; i < K; i++) {
        cin >> R >> C;
        
        int ** sticker = new int * [R];
        for(int i = 0; i < R; i++)
            sticker[i] = new int [C];

        for(int j = 0; j < R; j++)
            for(int k = 0; k < C; k++)
                cin >> sticker[j][k];

        for(int j = 0; j < 4; j++) { // 총 4번 확인
            if(can_stick(sticker, R, C)) break;

            sticker = rotate(sticker, R, C);   
            int tmp = R;
            R = C;
            C = tmp; 
        }   

        for(int i = 0; i < R; i++)
            delete[] sticker[i];
        delete[] sticker;
    }

    int ans = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(note[i][j]) ans++;

    cout << ans;
}