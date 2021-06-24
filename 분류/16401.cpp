#include <iostream>
#include <algorithm>
using namespace std;

int arr[1000001];
int M;  //조카의 수
int N;  //과자의 수
int ans;

int BS(int left, int right, int max, int n){//0,10,15,2
    int mid;
    while(left <= right){
        cout << ':' << left << '\n';
		int mid = (left + right) / 2;
		if (mid*n <= max) { // 가능한 값이면
			ans = mid; // 저장
			left = (mid/n) + 1; // 작은 값을 이동
		}
		else // 불가능한 값이면
			right = mid; // 큰 값을 이동        
    }
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }sort(arr, arr+N-1);
    if(M <= N){
        ans = arr[N-M];
    }else{
        int right, max, split_n;
        right = arr[0];
        max = arr[N-1];
        split_n = M-(N-1);
        cout << right << ',' << max << ',' << split_n << '\n';
        BS(0, right, max, split_n);
    }
    cout << ans;
}