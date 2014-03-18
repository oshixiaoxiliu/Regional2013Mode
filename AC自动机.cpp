#define maxn 10005*50

int ans ;
struct Trie {
    int ch[maxn][26],fail[maxn],cnt[maxn],sind,root;

    int NewNode() {
        ++sind;
        memset(ch[sind],-1,sizeof(ch[sind]));
        cnt[sind]=0;
        fail[sind]=-1;
        return sind;
    }
    void init() {
        sind=0;
        root=NewNode();
    }

    void ins(char *s ) {
        int len=strlen(s),pos=root;
        for (int i=0; i<len; ++i) {
            int val=s[i]-'a';
            if (ch[pos][val]==-1) ch[pos][val]=NewNode();
            pos=ch[pos][val];
        }
        cnt[pos]++;
    }

    queue<int> Q;
    void getfail() {
        fail[root]=root;
        for (int i=0; i<26; ++i)
            if (ch[root][i]==-1) ch[root][i]=root;
            else {
                fail[ch[root][i]]=root;
                Q.push(ch[root][i]);
            }

        while (!Q.empty()) {
            int pos=Q.front();
			cnt[pos] |= cnt[fail[pos]];
            Q.pop();
            for (int i=0; i<26; ++i)
                if (ch[pos][i]==-1) ch[pos][i]=ch[fail[pos]][i];
                else {
                    fail[ch[pos][i]]=ch[fail[pos]][i];
                    Q.push(ch[pos][i]);
                }
        }
    }

    void find(char *s ) {
        int len=strlen(s),pos=root ;

        for (int i=0; i<len; ++i) {
            int tmp=ch[pos][s[i]-'a'];
            pos=tmp;
            while (tmp!=root) {
                ans += cnt[tmp];
                cnt[tmp]=0;
                tmp=fail[tmp];
            }
        }
    }
} ac;
