#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX_NUM_LEN 10001

void makeBadNumTable(vector<int> & target, int length, int * table) {
    int i;

    for(i = 0; i < MAX_NUM_LEN; i++)
        table[i] = -1;
    for(i = 0; i < length; i++)
        table[target[i]] = i;
}

bool search(vector<int> & target, vector<int> & base, int * table) {
    int len_base = base.size();
    int len_target = target.size();

    int s = 0, j;
    while(s + len_target <= len_base) {
        j = len_target - 1;

        while(j >= 0 && (target[j] == base[j + s]))
            j--;

        if(j >= 0) {
            s += max(1, j - table[base[s + j]]);
        }
        else {
            // s += (s + len_target < len_base) ? len_target - table[base[s + len_target]] : 1;
            return true;
        }
    }
    return false;
}

int main() {
    int N, K, M, temp;
    cin >> N >> K;

    vector<vector<int>> programs(N);

    for(int i = 0; i < N; i++) {
        cin >> M;

        for(int j = 0; j < M; j++) {
            cin >> temp;
            programs[i].emplace_back(temp);
        }
    }

    // programs[0] . target 생성
    // programs[1~]  base

    int length = programs[0].size() - K + 1, s = 0;

    while(s < length) {
        vector<int> target(K);
        vector<int> rev_target(K);

        for(int i = 0; i < K; i++) {
            target[i] = programs[0][i + s]; // target
            rev_target[K - i - 1] = programs[0][i + s]; // reverse target
        }

        int table[MAX_NUM_LEN]; // BadNumTable
        makeBadNumTable(target, K, table);
        int rev_table[MAX_NUM_LEN]; // reverse_BadNumTable
        makeBadNumTable(rev_target, K, rev_table);

        int count = 1;
        for(int i = 1; i < N; i++) {
            if(search(target, programs[i], table) || search(rev_target, programs[i], rev_table))
                count++;
        }

        if(count == N) {
            cout << "YES";
            return 0;
        }

        s++;
    }   
    cout << "NO";
}