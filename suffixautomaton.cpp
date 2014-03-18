#define N 2010
#define MAXQ 10010

struct Suffix_Automaton
{
    int F[N << 1],ant,last,ch[N << 1][26],step[N << 1];

    void init()
    {
        last = ant = 1;
        memset(F,0,sizeof(F));
        memset(ch,0,sizeof(ch));
        memset(step,0,sizeof(step));
    }

    void ins(int x)
    {
        int t = ++ant, pa = last;
        step[t] = step[last] + 1;
        last = t;
        for( ; pa && !ch[pa][x]; pa = F[pa] )
            ch[pa][x] = t;
        if( pa == 0 ) F[t] = 1;
        else if( step[pa] + 1 == step[ ch[pa][x] ] )
            F[t] = ch[pa][x];
        else
        {
            int nq = ++ant, q = ch[pa][x];
            memcpy( ch[nq], ch[q], sizeof(ch[nq]) );
            step[nq] = step[pa] + 1;
            F[nq] = F[q];
            F[q] = F[t] = nq;
            for( ; pa && ch[pa][x] == q; pa = F[pa] )
                ch[pa][x] = nq;
        }
	}
};


const int MAX_N = 250000 + 10;
char buf[MAX_N];
struct State {
	State*suf, *go[26];
	int val;
	State() :
			suf(0), val(0) {
		memset(go, 0, sizeof go);
	}
}*root, *last;
State statePool[MAX_N * 2], *cur;

void init() {
	cur = statePool;
	root = last = cur++;
}

void extend(int w) {
	State*p = last, *np = cur++;
	np->val = p->val + 1;
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p)
		np->suf = root;
	else {
		State*q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q;
		} else {
			State*nq = cur++;
			memcpy(nq->go, q->go, sizeof q->go);
			nq->val = p->val + 1;
			nq->suf = q->suf;
			q->suf = nq;
			np->suf = nq;
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	last = np;
}
