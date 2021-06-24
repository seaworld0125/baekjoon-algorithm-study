#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(int & a, int & b){
    return a > b;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    vector<int> v(N);
    for(int i = 0; i < N; i++){
        scanf("%d", &v[i]);
    }
    vector<int> v2(N-1);
    for(int i = 0; i < N-1; i++){
        v2[i] = v[i+1]-v[i];
    }sort(v2.begin(), v2.end(), cmp);
    int sum = 0;
    for(int i = K-1; i < N-1; i++){
        sum += v2[i];
    }printf("%d", sum);
}