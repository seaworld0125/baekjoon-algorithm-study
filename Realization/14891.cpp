#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
#define LAST 7
#define endl '\n'

int K;
string gear[4];

bool rightCmp(int index, int prev){
    if(gear[index][2] != gear[index+1][6] && index+1 != prev) return true;
    return false;
}
bool leftCmp(int index, int prev){
    if(gear[index][6] != gear[index-1][2] && index-1 != prev) return true;
    return false;
}

void counterClockwise(int index, int prev);

// 시계방향
void clockwise(int index, int prev){
    if(index == 1 || index == 2)
    {
        if(leftCmp(index, prev)) counterClockwise(index-1, index);   
        if(rightCmp(index, prev)) counterClockwise(index+1, index);   
    }
    else if(index == 0)
    {
        if(rightCmp(index, prev)) counterClockwise(index+1, index); 
    }
    else if(index == 3)
    {
        if(leftCmp(index, prev)) counterClockwise(index-1, index);  
    }
    
    // 회전
    gear[index] = gear[index][LAST] + gear[index].substr(0, LAST);
}
// 반시계방향
void counterClockwise(int index, int prev){
    if(index == 1 || index == 2)
    {
        if(leftCmp(index, prev)) clockwise(index-1, index);   
        if(rightCmp(index, prev)) clockwise(index+1, index);   
    }
    else if(index == 0)
    {
        if(rightCmp(index, prev)) clockwise(index+1, index); 
    }
    else if(index == 3)
    {
        if(leftCmp(index, prev)) clockwise(index-1, index);  
    }

    // 회전
    gear[index] = gear[index].substr(1) + gear[index][0];
}

void solution(){
    for(int i = 0; i < 4; i++)
        cin >> gear[i];

    cin >> K;

    int gearNum, dir;
    for(int i = 0; i < K; i++)
    {
        cin >> gearNum >> dir;
        gearNum -= 1;
        if(dir == 1) clockwise(gearNum, -1);
        else counterClockwise(gearNum, -1);
    }
    
    int score = 0;
    for(int i = 0; i < 4; i++)
    {
        // S극이면
        if(gear[i][0] == '1')
            score += (int)pow(2, i);
    }
    cout << score;
}

int main(){
    solution();
}