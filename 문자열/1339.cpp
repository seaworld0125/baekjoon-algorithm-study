#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

int N;
vector<string> v;
vector<vector<pair<char, int>>> vc(8);
map<char, int> m = {};
int charCount[26] = {0};

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for(int j = str.length() - 1, k = 0; j >= 0; j--, k++) {
            bool flag = true;
            for(int l = 0; l < vc[k].size(); l++) {
                if(vc[k][l].first == str[j]) {
                    vc[k][l].second++;
                    if(vc[k][l].second == 10) {
                        vc[k][l].second = 0;
                        vc[k+1].emplace_back(vc[k][l].first, 1);
                    }
                    flag = false;
                    break;
                }
            }
            if(flag)
                vc[k].emplace_back(str[j], 1);

            charCount[str[j] - 'A']++;
        }
    }
    for(int i = 0; i < 8; i++)
        sort(vc[i].begin(), vc[i].end(), [](pair<char, int> a, pair<char, int> b) {
            if(a.second > b.second) return true;
            else if(a.second == b.second) return charCount[a.first - 'A'] > charCount[b.first - 'A'];
            else return false;
        });

    for(int i = 7; i >= 0; i--) {
        for(int j = 0; j < vc[i].size(); j++) {
            cout << "(" << vc[i][j].first << ", " << vc[i][j].second << ") -";
        }cout << endl;
    }

    int ans = 0;
    int num = 9;
    for(int i = 7; i >= 0; i--) {
        for(int j = 0; j < vc[i].size(); j++) {
            if(!m.count(vc[i][j].first)) { // 키가 없으면
                m[vc[i][j].first] = num;
                num--;
            }
            cout << "+ " << m[vc[i][j].first] * pow(10, i) * vc[i][j].second << endl;
            ans += m[vc[i][j].first] * pow(10, i) * vc[i][j].second;
        }
    }
    cout << ans;
}