#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<math.h>
#define inf 0x3fffffff
using namespace std;
const int N = 305; /*����*/
const int M = 4000; /*����*/
int map[N][N];  /* 01����� */
int U[M], D[M], R[M], L[M], rs[N];
int size[N], head, row[M], col[M];
int n, m, k;
int ans[N], ansL;
bool yes;
int nodecnt;
void read() {
    /* �����ʼ�� */
}
void init(int m) {
    /* ��ʼ����m Ϊ���� */
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
    /* �˺���ʹ�ü��ʲ��� */
    /* ����ĺϷ��ԣ���ѡ����д���ans������ */
}
void dfs(int num) {
    if (num >= ansL) return; /* ���ѡ�������еĽ�ķ�������ע�͵������Ǿ� */
    if (R[0] == 0) {
        ansL = num; /* ansL Ϊ�������ѡ�еĸ������༴ ans ��������ĸ��� */
        yes = check(); /* �����ж�����н⣬����ĺϷ��� */
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
        if (yes) return; /* ���Ҫ�����ѡ�����������Ľ⣬��һ��Ҫע�͵� */
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
        /* һЩ��� */
        /* �� 01 ������������������������Щ��Ŀ����ֱ�ӵõ� tt ���� */
    }
    int tt[N], c = 0;
    int t = n * k + 1;
    for (int i = 1; i < t; i++) { /* ɨһ�����е��У����ÿһ�е� 1 */
        c = 0;
        for (int j = 1; j < t; j++)
            if (map[i][j] == 1) tt[c++] = j;
        insert(i, tt, c); /*���룬tt ���������� 01 ������ÿһ������1���ڵ��У�c Ϊ 1 �ĸ���*/
    }
}
void solve() {
    ansL = inf;
    yes = false;
    dfs(0);
    if (yes) {
        /*����𰸣���ѡ����д��� ans ������*/
    } else {
        /* ����޽���Ϣ */
        puts("No solution");
    }
    return;
}
int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        read();         /* �����ʼ�� */
        init(n * k);    /* ��ʼ����n*k Ϊ���� */
        build();        /* ��ͼ */
        solve();        /* ������� */
    }
    return 0;
}&nbsp;