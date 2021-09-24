#include <iostream>
#define endl '\n'
using namespace std;

int dp[1000000];
int arr[1000000];
int N;
int SIZE = 0;

int binary_search(int begin, int end, int key){
    while(begin < end){
        int mid = (begin + end) / 2;
        if(dp[mid] < key){
            begin = mid+1;
        }else{
            end = mid;  //아마 0떄문에 ??
        }
    }return end;
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    dp[0] = arr[0];
    for(int i = 1; i < N; i++){
        if(dp[SIZE] < arr[i]){
            SIZE += 1;
            dp[SIZE] = arr[i];
        }else{
            dp[binary_search(0, SIZE, arr[i])] = arr[i];
        }
    }
    cout << SIZE + 1;
}