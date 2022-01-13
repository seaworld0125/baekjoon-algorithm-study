#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Test {
    string name;
    Test(char * n) : name(n) {}
};

int main() {
    vector<int> v = {0,1,2,3};

    vector<int> s;

    v.swap(s);

    cout << s.size();
    cout << " " << v.size();
}