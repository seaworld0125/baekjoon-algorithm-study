#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//sort 알고리즘 사용
struct Student{
    string name;
    int kor;
    int eng;
    int math;
};
bool cmp(Student & a, Student & b){
    if (a.kor == b.kor && a.eng == b.eng && a.math == b.math) return a.name < b.name;
    else if (a.kor == b.kor && a.eng == b.eng) return a.math > b.math;
    else if (a.kor == b.kor) return a.eng < b.eng;
    return a.kor > b.kor;
}
int main(){
    int T;
    cin >> T;
    vector<Student> v(T);
    for(int i = 0; i < T; i++){
        cin >> v[i].name >> v[i].kor >> v[i].eng >> v[i].math;
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < T; i++){
        cout << v[i].name << "\n";
    }
}

