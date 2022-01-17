#include<iostream>
#include <vector>
#include <bitset>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

    bitset<10> bs;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        bs.set();

		int N, tmp, i = 0;
        cin >> N;
        
        while(bs.any()) {
            i++;
            tmp = N * i;
            while(tmp) {
                bs[tmp % 10] = 0;
                tmp /= 10;
            }
        }
        cout << "#" << test_case << ' ' << N * i << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}