const int UNDEF = 0;
const int MAXN = 10004 * 50;
const int CHARSET = 26;
int ans ;
struct ACmation {
    int cnt[MAXN];
    int fail[MAXN];
    int ch[MAXN][CHARSET];
    int end;
    void init() {
        cnt[0] = UNDEF;
        fill(ch[0], ch[0] + CHARSET, -1);
        end = 1;
    }
    void add(char *str) {
        int p = 0;
        int m = strlen(str);
        for (int i = 0; i < m; ++i) {
            if (ch[p][*str - 'a'] == -1) {
                cnt[end] = UNDEF;
                fill(ch[end], ch[end] + CHARSET, -1);
                ch[p][*str - 'a'] = end++;
            }
            p = ch[p][*str -'a'];
            ++str;
        }
        cnt[p] ++ ;
    }
    void build() {
        queue<int> bfs;
        fail[0] = 0;
        for (int i = 0; i < CHARSET; ++i) {
            if (ch[0][i] != -1) {
                fail[ch[0][i]] = 0;
                bfs.push(ch[0][i]);
            } else {
                ch[0][i] = 0;
            }
        }
        while (!bfs.empty()) {
            int p = bfs.front();
            bfs.pop();
            //cnt[p] |= cnt[fail[p]];
            for (int i = 0; i < CHARSET; ++i) {
                if (ch[p][i] != -1) {
                    fail[ch[p][i]] = ch[fail[p]][i];
                    bfs.push(ch[p][i]);
                } else {
                    ch[p][i] = ch[fail[p]][i];
                }
            }
        }
    }
    void find(char *s ) {
        int len , j , u ;
        len = strlen(s);
        u = 0 ;
        for(int i = 0 ; i < len ; i ++ ) {
            j = s[i] - 'a';
            u = ch[u][j];
            for(int k = u ; k ; k = fail[k]) {
                ans += cnt[k] ;
                cnt[k] = 0 ;
            }
        }
        return ;
    }
} ac;
