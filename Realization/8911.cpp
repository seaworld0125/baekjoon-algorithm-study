#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define F first
#define S second

int T, dir; // 0 = 북쪽, 1 = 동쪽, 2 = 남쪽, 3 = 서쪽
// y, x
pair<int, int> move_[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 1 -> max  2 -> min
int turtle_x, turtle_y, x1, x2, y1, y2;

void refresh() {
    x1 = max(x1, turtle_x);
    y1 = max(y1, turtle_y);
    x2 = min(x2, turtle_x);
    y2 = min(y2, turtle_y);
}

int main() {
    cin >> T;
    for(int i = 0; i < T; i++) {
        string input;
        cin >> input;

        dir = 0, turtle_x = 0, turtle_y = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;

        int size = input.length();
        for(int j = 0; j < size; j++) {
            char order = input[j];

            if(order == 'F') {
                turtle_y += move_[dir].F;
                turtle_x += move_[dir].S;
                refresh();
            }
            else if(order == 'B') {
                turtle_y -= move_[dir].F;
                turtle_x -= move_[dir].S;
                refresh();
            }
            else if(order == 'L') {
                dir = (dir + 3) % 4;
            }
            else {
                dir = (dir + 1) % 4;
            }
        }
        cout << (x1 - x2) * (y1 - y2) << endl;
    }
}