#include<iostream>
#include<cstdio>
#include<string.h>
#include<vector>
#include<math.h>
#define inf 0x3fffffff
using namespace std;
const int N = 1005;
const int M = 4000;
int U[M], D[M], R[M], L[M], rs[N];
int size[N], head, row[M], col[M];
int n, m, k;
int nodecnt, ans;
void init(int m) {
    memset(size, 0, sizeof (size));
    memset(col, -1, sizeof (col));
    nodecnt = m + 1;
    for (int i = 0; i <= m; i++) {
        L[i] = (i - 1);
        R[i] = (i + 1);
        col[i] = i;
        D[i] = U[i] = i;
    }
    L[0] = m;
    R[m] = 0;
    size[0] = INT_MAX;
}
inline void Remove(int x) {
    for (int i = D[x]; i != x; i = D[i]) {
        L[ R[i] ] = L[i];
        R[ L[i] ] = R[i];
        size[ col[i] ]--;
    }
}
inline void Resume(int x) {
    for (int i = U[x]; i != x; i = U[i]) {
        L[ R[i] ] = R[ L[i] ] = i;
        size[ col[i] ]++;
    }
}
int rec[N];
inline int evalute() { /* 估价函数 */
    bool vis[40] = {false};
    int tt = 0;
    for (int i = R[0]; i != 0; i = R[i])
        if (!vis[col[i]]) {
            tt++;
            vis[col[i]] = true;
            for (int j = D[i]; j != i; j = D[j])
                if (col[j] != 0)
                    for (int k = R[j]; k != j; k = R[k]) vis[ col[k] ] = true;
        }
    return tt;
}
int dfs(int num) {  /*这里的dfs是一个迭代加深的过程*/
    if (num + evalute() > ans) return 0;
    if (R[0] == 0) return 1;
    int i, j, opt = 0;
    for (i = R[0]; i != 0; i = R[i])
        if (size[col[i]] < size[col[opt]]) {
            opt = i;
            if (size[col[i]] <= 1) break;
        }
    for (i = D[opt]; i != opt; i = D[i]) {
        Remove(i);
        for (j = R[i]; i != j; j = R[j]) Remove(j);
        if (dfs(num + 1)) return 1;
        for (j = L[i]; j != i; j = L[j]) Resume(j);
        Resume(i);
    }
    return 0;
}
inline void insert(int i, int *tt, int c) {
    for (int j = 0; j < c; j++, nodecnt++) {
        int x = tt[j];
        row[nodecnt] = i;
        col[nodecnt] = x;
        size[x]++;
        U[nodecnt] = x;
        D[nodecnt] = D[x];
        U[D[x]] = nodecnt;
        D[x] = nodecnt;
        if (j == 0) L[nodecnt] = R[nodecnt] = nodecnt;
        else {
            L[nodecnt] = nodecnt - 1;
            R[nodecnt] = nodecnt - j;
            R[nodecnt - 1] = nodecnt;
            L[nodecnt - j] = nodecnt;
        }
    }
}
void build() {
    /*建图过程，同精确覆盖，通过 insert(i,tt,c) 完成*/
}
void solve() {
    ans = 0;
    while (!dfs(0)) {
        ans++;
        if (ans > m) break;
    }
    /*解题过程*/
}
int main() {
    while (scanf("%d%d%d", &n, &m, &k)!=EOF) {
        read();     /*读入初始化*/
        build();    /*建图过程*/
        solve();    /*解题过程*/
    }
    return 0;
}