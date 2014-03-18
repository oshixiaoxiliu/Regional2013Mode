
void tarjan(int u ) {
    int v ;
    dfn[u] = low[u] = dep ++ ;
    vis[u] = 1;
    for (int i = head[u] ; i != -1 ; i = e[i].next)
        if(!vst[i>>1]) {
            // printf("i>>1 = %d\n",i>>1);
            vst[i >> 1] = 1;
            v = e[i].v;
            //  printf("v = %d\n",v);
            if(dfn[v] == -1 ) {
                tarjan(v);
                low[u] = min(low[u],low[v]);
                if(dfn[u] < low[v] ) {
                    ans = min(ans , e[i].w);
                }
            } else if(vis[v] == 1) low[u] = min(low[u] , dfn[v]);
        }
    vis[u] = 2 ;
}
