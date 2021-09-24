//이분 탐색으로 푸는 LIS / 최장 증가 부분 수열

#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
using namespace std;

int n;
int arr[40001];
int lis[40001];

// LIS를 유지하기 위해 숫자가 들어갈 위치를 이분탐색으로 찾는 함수
int binarysearch(int left, int right, int target) {
	int mid;
    // lis 배열에 들어갈 target=arr[i]의 위치를 이분탐색으로 찾기
	while (left < right) {
		mid = (left + right) / 2; // 중간값 설정
		if (lis[mid] < target) { 
			left = mid + 1;
		}else {
			right = mid;
		}
	}
	return right;
}

int main() {ios::sync_with_stdio(0); cin.tie(0);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	int size = 0;
	lis[0] = arr[0]; // lis 배열의 맨 첫번째 값은 arr[0]으로 초기화

	// arr의 두번째부터 마지막까지 하나씩 lis와 비교하면서 넣어준다.
	for(int i = 1; i < N; i++) {
        if (lis[size] < arr[i]) {   // lis 배열의 맨 뒤의 값보다 arr[i]가 더 크면 그것을 lis 배열 맨 뒤에 넣어준다.
			lis[size + 1] = arr[i];
			size += 1;
		}else {  // arr[i]값이 더 작으면, arr[i]의 값이 lis 배열 중 어느 곳에 들어올지 이분탐색한다.
            // 0부터 size까지 탐색하면서 arr[i]가 들어갈 수 있는 위치를 찾아서 idx에 반환
			int idx = binarysearch(0, size, arr[i]);
			lis[idx] = arr[i];
		}
	}
    for(int i = 0; i < size+1; i++){
        cout << lis[i] << ' ';
    }cout << endl;
	cout << size + 1;
	return 0;
}