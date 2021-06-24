#include <iostream>
#include <deque>
using namespace std;

int main(){
    int N, n;
    cin >> N;
    deque<int> dq1;
    char odr[11];
    for(int i = 0; i < N; i++){
        cin >> odr;
        if(odr[1] == 'u' && odr[5] == 'f'){
            cin >> n;
            dq1.push_front(n);
        }else if(odr[1] == 'u' && odr[5] == 'b'){
            cin >> n;
            dq1.push_back(n);
        }else if(odr[1] == 'o' && odr[4] == 'f'){
            if(dq1.size() == 0) cout << -1 << endl;
            else {
                cout << dq1.front() << endl;
                dq1.pop_front();
            }
        }else if(odr[1] == 'o' && odr[4] == 'b'){
            if(dq1.size() == 0) cout << -1 << endl;
            else {
                cout << dq1.back() << endl;
                dq1.pop_back();
            }
        }else if(odr[0] == 's') cout << dq1.size() << endl;
        else if(odr[0] == 'e'){
            if(dq1.size() == 0) cout << 1 << endl;
            else cout << 0 << endl;
        }else if(odr[0] == 'f'){
            if(dq1.size() == 0) cout << -1 << endl;
            else cout << dq1.front() << endl; 
        }else{
            if(dq1.size() == 0) cout << -1 << endl;
            else cout << dq1.back() << endl; 
        }
    }return 0;
}