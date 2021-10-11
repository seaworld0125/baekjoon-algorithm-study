#include <iostream>
#include <bitset>
using namespace std;

int main() {
    bitset<(1 << 25)> set;
    int input;
    while(scanf("%d", &input) != EOF) {
        if(!set[input]) {
            set.set(input);
            printf("%d ", input);
        }
    }
}