
#define maxn 2000

struct node
{
  int v,next;
  bool isbri;
};
node e[maxn * 4];
int head[maxn];
int cnt , dep , n  , m ;
int low[maxn],dfn[maxn];
int vis[maxn];
bool vst[maxn * 2]; // 边有没有访问过
int col[maxn],scnt;
int num[maxn],deg[maxn];
void init()
{
  cnt = 0;
  memset(head,-1,sizeof(head));
}
void add(int u , int v )
{
  e[cnt].v = v;
  e[cnt].isbri = false;
  e[cnt].next = head[u] ;
  head[u] = cnt ++ ;
  e[cnt].v = u;
  e[cnt].isbri = false;
  e[cnt].next = head[v];
  head[v] = cnt ++ ;
}
void tarjan(int u )
{
  int v;
  dfn[u] = low[u] = dep ++ ;
  vis[u] = 1;
  for(int i = head[u] ; i != -1; i = e[i].next)
  if(!vst[i >> 1 ])
  {
    vst[i>>1] = 1;
    v = e[i].v;
    if(dfn[v] == -1 )
    {
      tarjan(v);
      low[u] = min(low[u] ,low[v]);
      if(dfn[u] < low[v] )
      {
        e[i].isbri = 1 ;
        e[i^1].isbri = 1;
      }
    }
    else if(vis[v] == 1 ) low[u] = min(low[u] , dfn[v]);
  }
  vis[u] = 2;
}
void dfs(int u )
{
  col[u] = scnt;
  for(int i = head[u] ; i != -1; i = e[i].next)
    if(e[i].isbri == false && col[e[i].v] == -1)
      dfs(e[i].v);
}
void base()
{
  memset(dfn,-1,sizeof(dfn));
  memset(vst,0,sizeof(vst));
  memset(vis,0,sizeof(vis));
  dep = 0 ;
  for(int i = 1 ; i <= n ; i ++ )
    if(dfn[i] == -1)
      tarjan(i);
  memset(col,-1,sizeof(col));
  scnt = 0 ;
  for(int i = 1 ; i <= n ; i ++ )
  {
    if(col[i] == -1)
    {
      scnt ++ ;
      dfs(i);
    }
  }
  //printf("scnt = %d\n",scnt);
  memset(deg,0,sizeof(deg));
  for(int i = 1; i <= n; i ++ )
  {
    for(int j = head[i] ; j != -1 ; j =e[j].next)
    {
      if(e[j].isbri )
      {
        //jianbian
        deg[col[i]] ++ ;
        deg[col[e[j].v]] ++ ;
      }
    }
  }
}
/*
初始化 init();
加边 add() , cnt从0开始为边数
scnt为边双连通分两个数，从1开始
num为每个bcc中的点的个数
deg为每个bcc的度数
.isbri表示该边是不桥
可以处理重边
*/
