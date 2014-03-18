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

#define maxn 100105

struct node {
    int l,r;
    int cnt;
    void init(int ll,int rr,int cc) {
        l = ll;
        r = rr;
        cnt = cc;
    }
};
node tt[maxn * 30];

int t[maxn ];
int a[maxn];
int v[maxn];
int n,q;
int m;
int tot;

void build(int &root ,int l ,int r ) {
    root = tot ++ ;
    tt[root].init(0,0,0);
    if(l == r ) return ;
    int mid = (l + r ) / 2 ;
    build(tt[root].l,l,mid);
    build(tt[root].r,mid + 1 , r);
}
void ins(int &root ,int p ,int l ,int r , int x) {
    root = tot ++ ;
    tt[root].init(tt[p].l,tt[p].r,tt[p].cnt + 1 );
    if(l == r ) return ;
    int mid = (l + r ) / 2 ;
    if(mid >= x ) ins(tt[root].l,tt[p].l, l , mid , x);
    else ins(tt[root].r,tt[p].r, mid + 1 , r , x );
}
int query(int lroot,int rroot,int l, int r ,int k) {
    if(l == r ) return l ;
    int mid = (l + r ) / 2 ;
    int lcnt = tt[tt[rroot].l].cnt - tt[tt[lroot].l].cnt;
    if(lcnt >= k )
        query(tt[lroot].l,tt[rroot].l , l , mid , k );
    else
        query(tt[lroot].r,tt[rroot].r , mid + 1 , r , k - lcnt );
}
int main() {
    int cas;
    scanf("%d",&cas);
    while(cas -- ) {
        scanf("%d%d",&n,&q);
        for(int i = 1 ; i <= n ; i ++ ) scanf("%d",&a[i]),v[i-1] = a[i];
        sort(v ,v + n );
        m = unique(v , v + n ) - v ;
        //printf("m = %d\n",m);
        memset(t,0,sizeof(t));
        tot = 0 ;
        build(t[0],1,m);
        int pos;
        for(int i = 1 ; i <= n ; i ++) {
            pos = lower_bound(v ,v + m ,a[i]) - v + 1 ;
            //printf("pos = %d\n",pos);
            ins(t[i],t[i-1],1,m,pos);
        }
        int x,y,k;
        for(int i = 1 ; i <= q ; i ++ ) {
            scanf("%d%d%d",&x,&y,&k);
            pos = query(t[x-1],t[y],1,m,k);
            printf("%d\n",v[pos-1]);
        }
    }
    return 0;
}

