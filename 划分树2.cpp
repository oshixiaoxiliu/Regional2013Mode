#define MAXN 100010
int len;
int sorted[MAXN];
int toLeft[20][MAXN],val[20][MAXN];
void build(int d,int l,int r) {
    if(l==r)return;
    int m=(l+r)>>1;
    int lsame=m-l+1;//lsame��ʾ��val_mid����ҷֵ���ߵ�
    for(int i=l; i<=r; i++)
        if(val[d][i]<sorted[m])
            lsame--;////�ȼ�����ߵ���(mid - l + 1)��������val_mid,Ȼ���ʵ����С��val_mid�ļ�ȥ
    int lpos=l;
    int rpos=m+1;
    int same=0;
    for(int i=l; i<=r; i++) {
        if(i==l) {
            toLeft[d][i]=0;//toLeft[i]��ʾ[ l , i ]�������ж��ٸ����ֵ����
        } else {
            toLeft[d][i]=toLeft[d][i-1];
        }
        if(val[d][i]<sorted[m]) {
            toLeft[d][i]++;
            val[d+1][lpos++]=val[d][i];
        } else if(val[d][i]>sorted[m]) {
            val[d+1][rpos++]=val[d][i];
        } else {
            if(same<lsame) { //��lsame�����Ƿֵ���ߵ�
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
    int s;//s��ʾ[ L , R ]�ж��ٸ��ֵ����
    int ss;//ss��ʾ [l , L-1 ]�ж��ٸ��ֵ����
    int m=(l+r)>>1;
    if(L==l) {
        s=toLeft[d][R];
        ss=0;
    } else {
        s=toLeft[d][R]-toLeft[d][L-1];
        ss=toLeft[d][L-1];
    }
    if(s>=k)//�ж���k���ֵ����,��Ȼȥ����������ҵ�k��
        return query(l+ss,l+ss+s-1,k,d+1,l,m);
    else
        return query(m+L-l-ss+1,m-l-ss+R-s+1,k-s,d+1,m+1,r);
}