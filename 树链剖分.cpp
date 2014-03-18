
int w[maxn],son[maxn],sz[maxn],top[maxn],fa[maxn],dep[maxn];
int d1[maxn][3];
int z;
int n ;
char str[15];
struct node {
    int v ,next;
};

node e[maxn * 2 ];
int cnt ;
int head[maxn];
int tt[maxn * 3 ];

inline void add(int u ,int v) {
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++ ;
    return ;
}
void push_up(int root ) {
    tt[root] = max(tt[root*2],tt[root*2+1]);
}
inline void dfs1(int u ) { // º∆À„ sz[],son[],dep[],fa[];
    sz[u] = 1 ;
    son[u] = 0;
    for(int i = head[u] ; i != -1 ; i = e[i].next)
        if(e[i].v != fa[u]) {
            fa[e[i].v] = u;
            dep[e[i].v] = dep[u] + 1;
            dfs1(e[i].v);
            if(sz[e[i].v] > sz[son[u]] )  son[u] = e[i].v;
            sz[u] += sz[e[i].v];
        }
}

void dfs2(int u,int tp) { // º∆À„ w[],top[]
    w[u] = ++ z ;
    top[u] = tp;
    if(son[u] != 0 ) dfs2(son[u] , top[u]);
    for(int i = head[u] ; i!= -1 ; i = e[i].next)
        if(e[i].v != fa[u] && e[i].v != son[u] )
            dfs2(e[i].v,e[i].v);
    return ;
}
void update(int root,int l,int r,int pos,int val) {
    if(l == r ) {
        tt[root] = val;
        return ;
    }
    int mid = (l + r ) / 2;
    if(pos <= mid)
        update(root + root ,l,mid, pos , val);
    else
        update(root + root  + 1 ,mid +1 , r , pos ,val);
    push_up(root);
    return ;
}
int query(int root,int l1,int r1,int l,int r) {
    if(l <= l1 && r1 <= r)
        return tt[root];
    int mid = (l1 + r1 ) / 2 ;
    int res = 0 ;
    if(l <= mid )
        res = max(res , query(root + root,l1 , mid , l , r ));
    if(r > mid )
        res = max(res , query(root + root + 1 ,mid + 1 , r1 , l , r ));
    return res;
}
int find(int a,int b) {
    int f1 = top[a] , f2 = top[b] , tmp = 0 ;
    while( f1 != f2 ) {
        if(dep[f1] < dep[f2])
            swap(f1,f2),swap(a,b);
        tmp = max(tmp , query(1,1,z,w[f1],w[a]) );
        a = fa[f1],f1 = top[a];
    }
    if(a == b) return tmp ;
    if(dep[a] > dep[b]) swap(a,b);
    return max(tmp , query(1,1,z,w[son[a]],w[b]) ); // ∏∏±ﬂ
}
