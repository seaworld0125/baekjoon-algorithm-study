#include <iostream>
using namespace std;

int arr[100000] = {0};
int N, M, mid, L = 1, R = 100000 * 10000, ans = 0;

bool check() {
    int m = 1, space = mid;
    for(int i = 0; i < N; i++) {
        if(mid < arr[i]) return false;
        if(space < arr[i]) space = mid, m++;
        space -= arr[i];
        if(m > M) return false;
    }
    return m <= M;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> arr[i];

    while(L <= R) {
        mid = (L+R)/2;
        if(check()) ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    cout << ans;
}