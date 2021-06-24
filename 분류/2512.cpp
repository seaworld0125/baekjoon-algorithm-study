#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

int N, MaxBudget;
ll M;
int arr[11111];

ll Sum(int x) {
	ll sum = 0LL;
	for (int i = 0; i < N; ++i)
		sum += min(arr[i], x);

	return sum;
}

int th() {
	int st = 1;
	int ed = MaxBudget; // 최대 예산값
	int ans = 1;
	// st 이상 ed 이하
	while (st <= ed) {
		int mid = (st + ed) / 2;
		if (Sum(mid) <= M) { // 가능한 값이면
			ans = mid; // 저장
			st = mid + 1; // 작은 값을 이동
		}
		else // 불가능한 값이면
			ed = mid - 1; // 큰 값을 이동
	}
	return ans;
}

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
        MaxBudget = max(MaxBudget, arr[i]);
    }
    cin >> M;
    cout << th();
    return 0;
}