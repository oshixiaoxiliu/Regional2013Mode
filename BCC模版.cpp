
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
bool vst[maxn * 2]; // ����û�з��ʹ�
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
��ʼ�� init();
�ӱ� add() , cnt��0��ʼΪ����
scntΪ��˫��ͨ������������1��ʼ
numΪÿ��bcc�еĵ�ĸ���
degΪÿ��bcc�Ķ���
.isbri��ʾ�ñ��ǲ���
���Դ����ر�
*/
