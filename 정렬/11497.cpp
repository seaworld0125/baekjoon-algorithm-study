#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
// ���Ҹ� ���� ������ �����ư��鼭 ���� ������� ��ġ
// ����� ���� ū ���� ���Ե�
// ��ġ�� �Ϸ��ϰ� ���̸� Ȯ���Ϸ��� 
// ���� �迭���� �ε��� 2���� ������ ������ ���̸� �����ϸ��
// 2 ������ �ΰ� ���ҵ��� ���̸� ����ؼ� ���� ū���� ��
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