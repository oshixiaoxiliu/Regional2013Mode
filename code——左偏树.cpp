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
֧�ֺϲ������룬ɾ����Сֵ����������
���������������Կ��ɵ�һ����������չ��
��ɾ����Сֵ�Ǻϲ���������������������ֱ�ӽ�Ԫ�ؿ���һ����ƫ����
����ֻҪд��Merge�Ϳ����ˣ�
����:
�ڵ�ļ�ֵС�ڻ�������������ӽڵ�ļ�ֵ��
�ڵ�����ӽڵ�ľ��벻С�����ӽڵ�ľ��롣
�ڵ�����ӽڵ����ӽڵ�Ҳ��һ����ƫ����
*/
