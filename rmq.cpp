int rmq[maxn] ; // dep
struct RMQ
{
  int lg[maxn + 5];
  int _min[20][maxn + 5 ];
  int n;
  RMQ()
  {
    lg[0] = -1;
    for(int i = 1 ; i < maxn ; i++ )
    {
      lg[i] = ((i&(i - 1)) == 0 ) ? lg[i-1] + 1 :lg[i-1];
      _min[0][i] = i ;
    }
  }
  void init(int _n )
  {
     n = _n ;
     for(int i = 1 ;i <= lg[n] ; i ++ )
     {
       for(int j = 1 ;j <= n + 1 - (1 << i ) ; j ++ )
       {
         int a = _min[i-1][j];
         int b = _min[i-1][j + (1<<(i-1))];
         _min[i][j] = rmq[a] < rmq[b] ? a : b ;
       }
     }
  }
  int getmin(int s, int t)
  {
    if(s > t ) swap(s,t);
    int k = lg[t - s + 1 ];
    int a = _min[k][s];
    int b = _min[k][t - (1 << k) + 1 ];
    if(rmq[a] < rmq[b]) return a;
    else return b ;
  }
};
RMQ st;