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

#define abs(x) ((x)>=0?(x):-(x))
#define i64 long long
#define u32 unsigned int
#define u64 unsigned long long
#define clr(x,y) memset(x,y,sizeof(x))
#define PI acos(-1.0)
#define sqr(x) ((x)*(x))
#define maxn 20005

struct suffix_automaton {
    int f[maxn << 1 ] , ant , last ;
    int pos[maxn<<1];
    int ch[maxn << 1][26],step[maxn<<1];
    void init() {
        last = ant =1 ;
        memset(f,0,sizeof(f));
        memset(ch,0,sizeof(ch));
        memset(step,0,sizeof(step));
    }
    void add(int x ) {
        int t = ++ ant ,pa =last;
        step[t] = step[last] + 1 ;
        pos[t] = step[t];
        last = t;
        for(; pa && !ch[pa][x]; pa = f[pa])
            ch[pa][x] = t;
        if(pa == 0 ) f[t] = 1;
        else if(step[pa] + 1 == step[ch[pa][x]])
            f[t] = ch[pa][x];
        else {
            int nq = ++ ant,q = ch[pa][x];
            memcpy(ch[nq],ch[q],sizeof(ch[nq]));
            step[nq] = step[pa] + 1 ;
            f[nq] = f[q];
            f[q] = f[t] = nq;
            pos[q] = pos[t];
            for(; pa && ch[pa][x] == q; pa = f[pa])
                ch[pa][x] = nq;
        }
    }
};
suffix_automaton SAM;


char str[maxn];
int main()
{
    int cas;
    scanf("%d\n",&cas);
    while(cas -- ) {
        scanf("%s",str);
        int n ;
        n = strlen(str);
        SAM.init();
        for(int i = 0 ; i < n ; i ++  )
            SAM.add(str[i]-'a');
        for(int i = 0 ; i < n ; i ++  )
            SAM.add(str[i]-'a');
        int root ;
        root = 1 ;
        for(int i = 0 ; i < n ; i ++ ) {
            for(int j = 0 ; j < 26 ; j ++ )
                if(SAM.ch[root][j] != 0) {
                    root = SAM.ch[root][j];
                    break ;
                }
        }
        printf("%d\n",SAM.pos[root] - n + 1);
    }
    return 0;
}
