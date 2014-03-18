struct heap
{
    int len;
    int a[maxn];
    int k[maxn];
    void heap_down(int s)
    {
        int m = len - 1;
        for(int j = 2 * s + 1; j <= m ;j = 2 * j + 1 )
        {
            if(j < m && a[j] > a[j+1]) j ++ ;
            if(a[s] <= a[j] ) break;
            swap(a[s],a[j]);swap(k[s],k[j]);
            s = j ;
        }
    }
    void heap_up(int p)
    {
        int s;
        while(p)
        {
            s = (p-1)/ 2;
            if(a[s] > a[p])
            {
                swap(a[s],a[p]);
                swap(k[s],k[p]);
                p = s ;
            }
            else break;
        }
    }
    void insert(int x,int y)
    {
        a[len] = x;
        k[len] = y;
        heap_up(len);
        len ++ ;
    }
    void del()
    {
        swap(a[0] ,a[len-1]);
        swap(k[0],k[len-1]);
        len -- ;
        heap_down(0);
    }
    void build()
    {
        for(int i = len / 2 ;i >= 0; i -- )
            heap_down(i);
    }
};
heap hh;
