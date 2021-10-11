#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, x, y, start, end, ans = 0;
    pair<int, int> pos[1000001];

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> x >> y;
        pos[i].first = x, pos[i].second = y;
    }

    sort(pos, pos + N);

    start = pos[0].first, end = pos[0].second;
    for(int i = 1; i < N; i++) {
        if(end >= pos[i].first) end = max(end, pos[i].second);
        else {
            ans += (end-start);
            start = pos[i].first, end = pos[i].second;
        }
    }
    ans += (end-start);
    cout << ans;
}