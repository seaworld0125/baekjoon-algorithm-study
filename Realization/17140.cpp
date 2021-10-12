#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[101][101];
int colLength = 3, rowLength = 3, time = 0, r, c, k;

void print(int col = colLength, int row = rowLength) {
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            if(arr[i][j] != 0)
                cout << arr[i][j] << " ";
            else cout << " " << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void R() {
    int maxRowLength = rowLength, idx = 0;
    for(int i = 1; i <= colLength; i++) {
        // print(colLength, maxRowLength);
        int check[101] = {0};
        for(int j = 1; j <= rowLength; j++) { // 한 행에 대한 연산
            if(arr[i][j] <= 0) break;
            check[arr[i][j]] += 1;
            idx = idx > arr[i][j] ? idx : arr[i][j];
        }

        vector<pair<int, int>> newArr;
        for(int j = 1; j <= idx; j++) {
            if(check[j] <= 0) continue;
            newArr.emplace_back(j, check[j]);
        }

        int length = newArr.size() * 2;
        maxRowLength = maxRowLength > length ? maxRowLength : length;
        if(maxRowLength > 100) maxRowLength = 100;

        sort(newArr.begin(), newArr.end(), [](auto a, auto b) {
            if(a.second < b.second) return true;
            else if(a.second == b.second) return a.first < b.first;
            else return false;
        });

        for(int j = 1, k = 0; j <= length && k < newArr.size(); k++) {
            arr[i][j] = newArr[k].first; j++;
            if(j >= 100) break;
            arr[i][j] = newArr[k].second; j++;
        }
        for(int j = length+1; j <= 100; j++) arr[i][j] = 0;
    }
    rowLength = rowLength > maxRowLength ? rowLength : maxRowLength;
}
void C() {
    int maxColLength = colLength, idx = 0;
    for(int i = 1; i <= rowLength; i++) {
        // print(maxColLength, rowLength);
        int check[101] = {0};
        for(int j = 1; j <= colLength; j++) { // 한 열에 대한 연산
            if(arr[j][i] <= 0) break;
            check[arr[j][i]] += 1;
            idx = idx > arr[j][i] ? idx : arr[j][i];
        }

        vector<pair<int, int>> newArr;
        for(int j = 1; j <= idx; j++) {
            if(check[j] <= 0) continue;
            newArr.emplace_back(j, check[j]);
        }

        int length = newArr.size() * 2;
        maxColLength = maxColLength > length ? maxColLength : length;
        if(maxColLength > 100) maxColLength = 100;

        sort(newArr.begin(), newArr.end(), [](auto a, auto b) {
            if(a.second < b.second) return true;
            else if(a.second == b.second) return a.first < b.first;
            else return false;
        });

        for(int j = 1, k = 0; j <= length && k < newArr.size(); k++) {
            arr[j][i] = newArr[k].first; j++;
            if(j >= 100) break;
            arr[j][i] = newArr[k].second; j++;
        }
        for(int j = length+1; j <= 100; j++) arr[i][j] = 0;
    }
    colLength = colLength > maxColLength ? colLength : maxColLength;
}

int main() {
    fill_n(arr[0], 10201, 0);
    cin >> r >> c >> k;
    
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            cin >> arr[i][j];
    
    while(arr[r][c] != k && time <= 100) {
        cout << "\ncolL :" << colLength << ", rowL :" << rowLength << endl;
        if(colLength >= rowLength) R();
        else C();
        time++;
    }

    if(time > 100) time = -1;
    cout << time;
}