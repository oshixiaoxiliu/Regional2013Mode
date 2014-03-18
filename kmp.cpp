#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>=0?(x):-(x))
#define i64 long long
#define u32 unsigned int
#define u64 unsigned long long
#define clr(x,y) memset(x,y,sizeof(x))
#define PI acos(-1.0)
#define sqr(x) ((x)*(x))
#define maxn 100050
int n,m;
string s,t;
// s wei text  m
// t wei pattern n
int pre[maxn];
void getnext() {
    pre[0] = -1;
    for(int j=-1,i=1; i<n; ++i) {
        while(j!=-1 && t[i]!=t[j+1]) j = pre[j];
        if(t[i]==t[j+1]) ++j;
        pre[i] = j;
    }
}
void kmp() {
    for(int j=-1,i=0; i<m; ++i) {
        while(j!=-1 && s[i]!=t[j+1]) j = pre[j];
        if(s[i]==t[j+1]) ++j;
        if(j==n-1) {
            printf("%d\n",i - n + 1 );
        }
    }
}
int main() {
    cin >> s >> t;
    n = t.length();
    m = s.length();
    getnext();
    kmp();
    return 0;
}
