#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
# define NO_OF_CHARS 256
 
void badCharHeuristic( string str, int size,
                        int badchar[NO_OF_CHARS])
{
    int i;
 
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++) 
        badchar[(int) str[i]] = i;
}
 
void search( string txt, string pat)
{
    int n = txt.size();
    int m = pat.size();
 
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);
 
    int s = 0;
    
    while(s <= (n - m))
    {
        int j = m - 1;
 
        while(j >= 0 && pat[j] == txt[s + j])
            j--;
 
        if (j < 0)
        {
            cout << "pattern occurs at shift = " <<  s << endl;
            cout << "m-badchar[txt[s + m]] = " << m-badchar[txt[s + m]] << endl;
            cout << "s += " << ((s + m < n)? m-badchar[txt[s + m]] : 1) << endl;
            s += (s + m < n)? m-badchar[txt[s + m]] : 1;
            // s += (s + m < n)? m : 1;
        }
        else 
        {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}
 
int main()
{
    string txt = "XXXBOBOB";
    string pat = "BOB";
    search(txt, pat);
    return 0;
}