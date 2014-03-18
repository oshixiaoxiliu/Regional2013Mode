#define maxn 1005
const int inf = 0x3f3f3f3f;

int n,s,t;
int nn;
bool vis[maxn];
bool mmm;
int pre[maxn];
struct node {
    int v,next,cap,cost;
} e[maxn * maxn];
int head[maxn],cnt;

void add(int u,int v,int cap , int cost) {
    e[cnt].v=v;
    e[cnt].cap=cap;
    e[cnt].cost=cost;
    e[cnt].next=head[u];
    head[u]=cnt++;
    e[cnt].v=u;
    e[cnt].cap=0;
    e[cnt].cost=-cost;
    e[cnt].next=head[v];
    head[v]=cnt++;
}
void init() {
    memset(head,-1,sizeof(head));
    cnt = 0 ;
}
queue<int> q;
int dist[maxn];
bool spfa() {
    memset(dist,inf,sizeof(dist));
    memset(vis,0,sizeof(vis));
    while(!q.empty()) q.pop();
    q.push(s);
    vis[s]=1;
    dist[s]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u]; i!=-1; i=e[i].next) {
            int v=e[i].v;
            if(dist[v]>dist[u]+e[i].cost&&e[i].cap>0) {
                dist[v]=dist[u]+e[i].cost;
                pre[v]=i;
                if(!vis[v]) {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
        vis[u]=0;
    }
    if(dist[t]<0) return true;
    else return false;
}
int ans ; // 最小费用
int ans1 ; // 最大流
void mincost() {
    int i;
    i=t;
    ans1 ++ ;
    while(i!=s) {
        ans+=e[pre[i]].cost;
        e[pre[i]].cap--;
        if(e[pre[i]].cap==0) mmm=true;
        e[pre[i]^1].cap++;
        if(e[pre[i]^1].cap==1) mmm=true;
        i=e[pre[i]^1].v;
    }
}
int sum;
void work() {
    ans=0;
    ans1 = 0 ;
    mmm=true;
    while(!mmm||spfa()) {
        mmm=false;
        mincost();
    }
    printf("ans1 = %d\n",ans1);
    sum = -ans ;
}


/// 建图: 加边add，初始化 s 超级源点 t 超级汇点 节点个数
/// 让s为0 ， t为最后一个节点，nn = t + 1 ;
/// 加边初始化init();
/// ans 求出最小费用
/// ans1 为流量

int main() {

    return 0  ;
}