#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int map[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    cout << *(map[0]) << endl;
    cout << *(map[2]) << endl;

    for(int i = 0; i < 3; i++)
        fill(map[i], map[i] + 3, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            cout << map[i][j] << ' ';
}