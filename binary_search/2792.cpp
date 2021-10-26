#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int L = 1, R, N, M, ans, candy[300000];

long long candyCount;

bool check(int mid) {
    long long count = 0;

    for(int i = 0; i < M; i++) {
        count += candy[i] / mid;

        if(candy[i] % mid)
            count++;
    }

    if(N >= count) 
        return true;
    else 
        return false;
}

int main() {
    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        cin >> candy[i];
        
        R = max(R, candy[i]);

        candyCount += candy[i];
    }

    while(L <= R) {
        int mid = ( L + R ) / 2;
        
        if(check(mid)) {
            ans = mid;
            R = mid - 1;
        }
        else
            L = mid + 1;
    }

    cout << ans << endl;
}

// ㄷ