#include <iostream>
#include <algorithm>
using namespace std;
int M, N;   //M : 조카 수, N : 과자 수
int snack[1000001];

bool possible(int len){
        int cnt = 0;
        for (int i = 0; i < N; i++) {cnt += snack[i] / len;}

        //조건이 성립할 경우에만 true
        if (cnt >= M) return true;
        else return false;
}
int main(void){
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin.tie(0);
    cin >> M >> N;
    int low = 1, high = 0;

    for (int i = 0; i < N; i++){
        cin >> snack[i];
        high = max(high, snack[i]); //제일 긴 과자길이
    }
    int result = 0;

    //이분 탐색
    while (low <= high){
        int mid = (low + high) / 2;
        if (possible(mid)){
                result = mid;
                low = mid + 1;
        }
        else high = mid - 1;
    }
    cout << result << "\n";
    return 0;
}