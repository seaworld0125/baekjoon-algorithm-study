#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
// 원소를 왼쪽 오른쪽 번갈아가면서 작은 순서대로 배치
// 가운데에 제일 큰 놈이 오게됨
// 배치를 완료하고 차이를 확인하려면 
// 원래 배열에서 인덱스 2정도 떨어진 원소의 차이를 조사하면됨
// 2 간격을 두고 원소들의 차이를 계산해서 제일 큰놈이 답
int main(){
    int T, N, result;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        result = 0;
        scanf("%d", &N);
        vector<int> v(N);
        for(int j = 0; j < N; j++){
            scanf("%d", &v[j]);
        }
        sort(v.begin(), v.end());
        for(int j = 0; j < N-2; j++){
            int temp = v[j+2] - v[j];
            result = max(result, temp);
        }
        printf("%d\n", result);
    }
}