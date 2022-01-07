#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool remote[10];
bool canRemote = true;

int check(int target) {
    int share = target / 10;
    do
    {
        if(remote[target % 10]) {
            target = share;
            share /= 10;
        }
        else return false;
    } while (target);

    return true;
}

int findClosedNum(int base, int target) {
    int high = base, low = base;
    while(1) {
        if(canRemote && check(high)) break;
        if(high == target) break;
        high++;
    }
    while(low >= 0) {
        if(canRemote && check(low)) break;
        if(low == target) break;
        low--;
    }

    return (high - base < base - low)
}

int main() {
    int NOW = 100, ans = 1e9;
    int N, M, temp;
    fill(remote, remote + 10, true);

    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        cin >> temp;
        remote[temp] = false; 
    }
    if(M == 10) canRemote = false;

    if(N == NOW) {
        cout << 0;
        return 0;
    }


}