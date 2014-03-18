#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

#define abs(x) ((x)>=0?(x):-(x))
#define i64 long long
#define u32 unsigned int
#define u64 unsigned long long
#define clr(x,y) memset(x,y,sizeof(x))
#define PI acos(-1.0)
#define sqr(x) ((x)*(x))

#define mod 1000000007

int f[105][105][205][4] ;
int hash[256];
int n,m;
struct ACmation {
  static const int UNDEF = 0;
  static const int MAXN = 10240;
  static const int CHARSET = 2;

  int end;
  int count[MAXN];
  int fail[MAXN];
  int ch[MAXN][CHARSET];

  void init() {
    count[0] = UNDEF;
    fill(ch[0], ch[0] + CHARSET, -1);
    end = 1;
  }

  void add(int m, const int* s, int t) {
    int p = 0;
    for (int i = 0; i < m; ++i) {
      if (ch[p][*s] == -1) {
        count[end] = UNDEF;
        fill(ch[end], ch[end] + CHARSET, -1);
        ch[p][*s] = end++;
      }
      p = ch[p][*s];
      ++s;
    }
    count[p] |= t;
  }

  void build() {
    queue<int> bfs;
    fail[0] = 0;
    for (int i = 0; i < CHARSET; ++i) {
      if (ch[0][i] != -1) {
        fail[ch[0][i]] = 0;
        bfs.push(ch[0][i]);
      } else {
        ch[0][i] = 0;
      }
    }
    while (!bfs.empty()) {
      int p = bfs.front();
      count[p] |= count[fail[p]];
      bfs.pop();
      for (int i = 0; i < CHARSET; ++i) {
        if (ch[p][i] != -1) {
          fail[ch[p][i]] = ch[fail[p]][i];
          bfs.push(ch[p][i]);
        } else {
          ch[p][i] = ch[fail[p]][i];
        }
      }
    }
  }
  int solve()
  {
    memset(f,0,sizeof(f));
    f[0][0][count[0]][0] = 1 ;
    int tmp ;
    for(int x = 0 ; x <= n ; x ++ )
    {
      for(int y = 0 ; y <= m; y ++ )
      {
        for(int i = 0 ; i < end; i ++  )
        {
          for(int cur = 0 ; cur < 4; cur ++  )
          {
            //printf("count[i] = %d\n",count[i]);
            if(x + 1 <= n )
            {
              tmp = cur | count[ch[i][0]];
              f[x+1][y][ch[i][0]][tmp] = (f[x][y][i][cur] + f[x+1][y][ch[i][0]][tmp] ) % mod;
             // printf("%d %d %d %d %d\n",x+1,y,ch[i][0],tmp,f[x+1][y][ch[i][0]][tmp]);
            }
            if(y + 1 <= m )
            {
              tmp = cur | count[ch[i][1]];
              f[x][y+1][ch[i][1]][tmp] =  (f[x][y][i][cur] + f[x][y+1][ch[i][1]][tmp] ) % mod;
              //printf("%d %d %d %d %d\n",x,y+1,ch[i][0],tmp,f[x][y+1][ch[i][0]][tmp]);
            }
          }
        }
      }
    }
    int res;
    res = 0 ;
    for(int i = 0 ; i < end ; i ++ )
    {
      res = (f[n][m][i][3] + res) % mod ;
    }
    return res % mod ;
  }
} ac;
char str[106];
int len ;
int te[106];
int main()
{
  int cas;
  memset(hash,-1,sizeof(hash));
  hash['D'] = 0 ;
  hash['R'] = 1 ;
  scanf("%d",&cas);
  while(cas -- )
  {
    scanf("%d%d",&m,&n);
    ac.init();
    for(int k = 0; k < 2; k ++ )
    {
      scanf("%s",str);
      len = strlen(str);
      for(int i = 0; i < len ; i ++ )
        te[i] = hash[str[i]];
      ac.add(len,te,1<<k);
    }

    ac.build();
    int ans ;
    ans = ac.solve();
    printf("%d\n",ans);
  }
  return 0;
}
