#define MAXN 100010
int len;
int sorted[MAXN];
int toLeft[20][MAXN],val[20][MAXN];
void build(int d,int l,int r) {
    if(l==r)return;
    int m=(l+r)>>1;
    int lsame=m-l+1;//lsame表示和val_mid相等且分到左边的
    for(int i=l; i<=r; i++)
        if(val[d][i]<sorted[m])
            lsame--;////先假设左边的数(mid - l + 1)个都等于val_mid,然后把实际上小于val_mid的减去
    int lpos=l;
    int rpos=m+1;
    int same=0;
    for(int i=l; i<=r; i++) {
        if(i==l) {
            toLeft[d][i]=0;//toLeft[i]表示[ l , i ]区域里有多少个数分到左边
        } else {
            toLeft[d][i]=toLeft[d][i-1];
        }
        if(val[d][i]<sorted[m]) {
            toLeft[d][i]++;
            val[d+1][lpos++]=val[d][i];
        } else if(val[d][i]>sorted[m]) {
            val[d+1][rpos++]=val[d][i];
        } else {
            if(same<lsame) { //有lsame的数是分到左边的
                same++;
                toLeft[d][i]++;
                val[d+1][lpos++]=val[d][i];
            } else {
                val[d+1][rpos++]=val[d][i];
            }
        }
    }
    build(d+1,l,m);
    build(d+1,m+1,r);
}

int query(int L,int R,int k,int d,int l,int r) {
    if(l==r) return val[d][l];
    int s;//s表示[ L , R ]有多少个分到左边
    int ss;//ss表示 [l , L-1 ]有多少个分到左边
    int m=(l+r)>>1;
    if(L==l) {
        s=toLeft[d][R];
        ss=0;
    } else {
        s=toLeft[d][R]-toLeft[d][L-1];
        ss=toLeft[d][L-1];
    }
    if(s>=k)//有多于k个分到左边,显然去左儿子区间找第k个
        return query(l+ss,l+ss+s-1,k,d+1,l,m);
    else
        return query(m+L-l-ss+1,m-l-ss+R-s+1,k-s,d+1,m+1,r);
}