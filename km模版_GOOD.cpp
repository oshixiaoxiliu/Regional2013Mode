#include <stdio.h>
#include <string.h>
#define M 310
#define inf 0x3f3f3f3f

int n,nx,ny;
int Link[M],lx[M],ly[M],slack[M];    //lx,lyΪ���꣬nx,ny�ֱ�Ϊx�㼯y�㼯�ĸ���
int visx[M],visy[M],w[M][M];

int DFS(int x) {
    visx[x] = 1;
    for (int y = 1; y <= ny; y ++) {
        if (visy[y])
            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if (t == 0) {     //
            visy[y] = 1;
            if (Link[y] == -1||DFS(Link[y])) {
                Link[y] = x;
                return 1;
            }
        } else if (slack[y] > t) //���������ͼ��slack ȡ��С��
            slack[y] = t;
    }
    return 0;
}
int KM() {
    int i,j;
    memset (Link,-1,sizeof(Link));
    memset (ly,0,sizeof(ly));
    for (i = 1; i <= nx; i ++)          //lx��ʼ��Ϊ����������������
        for (j = 1,lx[i] = -inf; j <= ny; j ++)
            if (w[i][j] > lx[i])
                lx[i] = w[i][j];

    for (int x = 1; x <= nx; x ++) {
        for (i = 1; i <= ny; i ++)
            slack[i] = inf;
        while (1) {
            memset (visx,0,sizeof(visx));
            memset (visy,0,sizeof(visy));
            if (DFS(x))     //���ɹ����ҵ�������죩����õ�������ɣ�������һ���������
                break;  //��ʧ�ܣ�û���ҵ�����죩������Ҫ�ı�һЩ��ı�ţ�ʹ��ͼ�п��бߵ��������ӡ�
            //����Ϊ����������������У���������������б���������X����ı��ȫ����ȥһ������d��
            //������������е�Y����ı��ȫ������һ������d
            int d = inf;
            for (i = 1; i <= ny; i ++)
                if (!visy[i]&&d > slack[i])
                    d = slack[i];
            for (i = 1; i <= nx; i ++)
                if (visx[i])
                    lx[i] -= d;
            for (i = 1; i <= ny; i ++) //�޸Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥd
                if (visy[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
        }
    }
    int res = 0;
    for (i = 1; i <= ny; i ++)
        if (Link[i] > -1)
            res += w[Link[i]][i];
    return res;
}

int main () {
    int i,j;
    while (scanf ("%d",&n)!=EOF) {
        nx = ny = n;
        //  memset (w,0,sizeof(w));
        for (i = 1; i <= n; i ++)
            for (j = 1; j <= n; j ++)
                scanf ("%d",&w[i][j]);
        int ans = KM();
        printf ("%d\n",ans);
    }
    return 0;
}
