#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define endl '\n'
using namespace std;

string arr[11] = {"zero", "one", "two", "three", "hour", "five", "six", "seven", "eight", "nine"};
int M, N;
string str;

vector<pair<string, int>> v;

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M >> N;

    for(int i = M; i <= N; i++)
    {
        if(i >= 10)
            str = arr[i/10] + " " + arr[i%10];
        else
            str = arr[i%10];

        v.push_back(make_pair(str, i)); 
    }

    sort(v.begin(), v.end());

    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i].second << ' ';

        if(i % 10 == 9) cout << endl;
    }
}