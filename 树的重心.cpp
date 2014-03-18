int findroot(int cur) {
    int i, j, x, rear = 0, max, min = INF, root;
    q[rear ++] = cur, fa[cur] = 0;
    for(i = 0; i < rear; i ++) {
        x = q[i];
        for(j = first[x]; j != -1; j = next[j])
            if(!del[v[j]] && v[j] != fa[x])
                q[rear ++] = v[j], fa[v[j]] = x;
    }
    for(i = rear - 1; i >= 0; i --) {
        x = q[i];
        size[x] = 1, max = 0;
        for(j = first[x]; j != -1; j = next[j])
            if(!del[v[j]] && v[j] != fa[x])
                size[x] += size[v[j]], max = Max(max, size[v[j]]);
        max = Max(max, rear - size[x]);
        if(max < min)
            min = max, root = x;
    }
    return root;
}
