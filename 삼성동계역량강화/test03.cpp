#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int limit);
extern void play();

static int board[10][10];

#define MISS		0
#define CARRIER		1
#define BATTLESHIP	2
#define CRUISER		3
#define SUBMARINE	4
#define DESTROYER	5

static int hit;
static const int len[5] = { 5, 4, 3, 3, 2 };

#define MAX_CALLCOUNT	10000

static int callcount;
static int limit;

int fire(int r, int c)
{
	if (r < 0 || r > 9 || c < 0 || c > 9 || callcount >= MAX_CALLCOUNT)
	{
		callcount = MAX_CALLCOUNT;
		return 0;
	}
	
	++callcount;
	
	int ret = board[r][c];
	
	if (board[r][c] > 0) --hit;
	board[r][c] = 0;
	
	return ret;
}

#include <iostream>
using namespace std;

extern int fire(int r, int c);

int visited_map[10][10];
int move_first[5] = {1,3,5,7,9};
int move_second[5] = {8,6,4,2,0};

int boat_length[6] = {0,5,4,3,3,2};

int my_end = 17;
int my_limit;
int my_hit;
int move_count;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void printMyMap() {
    cout << endl;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cout << visited_map[i][j] << ' '; 
        }cout << endl;
    }
}

void init(int limit)
{
    my_limit = limit;
}
void my_init() {
    fill(visited_map[0], visited_map[0] + 100, 0);
    my_hit = 0;
}
bool checkLange(int r, int c) {
    if (r < 0 || r > 9 || c < 0 || c > 9) return false;
    return true;
}
void findBoat_v2(int r, int c, int boat);
void goStraight(int r, int c, int dir, int boat, int & idx) { // 직진
    do
    {
        r += dy[dir];
        c += dx[dir];

        if(!checkLange(r, c)) return;
        if(visited_map[r][c]) continue;
        visited_map[r][c] = true;

        int new_boat;
        if(new_boat = fire(r, c)) {
            visited_map[r][c] = (new_boat == 1 ? 7 : new_boat);
            my_hit++;

            if(my_hit == my_end) return;

            if(new_boat != boat) {
                findBoat_v2(r, c, new_boat);
                return;
            }
            else {
                idx--;
            }
        }
        else return;
    } while (idx);
}
void findBoat_v2(int r, int c, int boat) { // 좌우냐 위아래냐
    for(int i = 0; i < 4; i++) {
        int r_ = r + dy[i];
        int c_ = c + dx[i];

        if(!checkLange(r_, c_) || visited_map[r_][c_]) continue;
        visited_map[r_][c_] = true;

        int new_boat;
        if(new_boat = fire(r_, c_)) {
            visited_map[r_][c_] = (new_boat == 1 ? 7 : new_boat);
            my_hit++;
            if(my_hit == my_end) return;

            if(new_boat != boat) {
                findBoat_v2(r_, c_, new_boat);
            }
            else {
                int idx = boat_length[boat] - 2;
                if(!idx) return;

                if(i == 0 || i == 1) { // 좌우
                    goStraight(r_, c_, 0, boat, idx);
                    goStraight(r_, c_, 1, boat, idx);
                    return;
                }
                else if(i == 2 || i == 3) { // 위 아래
                    goStraight(r_, c_, 2, boat, idx);
                    goStraight(r_, c_, 3, boat, idx);
                    return;
                }
            }
        }
    }
}

void play()
{  
    my_init();
    for(int i = 0; i < 5; i++) {
        int r = move_first[i];
        for(int j = 0; j < 5; j++) {
            int c = move_first[j];

            if(visited_map[r][c]) continue;

            visited_map[r][c] = true;

            int boat;
            if(boat = fire(r, c)) {
                visited_map[r][c] = (boat == 1 ? 7 : boat);
                my_hit++;
                if(my_hit == my_end) return;
                findBoat_v2(r, c, boat);
            }
        }
    }
    for(int i = 0; i < 5; i++) {
        int r = move_second[i];
        for(int j = 0; j < 5; j++) {
            int c = move_second[j];

            if(visited_map[r][c]) continue;

            visited_map[r][c] = true;

            int boat;
            if(boat = fire(r, c)) {
                visited_map[r][c] = (boat == 1 ? 7 : boat);
                my_hit++;
                if(my_hit == my_end) return;
                findBoat_v2(r, c, boat);
            }
        }
    }
}

static int seed;

static int pseudo_rand()
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7fff;
}

static bool check(int r, int c, int d, int l)
{	
	if (d == 1)
	{
		for (int m = 0; m < l; ++m)
			if (board[r][c + m] > 0)
				return false;
		return true;
	}
	else
	{
		for (int m = 0; m < l; ++m)
			if (board[r + m][c] > 0)
				return false;
		return true;
	}
}

static void doarrangment()
{
	for (int r = 0; r < 10; ++r)
	for (int c = 0; c < 10; ++c)
		board[r][c] = 0;
	
	for (int k = 0; k < 5; ++k)
	{
		while(1)
		{
			int r, c, d;
			
			d = pseudo_rand() % 2;
			if (d == 1)
			{
				r = pseudo_rand() % 10;
				c = pseudo_rand() % (10 - len[k] + 1);
				if (check(r, c, d, len[k]))
				{
					for (int l = 0; l < len[k]; ++l)
						board[r][c + l] = k + 1;
					break;
				}
			}
			else
			{
				r = pseudo_rand() % (10 - len[k] + 1);
				c = pseudo_rand() % 10;
				if (check(r, c, d, len[k]))
				{
					for (int l = 0; l < len[k]; ++l)
						board[r + l][c] = k + 1;
					break;
				}
			}
		}
	}
}

int main()
{
	int TC;
	
    freopen("sample_input_2.txt", "r", stdin);

	setbuf(stdout, NULL);
    scanf("%d", &TC);

	int totalscore = 0, totalcallcount = 0;
    for (int testcase = 1; testcase <= TC; ++testcase)
	{
		int score = 100, callcount4tc = 0;
		
		scanf("%d %d", &seed, &limit);
		
		init(limit);

		for (int game = 0; game < 10; ++game)
		{
			doarrangment();
		
			hit = 0;
			for (int k = 0; k < 5; ++k)
				hit += len[k];
    
			callcount = 0;
			play();
            cout << "----- remain hit : " << hit << endl;
			if (hit != 0)
				callcount = MAX_CALLCOUNT;
			cout << "----- your call : " << callcount << endl;
            if(callcount == MAX_CALLCOUNT || callcount > 70) {
                printMyMap(); 
                cout << endl;
                for(int i = 0; i < 10; i++) {
                    for(int j = 0; j < 10; j++) {
                        cout << board[i][j] << ' ';
                    }cout << endl;
                }cout << endl;
            }
			if (callcount > limit)
				score = 0;

			callcount4tc += callcount;
		}
		
		printf("#%d %d %d\n", testcase, score, callcount4tc);

		totalscore += score;
		totalcallcount += callcount4tc;
    }

	printf("total score = %d, total callcount = %d\n", totalscore / TC, totalcallcount);
    return 0;
}