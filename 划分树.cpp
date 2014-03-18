#define M 100001
struct Seg_Tree {
    int left,right;
    int mid() {
        return (left + right) >> 1;
    }
} tt[M*4];
int len;
int sorted[M];
int toLeft[20][M];
int val[20][M];
void build(int l,int r,int d,int idx) {
    tt[idx].left = l;
    tt[idx].right = r;
    if(tt[idx].left == tt[idx].right)	return ;
    int mid = tt[idx].mid();
    int lsame = mid - l + 1;//lsame��ʾ��val_mid����ҷֵ���ߵ�
    for(int i = l ; i <= r ; i ++) {
        if(val[d][i] < sorted[mid]) {
            lsame --;//�ȼ�����ߵ���(mid - l + 1)��������val_mid,Ȼ���ʵ����С��val_mid�ļ�ȥ
        }
    }
    int lpos = l;
    int rpos = mid+1;
    int same = 0;
    for(int i = l ; i <= r ; i ++) {
        if(i == l) {
            toLeft[d][i] = 0;//toLeft[i]��ʾ[ tt[idx].left , i ]�������ж��ٸ����ֵ����
        } else {
            toLeft[d][i] = toLeft[d][i-1];
        }
        if(val[d][i] < sorted[mid]) {
            toLeft[d][i] ++;
            val[d+1][lpos++] = val[d][i];
        } else if(val[d][i] > sorted[mid]) {
            val[d+1][rpos++] = val[d][i];
        } else {
            if(same < lsame) {//��lsame�����Ƿֵ���ߵ�
                same ++;
                toLeft[d][i] ++;
                val[d+1][lpos++] = val[d][i];
            } else {
                val[d+1][rpos++] = val[d][i];
            }
        }
    }
    build(l,mid,d+1,LL(idx));
    build(mid+1,r,d+1,RR(idx));
}
int query(int l,int r,int k,int d,int idx) {
    if(l == r) {
        return val[d][l];
    }
    int s;//s��ʾ[ l , r ]�ж��ٸ��ֵ����
    int ss;//ss��ʾ [tt[idx].left , l-1 ]�ж��ٸ��ֵ����
    if(l == tt[idx].left) {
        s = toLeft[d][r];
        ss = 0;
    } else {
        s = toLeft[d][r] - toLeft[d][l-1];
        ss = toLeft[d][l-1];
    }
    if(s >= k) {//�ж���k���ֵ����,��Ȼȥ����������ҵ�k��
        int newl = tt[idx].left + ss;
        int newr = tt[idx].left + ss + s - 1;//������µ�ӳ������
        return query(newl,newr,k,d+1,LL(idx));
    } else {
        int mid = tt[idx].mid();
        int bb = l - tt[idx].left - ss;//bb��ʾ [tt[idx].left , l-1 ]�ж��ٸ��ֵ��ұ�
        int b = r - l + 1 - s;//b��ʾ [l , r]�ж��ٸ��ֵ��ұ�
        int newl = mid + bb + 1;
        int newr = mid + bb + b;
        return query(newl,newr,k-s,d+1,RR(idx));
    }
}

