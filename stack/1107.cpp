#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N, M;
int ans;

bool brokenButtonList[10];

int check(int target) {
    int share = target / 10, count = 0;
    do
    {
        if(brokenButtonList[target % 10]) {
            target = share;
            share /= 10;
            count++;
        }
        else return 0;
    } while (target);

    return count;
}

int main() {
    fill(brokenButtonList, brokenButtonList + 10, false);

    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        int tmp;
        cin >> tmp;
        brokenButtonList[tmp] = true;
    }

    if(N == 100) { // 이동할 필요 없음
        cout << 0;
        return 0;
    }
    
    ans = abs(N - 100);
    for(int i = 0; i <= 10000000; i++) {
        int now = i, count;

        if(count = check(now))
            ans = min(ans, abs(N - now) + count);
    }   
    cout << ans;
}