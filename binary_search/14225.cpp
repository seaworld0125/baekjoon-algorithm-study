#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 2000001

int N;
int S[20];
bool sum_arr[MAX] = {false};

// 부분 수열
// 수학에서, 부분 수열 또는 부분열은 주어진 수열의 일부 항을 원래 순서대로 나열하여 얻을 수 있는 수열이다. 
// 따라서 원래 수열의 순서를 어기는 수열은 부분 수열이 될 수 없다.

void recursive(int idx, int sum = 0) {
    if(idx == N) return;

    sum += S[idx];
    sum_arr[sum] = true;

    for(int i = idx + 1; i < N; i++) {
        recursive(i, sum);
    }
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) cin >> S[i]; 

    for(int i = 0; i < N; i++) recursive(i);

    for(int i = 1; i < MAX + 1; i++) {
        if(!sum_arr[i]) {
            cout << i;
            return 0;
        }
    }
}