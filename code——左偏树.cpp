struct tree {
    int l, r, v, dis, f;
} heap[maxn];


int merge( int a, int b ) {
    if( a == 0 ) return b;
    if( b == 0 ) return a;
    if( heap[a].v < heap[b].v ) swap( a, b );
    heap[a].r = merge( heap[a].r, b );
    heap[heap[a].r].f = a;
    if( heap[heap[a].l].dis < heap[heap[a].r].dis ) swap( heap[a].l, heap[a].r );
    if( heap[a].r == 0 ) heap[a].dis = 0;
    else heap[a].dis = heap[heap[a].r].dis + 1;
    return a;
}


int pop( int a ) {
    int l = heap[a].l;
    int r = heap[a].r;
    heap[l].f = l;
    heap[r].f = r;
    heap[a].l = heap[a].r = heap[a].dis = 0;
    return merge(l, r);
}


int find( int a ) {
    return heap[a].f == a ? a : find( heap[a].f ) ;
}

/*
支持合并，插入，删除最小值三个操作。
后两个操作都可以看成第一个操作的拓展，
如删除最小值是合并根的两棵子树，插入则直接将元素看作一个左偏树—
所以只要写个Merge就可以了！
性质:
节点的键值小于或等于它的左右子节点的键值。
节点的左子节点的距离不小于右子节点的距离。
节点的左子节点右子节点也是一颗左偏树。
*/
