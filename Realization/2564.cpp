#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// 일직선상에 두고 거리를 구하자.
int length, width;
int total_length;
int store_count; 
int user_pos;

vector<int> v;

int getIdx(int direct, int pos) {
    if(direct == 1)
        return pos;

    else if(direct == 2)
        return (length * 2) + width - pos;

    else if(direct == 3)
        return total_length - pos;

    else
        return length + pos;
}
int getShortCut(int store_pos) {
    int len01 = abs(user_pos - store_pos);
    int len02 = (user_pos > store_pos ? (total_length - user_pos) + store_pos : (total_length - store_pos) + user_pos);

    return (len01 < len02 ? len01 : len02);
}

int main() {
    cin >> length >> width;
    total_length = (length + width) * 2;

    cin >> store_count;

    int direct, pos;
    for(int i = 0; i < store_count; i++) {
        cin >> direct >> pos;
        v.emplace_back(getIdx(direct, pos));
    }

    cin >> direct >> pos;
    user_pos = getIdx(direct, pos);

    int ans = 0;
    for(int i = 0; i < store_count; i++)
        ans += getShortCut(v[i]);

    cout << ans;
}   
