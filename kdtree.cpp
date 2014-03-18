
typedef long long ll;
const long long INF=1LL<<61;
const int MaxN=100010;
struct POINT {
    ll x,y;
    ll dis(const POINT &tp) {
        return (x-tp.x)*(x-tp.x)+(y-tp.y)*(y-tp.y);
    }
} tree[MaxN],p[MaxN],q[MaxN];
bool flag[MaxN];
bool cmpx(const POINT &p1,const POINT &p2)
{
    return p1.x<p2.x;
}
bool cmpy(const POINT &p1,const POINT &p2)
{
    return p1.y<p2.y;
}
ll ans;
void built(int L,int R)
{
    if(L>R)return;
    int M=(L+R)>>1;
    ll miX=INF,maX=-INF,miY=INF,maY=-INF;
    for(int i=L; i<=R; i++) {
        miX=min(miX,p[i].x);
        maX=max(maX,p[i].x);
        miY=min(miY,p[i].y);
        maY=max(maY,p[i].y);
    }
    flag[M]=(maX-miX)>=(maY-miY);
    nth_element(p+L,p+M,p+R+1,flag[M]? cmpx:cmpy);
    tree[M]=p[M];
    built(L,M-1);
    built(M+1,R);
}
void fint(int L,int R,POINT v)
{
    if(L>R)return;
    int M=(L+R)>>1;
    ll tmp=tree[M].dis(v);
    if(tmp!=0) ans=min(ans,tmp);
    if(flag[M]) {
        ll d=(v.x-tree[M].x)*(v.x-tree[M].x);
        if(v.x<=tree[M].x) {
            fint(L,M-1,v);
            if(d<ans) fint(M+1,R,v);
        } else {
            fint(M+1,R,v);
            if(d<ans) fint(L,M-1,v);
        }
    } else {
        ll d=(v.y-tree[M].y)*(v.y-tree[M].y);
        if(v.y<=tree[M].y) {
            fint(L,M-1,v);
            if(d<ans) fint(M+1,R,v);
        } else {
            fint(M+1,R,v);
            if(d<ans) fint(L,M-1,v);
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) {
        int n;
        scanf("%d",&n);
        for(int i=0; i<n; i++) {
            scanf("%lld%lld",&p[i].x,&p[i].y);
            q[i]=p[i];
        }
        built(0,n-1);
        for(int i=0; i<n; i++) {
            ans=INF;
            fint(0,n-1,q[i]);
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
