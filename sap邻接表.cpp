
#define inf 0x3f3f3f3f
#define maxn 3000

struct node {
    int v,next,cap;
};
node e[maxn * 300 * 2];
int head[maxn];
int cnt ;
int s,t,nn;
int n ;
void init() {
    cnt = 0 ;
    memset(head,-1,sizeof(head));
}
void add(int u,int v,int w) {
    e[cnt].v=v;
    e[cnt].cap=w;
    e[cnt].next=head[u];
    head[u]=cnt++;
    e[cnt].v=u;
    e[cnt].cap=0;
    e[cnt].next=head[v];
    head[v]=cnt++;
}
int pre[maxn],cur[maxn],dis[maxn],gap[maxn];
int sap() {
    int flow,aug,u;
    int flag;
    flow=0;
    aug=inf;
    for(int i=0; i<nn; i++) {
        cur[i]=head[i];
        gap[i]=0;
        dis[i]=0;
    }
    gap[s]=nn;
    u=s;
    pre[s]=s;
    while(dis[s]<nn) {
        flag=0;
        for(int &j=cur[u]; j!=-1; j=e[j].next) {
            //cur[u]=j;
            int v=e[j].v;
            if(e[j].cap>0&&dis[u]==dis[v]+1) {
                flag=1;
                if(e[j].cap<aug)aug=e[j].cap;
                pre[v]=u;
                u=v;
                if (u==t) {
                    flow+=aug;
                    while(u!=s) {
                        u=pre[u];
                        e[cur[u]].cap-=aug;
                        e[cur[u]^1].cap+=aug;
                        //why?解释偶数异或1为偶数+1，奇数异或1为奇数-1，
                        //显然我们存的边是从0开始存的，
                        //所以偶数,偶数+1是残量网格中的两条边(无向边)
                    }
                    aug=inf;
                }
                break;
            }
        }
        if (flag) continue;
        int mindis=nn;
        for(int j=head[u]; j!=-1; j=e[j].next) {
            int v=e[j].v;
            if (e[j].cap>0&&dis[v]<mindis) {
                mindis=dis[v];
                cur[u]=j;
            }
        }
        if (--gap[dis[u]]==0) { //间隙优化
            break;
        }
        dis[u]=mindis+1;
        gap[dis[u]]++;
        u=pre[u];
    }
    return flow;
}



