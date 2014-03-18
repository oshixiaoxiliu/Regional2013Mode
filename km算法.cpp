int nx,ny;
int n,m,k,slack;
int linky[maxn],lx[maxn],ly[maxn],w[maxn][maxn];
bool visx[maxn],visy[maxn];

bool find(int x) {
    visx[x]=true;
    for(int y=1; y<=ny; y++) {
        if(visy[y]) continue;
        int t=lx[x]+ly[y]-w[x][y];
        if(t==0) {
            visy[y]=true;
            if(linky[y]==-1 || find(linky[y])) {
                linky[y]=x;
                return true;
            }
        } else if(slack > t)
            slack = t;
    }
    return false;
}

int KM() {
    int i,x,y;
    memset(linky,-1,sizeof(linky));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    for(x=1; x<=nx; x++)
        for(y=1; y<=ny; y++)
            if(w[x][y]>lx[x]) lx[x]=w[x][y];
    int old;
    for(x=1; x<=nx; x++)
        while(1 == 1) {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            slack=inf;
            if(find(x)) break;
            for(i=1; i<=nx; i++)
                if(visx[i]) lx[i] -= slack;
            for(i=1; i<=ny; i++)
                if(visy[i]) ly[i] += slack;
        }
    int ret=0;
    for(y=1; y<=ny; y++)
        if(linky[y]!=-1)
            ret += w[linky[y]][y];
    return ret;
}


/// 运用注意，把小的点集放在x上，大的点集放在y上
/// 否则会死循环&wa
