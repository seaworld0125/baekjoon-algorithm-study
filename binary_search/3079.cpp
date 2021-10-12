#include <iostream>
using namespace std;

long long time[1000001], N, M;

bool check(long long & mid) {
    // cout << "mid :" << mid << endl;
    long long max = 0;
    for(int i = 0; i < N; i++) {
        max += mid/time[i];
        if(max >= M) return true;
    }
    return false;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> time[i];

    long long mid, L = 1, R = 1e18+1, ans = 1e18+1;

    while(L <= R) {
        mid = (L+R)/2;
        if(check(mid)) {R = mid-1; ans = ans > mid ? mid : ans;}
        else L = mid+1;
    }
    cout << ans;
}