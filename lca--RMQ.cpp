void dfs(int u ,int fa,int dep) {
    E[++num] = u , L[num] = dep , R[u] = num;
    for(int i = head[u] ; i != -1; i = e[i].next)
        if(e[i].v != fa) {
            int v = e[i].v;
            dfs(v, u, dep + 1 );
            E[++num] = u , L[num] = dep;
        }
    return;
}
void initRMQ() {
    for(int i = 1 ; i <= num ; i ++ ) f[i][0] = i;
    for(int j = 1 ; (1<<j) <= num ; j++ )
        for(int i = 1; i + (1<<j) -1 <= num; i ++ )
            if(L[f[i][j-1]] < L[f[i+(1<<(j-1))][j-1]])      //ps:×¢ÒâÏÂ±ê
                f[i][j] = f[i][j-1];
            else f[i][j] = f[i+(1<<(j-1))][j-1];
}
int lca(int a ,int b) {
    a = R[a] , b = R[b];
    if(a>b) swap(a,b);
    int k = (log(1.0 + b - a )/log(2.0));
    if(L[f[a][k]] < L[f[b-(1<<k)+1][k]] )
        return E[f[a][k]];
    else return E[f[b-(1<<k)+1][k]];
}
