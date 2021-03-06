#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
#define endl '\n'
using namespace std;

int N;
int time_count = 0;
int sY, sX; //shark Y, X
int sS = 2; //shark size
int fat = 0;//먹은 물고기 수

int dy[4] = {1, 0, 0, -1};//위ㅡ왼ㅡ오ㅡ아
int dx[4] = {0, -1, 1, 0};  

int MAP[20][20];

// 가까운 물고기들의 수와 거리 반환
pair<int, int> BFS(vector<pair<int, int>> & fish_pos)
{
    bool visited[20][20];
    memset(visited, false, sizeof(visited));

    queue<pair<int , int>> dst;//y, x
    dst.push({sY, sX});

    int y_, x_;
    int length = -1;
    int fish_count = 0;

    bool exit = false;
    while(!exit && !dst.empty())
    {   
        length++;
        int size = dst.size();
        for(int i = 0; i < size; i++)
        {
            //큐 참조
            if(!dst.empty())
            {
                y_ = dst.front().first;
                x_ = dst.front().second;
                dst.pop();
            }
            visited[y_][x_] = true;

            //주변 확인
            for(int j = 0; j < 4; j++)
            {
                int ay = y_+dy[j];
                int ax = x_+dx[j];

                //N 범위 안에 들어오고 방문한 적이 없다면
                if(ay < N && ay >= 0 && ax < N && ax >= 0 && !visited[ay][ax])
                {
                    visited[ay][ax] = true;
                    // 만약 나보다 작은 물고기가 있다면
                    if(MAP[ay][ax] < sS && MAP[ay][ax])
                    {
                        //물고기 위치 저장
                        fish_pos.push_back({ay, ax});
                        fish_count++;
                        //탈출
                        if(!exit){
                            length++;
                            exit = true;
                        }
                    }// 만약 나랑 크기가 같은 물고기가 있거나 물고기가 없다면
                    else if(!MAP[ay][ax] || MAP[ay][ax] == sS)  
                    {   
                        dst.push({ay, ax});
                    }
                }
            }
        }
    }
    return {fish_count, length}; 
}
// 가까운 물고기 중에 상어가 먹을 물고기 고르기
int searchD(vector<pair<int, int>> & fish_pos)
{
    int y = fish_pos[0].first;
    int x = fish_pos[0].second;
    int target = 0;

    for(int i = 1; i < fish_pos.size(); i++)
    {   
        int fish_y = fish_pos[i].first;
        int fish_x = fish_pos[i].second;
        // 가장 위쪽에 있는 물고기 찾기
        if(y > fish_y)
        {
            y = fish_y;
            x = fish_x;
            target = i;
        }// 같은 높이, 더 왼쪽에 있는 경우
        else if(y == fish_y && x > fish_x)
        {
            y = fish_y;
            x = fish_x;
            target = i;            
        }
    }
    return target;
}
// 아기 상어를 이동시키는 함수
void move(int y, int x, int length)
{
    // 시간 증가
    time_count += length;
    MAP[sY][sX] = 0;
    sX = x;
    sY = y;

    fat++;
    // 상어 사이즈 증가
    if(fat == sS)
    {
        fat = 0;
        sS += 1;
    } 
    // 위치 동기화
    MAP[sY][sX] = 9;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            //상어 초기 위치 저장
            if(MAP[i][j] == 9)
            {
                sY = i;
                sX = j;
            }
        }
    }
    while(1){
        // 물고기 좌표 저장
        vector<pair<int, int>> fish_pos;
        pair<int, int> data = BFS(fish_pos);

        int fish_count = data.first;
        int length = data.second;

        // 없을 때
        if(!fish_count) break;
        else if(fish_count == 1)// 한 마리일 때
        {
            move(fish_pos[0].first, fish_pos[0].second, length);
        }
        else if(fish_count >= 2)// 두 마리 이상일 때
        {
            int index =  searchD(fish_pos);
            move(fish_pos[index].first, fish_pos[index].second, length);
        }
    }
    if(time_count == -1) cout << 0;
    else cout << time_count;

    return 0;
}