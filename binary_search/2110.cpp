#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, C;
// 집 좌표 저장
vector<int> pos;
// temp pos 저장
// queue<int> tempPos;
// center pos 저장
vector<int> centerPos;
// sub 오름차순 저장
priority_queue<int, vector<int>, greater<int>> subArr;

int getSub(int l, int r, int c) {
    return min(pos[c] - pos[l], pos[r] - pos[c]);
}

void binarySearch(int l, int r, int c, int count_) {
    if(l > c || r < c) return;
    
    int sub = getSub(l, r, c);

    // if(sub < getSub(l, r, c-1)){
    //     binarySearch(l, r, c-1, count_);
    //     return;
    // }
    int c1 = c-1;
    if(sub < getSub(l, r, c1))
        while(sub < getSub(l, r, c1) && c1 >= l) c1 -= 1;

    // if(sub < getSub(l, r, c+1)){
    //     binarySearch(l, r, c+1, count_);
    //     return;
    // }
    int c2 = c+1;
    if(sub < getSub(l, r, c2))
        while(sub < getSub(l, r, c2) && c2 <= r) c2 += 1;

    if(getSub(l,r,c1) < getSub(l,r,c2)) c1 = c2;
    if(sub < getSub(l,r,c1)) c = c1;


    if(count_ == C-2) {
        centerPos.emplace_back(c);
        return;
    }
    // tempPos.push(c);

    // int size = tempPos.size();
    // for(int i = 0; i < size; i++) {
    //     int tmp = tempPos.front();
    //     tempPos.pop();
    //     binarySearch(l, tmp, (tmp+l)/2, count_+1);
    //     if(centerPos.size() > 0)
    //         binarySearch(centerPos[centerPos.size()-1], r, (r+tmp)/2, count_+1);
    // }
    binarySearch(l, c, (c+l)/2, count_+1);
    if(centerPos.size() > 0)
        binarySearch(centerPos[centerPos.size()-1], r, (r+c)/2, count_+1);
}

void solution() {
    if(N == C){
        cout << 1;
        return; 
    }
    if(C == 2){
        cout << pos[pos.size()-1] - pos[0]; 
        return;
    }
    binarySearch(0, pos.size()-1, pos.size()/2, 1);
    int prev = pos[0], tmp;
    for(int i = 0; i < centerPos.size(); i++) {
        tmp = pos[centerPos[i]];
        subArr.push(tmp-prev);
        prev = tmp;
    }
    subArr.push(pos[pos.size()-1]-prev);

    cout << subArr.top();
}

int main() {
    cin >> N >> C;
    for(int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        pos.emplace_back(tmp);
    }
    sort(pos.begin(), pos.end());
    solution();
    return 0;
}