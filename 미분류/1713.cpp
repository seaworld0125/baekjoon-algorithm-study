#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Student{
public:
    int num;
    int voted;
    int age;
    Student(int n, int v, int a) : num(n), voted(v), age(a) {}
};

int N, M, num, time = 0;
vector<Student> frame;

bool searchFrame(int num) {
    for(Student & s : frame) {
        if(s.num == num) {
            s.voted++;
            return true;
        }
    }
    return false;
}
int searchOldFrame() {
    int index = 0;
    int voted = frame[0].voted;
    int age = frame[0].age;

    for(int i = 1; i < frame.size(); i++) {
        if(voted > frame[i].voted) index = i, voted = frame[i].voted, age = frame[i].age;
        else if(voted == frame[i].voted && age > frame[i].age) index = i, voted = frame[i].voted, age = frame[i].age;
    }
    return index;
}

int main() {
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        cin >> num;
        // 먼저 있는지 찾고
        if(!searchFrame(num)) {
            // 없으면 액자 개수 확인
            // 액자 꽉참
            if(N == frame.size()) {
                //뺄놈 찾기
                int index = searchOldFrame();
                frame[index].num = num;
                frame[index].voted = 1;
                frame[index].age = time;
            }
            else frame.emplace_back(num, 1, time);
        }
        time++;
    }
    sort(frame.begin(), frame.end(), [](Student & a, Student & b){
        return a.num < b.num;
    });
    for(Student & s : frame) cout << s.num << ' ';
}