#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<math.h>
#define inf 0x3fffffff
using namespace std;
const int N = 305; /*列数*/
const int M = 4000; /*点数*/
int map[N][N];  /* 01矩阵表 */
int U[M], D[M], R[M], L[M], rs[N];
int size[N], head, row[M], col[M];
int n, m, k;
int ans[N], ansL;
bool yes;
int nodecnt;
void read() {
    /* 读入初始化 */
}
void init(int m) {
    /* 初始化，m 为列数 */
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
inline void remove(int id) {
    int i, j;
    R[ L[id] ] = R[id];
    L[ R[id] ] = L[id];
    for (i = D[id]; i != id; i = D[i])
        for (j = R[i]; j != i; j = R[j]) {
            U[ D[j] ] = U[j];
            D[ U[j] ] = D[j];
            size[ col[j] ]--;
        }
}
inline void resume(int id) {
    int i, j;
    for (i = U[id]; i != id; i = U[i])
        for (j = L[i]; j != i; j = L[j]) {
            size[ col[j] ]++;
            U[ D[j] ] = j;
            D[ U[j] ] = j;
        }
    R[ L[id] ] = id;
    L[ R[id] ] = id;
}
int check() {
    /* 此函数使用几率不大 */
    /* 检查解的合法性，所选择的列存在ans数组中 */
}
void dfs(int num) {
    if (num >= ansL) return; /* 输出选择最少行的解的方案，须注释掉下面那句 */
    if (R[0] == 0) {
        ansL = num; /* ansL 为该组解所选行的个数，亦即 ans 数组里面的个数 */
        yes = check(); /* 可能有多组可行解，检查解的合法性 */
        return;
    }
    int i, j, id = 0, min = inf;
    for (i = R[0]; i != 0; i = R[i])
        if (size[i] < min) {
            min = size[i];
            id = i;
        }
    remove(id);
    for (i = D[id]; i != id; i = D[i]) {
        ans[num] = row[i];
        for (j = R[i]; j != i; j = R[j])
            remove(col[j]);
        dfs(num + 1);
        if (yes) return; /* 如果要求输出选择最少行数的解，这一句要注释掉 */
        for (j = L[i]; j != i; j = L[j])
            resume(col[j]);
    }
    resume(id);
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
    memset(map, 0, sizeof (map));
    {
        /* 一些语句 */
        /* 建 01 矩阵，这里可以视情况而定，有些题目可以直接得到 tt 数组 */
    }
    int tt[N], c = 0;
    int t = n * k + 1;
    for (int i = 1; i < t; i++) { /* 扫一遍所有的行，检查每一行的 1 */
        c = 0;
        for (int j = 1; j < t; j++)
            if (map[i][j] == 1) tt[c++] = j;
        insert(i, tt, c); /*插入，tt 数组里面是 01 矩阵里每一行里面1所在的列，c 为 1 的个数*/
    }
}
void solve() {
    ansL = inf;
    yes = false;
    dfs(0);
    if (yes) {
        /*处理答案，所选择的行存在 ans 数组中*/
    } else {
        /* 输出无解信息 */
        puts("No solution");
    }
    return;
}
int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        read();         /* 读入初始化 */
        init(n * k);    /* 初始化，n*k 为列数 */
        build();        /* 建图 */
        solve();        /* 问题求解 */
    }
    return 0;
}&nbsp;