#define maxn 403

const double eps = 1e-5;

double x[maxn],y[maxn];
double xi[maxn],yi[maxn];
double tx[maxn],ty[maxn];
double _max ;
double tmp;
int n ;
double dist(double x ,double y ,double xx , double yy )
{
  return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}
double calc(double t)
{
  for(int i = 1; i <= n ; i ++ )
  {
    tx[i] = x[i] + xi[i] * t ;
    ty[i] = y[i] + yi[i] * t ;
  }
  _max = 0;
  for(int i =1 ; i <= n ; i ++ )
  {
    for(int j= i + 1; j <= n ; j ++ )
    {
      _max = max(_max , dist(tx[i],ty[i],tx[j],ty[j]));
    }
  }
  return _max;
}
void Solve()
{
  double Left, Right;
  double mid, midmid;
  double mid_area, midmid_area;
  Left = 0.0;
  Right = 21000000.0;
  while (Left + eps < Right)
  {
    mid = (Left + Right) / 2;
    midmid = (mid + Right) / 2;
    mid_area = calc(mid);
    midmid_area = calc(midmid);
    // 假设求解最大极值.
    if (mid_area <= midmid_area) Right = midmid;
    else Left = mid;
  }
  printf("%.2lf %.2lf\n",Left,midmid_area);
}


int main()
{
  int cas;
  int cast = 0 ;
  scanf("%d",&cas);
  while(cas -- )
  {
    scanf("%d",&n);
    for(int i = 1; i <= n ; i ++ )
    {
      scanf("%lf%lf%lf%lf",&x[i],&y[i],&xi[i],&yi[i]);
    }
    printf("Case #%d: ", ++ cast);
    Solve();
  }
  return 0;
}
