
#define maxn 1005

struct node {
    int v,next;
};
node e[maxn * maxn];
int cnt ;
int head[maxn] , dfn[maxn] , low[maxn] , col[maxn];
bool instack[maxn];
int ind[maxn] , oud[maxn] , st[maxn] ;
int n , m , top, dep , scnt , dep ;
void init() {
    memset(head,-1,sizeof(head));
    cnt = 0 ;
}
void add(int u,int v) {
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt ++;
}
void tarjan(int u) {
    int v;
    dfn[u]=low[u]=dep++;
    st[++top]=u;
    instack[u]=1;
    for(int i=head[u]; i!=-1; i=e[i].next) {
        v=e[i].v;
        if (dfn[v]==-1) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if(instack[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]) {
        int x ;
        do {
            x=st[top--];
            instack[x]=0;
            col[x]=scnt;
        } while (x!=u);
        scnt++;
    }
}
void base() {
    scnt = 0;
    top = 0;
    dep = 0 ;
    memset(dfn,-1,sizeof(dfn));
    memset(instack,0,sizeof(instack));
    for(int i = 1; i <= n ; i ++)
        if (dfn[i] == -1) {
            tarjan(i);
        }
}
/*
初始化init();
加边add，cnt为边数，从0开始
调用base缩点，求的col为每个点所在的强连通编号
scnt为强连通数目，从0开始，
*/