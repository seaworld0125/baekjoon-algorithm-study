#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int pow(int exp) {
    int num = 1;
    for(int i = 0; i < exp; i++) num *= 10;
    return num;
}

int main() {
    map<char, int> m;
    string str;
    int N;

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> str;

        int length = str.length();
        for(int j = 0; j < length; j++) {
            int num = pow(length - 1 - j);
            
            if(m.find(str[j]) == m.end())
                m[str[j]] = num;
            else
                m[str[j]] += num;
        }
    }    

    vector<pair<char, int>> v(m.begin(), m.end());
    sort(v.begin(), v.end(), [](pair<char, int> a, pair<char, int> b) {
        return a.second > b.second;
    });

    int ans = 0, num = 9;
    for(int i = 0; i < v.size(); i++, num--)
        ans += v[i].second * num;

    cout << ans;
}