#include <iostream>
using namespace std;

int N, M;
int arr[100000] = {0};

bool check(int mid) {
    int count = 1, money = mid;
    for(int i = 0; i < N; i++) {
        if(mid < arr[i]) return false;
        if(money < arr[i]) {
            count += 1;
            money = mid;
        }
        money -= arr[i];
    }
    return count <= M;
}
int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    int L = 1, R = 100000 * 10000, mid = 0, answer = 0;
    for(int i = 0; i < N; i++) cin >> arr[i];

    while(L <= R) {
        mid = (L+R)/2;
        if(check(mid)) answer = mid, R = mid-1;
        else L = mid + 1;
    }
    cout << answer;
}