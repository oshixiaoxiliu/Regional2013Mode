*用dp[row][col][i][j]表示(row,col)到(row+2^i,col+2^j)矩形内的最小值
*查询的时候
*  int kx = log(double(x2 - x1 +1)) / log(2.0);
int ky = log(double(y2 - y1 +1)) / log(2.0);
int m1 = dp[x1][y1][kx][ky];
int m2 = dp[x2-(1<<kx)+1][y1][kx][ky];
int m3 = dp[x1][y2-(1<<ky)+1][kx][ky];
int m4 = dp[x2-(1<<kx)+1][y2-(1<<ky)+1][kx][ky];
*取4个值里面的最小值(有种二分的思想)
*/

const int maxn = 310;

int mat[maxn][maxn];
int dp[maxn][maxn][9][9];
int n , q;

void rmq_2d(void) {
    for(int row = 1 ; row <= n ; row++)
        for(int col = 1 ; col <= n ; col++)
            dp[row][col][0][0] = mat[row][col];
    int m = log((double)n) / log(2.0);

    for(int i = 0 ; i <= m ; i++) {
        for(int j = 0 ; j <= m ; j++) {
            if(i == 0 && j == 0)
                continue;
            for(int row = 1 ; row+(1<<i)-1 <= n ; row++) {
                for(int col = 1 ; col+(1<<j)-1 <= n ; col++) {
                    if(i == 0) {
                        dp[row][col][i][j] = min(dp[row][col][i][j-1] , dp[row][col+(1<<(j-1))][i][j-1]);
                    } else {
                        dp[row][col][i][j] = min(dp[row][col][i-1][j] , dp[row+(1<<(i-1))][col][i-1][j]);
                    }
                }
            }
        }
    }
}

int query_2d(int x1,int x2,int y1,int y2) {
    int kx = log(double(x2 - x1 +1)) / log(2.0);
    int ky = log(double(y2 - y1 +1)) / log(2.0);
    int m1 = dp[x1][y1][kx][ky];
    int m2 = dp[x2-(1<<kx)+1][y1][kx][ky];
    int m3 = dp[x1][y2-(1<<ky)+1][kx][ky];
    int m4 = dp[x2-(1<<kx)+1][y2-(1<<ky)+1][kx][ky];
    return min( min(m1,m2), min(m3,m4) );
}
