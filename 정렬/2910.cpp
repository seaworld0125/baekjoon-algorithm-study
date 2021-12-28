#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Info {
    int num;
    int pos;
    int count;

    Info(int n, int p, int c) : num(n), pos(p), count(c) {}; // emplace_back 을 사용할 경우 생성자 필요
};

int main() {
    int N, C, tmp;
    cin >> N >> C;

    vector<Info> v;
    for(int i = 0; i < N; i++) {
        cin >> tmp;

        bool insert = false;
        for(int j = 0; j < v.size(); j++) {
            if(v[j].num == tmp) {
                v[j].count++;
                insert = true;
            }
        }
        if(!insert)
            v.emplace_back(tmp, i, 1);
    }

    sort(v.begin(), v.end(), [](Info x, Info y){
        if(x.count > y.count) return true;
        if(x.count == y.count) return x.pos < y.pos;
        if(x.count < y.count) return false;
    });

    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < v[i].count; j++)
            cout << v[i].num << ' ';
}