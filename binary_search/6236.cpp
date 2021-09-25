#include <iostream>
using namespace std;

int N, M;
int arr[100000] = {0};

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    int L = 1, R = 100000 * 10000;
    for(int i = 0; i < N; i++) cin >> arr[i];

    int K, mm, nowMoney, i;
    while(L <= R) {
        K = (L+R)/2, mm = 1, nowMoney = K;
        for(i = 0; i < N; i++) {
            if(K < arr[i]) {
                L = K + 1; 
                break;
            }
            else if(nowMoney < arr[i]) {
                nowMoney = K, mm++;
            }
            nowMoney -= arr[i];
        }
        if(i == N && mm <= M) R = K - 1;
    }
    cout << K;
    return 0;
}