#include <iostream>
using namespace std;

int N, M, arr[10001], L = 1, R = 0, ans;
bool check(int mid, int max) {
    int budget = 0;
    for(int i = 0; i < N; i++) {
        if(mid < arr[i]) budget += mid;
        else budget += arr[i];

        if(budget > M) return false;
    }
    return true;
}
int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
        R = R < arr[i] ? arr[i] : R;
    } cin >> M;

    while(L <= R) {
        int mid = (L+R)/2;
        if(check(mid, M)) { ans = mid; L = mid+1; }
        else R = mid-1;
    }
    cout << ans; 
}