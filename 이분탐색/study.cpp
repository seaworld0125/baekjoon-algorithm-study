#include <iostream>
#include <algorithm>
using namespace std;

#define endl '\n'

int binary_search_recursive(int * arr, int begin, int end, int target){     //이분 탐색 //재귀로 구현 
    if(begin > end){
        return -1;
    }
    int mid = (begin + end)/2;
    if(target == arr[mid])
        return mid;
    else if(target < arr[mid]) 
        return binary_search_recursive(arr, begin, mid-1, target);
    else
        return binary_search_recursive(arr, mid+1, end, target);
}
int binary_search_while(int * arr, int begin, int end, int target){     //이분 탐색 //반복문으로 구현
    while(begin <= end){
        int mid = (begin + end)/2;
        if(target == arr[mid])
            return mid;
        else if(target < arr[mid]) 
            end = mid-1;
        else
            begin = mid+1;
    }
    return -1;
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    int arr[] = {2, 2, 2, 2, 2, 3, 4, 5};

    //C++ STL 사용
    int upp_index = upper_bound(arr, arr+7, 4) - arr;     //이분 탐색 기반 // KEY 값보다 (큰) 최초의 원소를 반환함
    int low_index = lower_bound(arr, arr+7, 4) - arr;     //이분 탐색 기반 // KEY 값보다 (같거나 큰) 최초의 원소를 반환함
    cout << upp_index << endl;
    cout << low_index << endl;

    bool search_index_stl = binary_search(arr, arr+7, 3); //이분탐색 //참 거짓만 반환함
    cout << search_index_stl << endl;

    //binary_search 구현 //탐색 실패 시 -1 반환
    int search_index_recursive = binary_search_recursive(arr, 0, 7, 3);
    cout << search_index_recursive << endl;
    int search_index_while = binary_search_while(arr, 0, 7, 3);
    cout << search_index_while << endl;
}