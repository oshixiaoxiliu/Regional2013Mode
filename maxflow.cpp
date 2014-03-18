#define INF 0x3f3f3f3f
const int inf = 0x7fffffff;

struct MaxFlow {
    int size, n;
    int st, en, maxflow, mincost;
    bool vis[maxn];
    int net[maxn], pre[maxn], cur[maxn], dis[maxn];
    std::queue <int> Q;
    struct EDGE {
        int v, cap, cost, next;
        EDGE() {}
        EDGE(int a, int b, int c, int d) {
            v = a, cap = b, cost = c, next = d;
        }
    } E[maxm<<1];
    void init(int _n) {
        n = _n, size = 0;
        memset(net, -1, sizeof(net));
    }
    void add_edge(int u, int v, int cap, int cost) {
        E[size] = EDGE(v, cap, cost, net[u]);
        net[u] = size++;
        E[size] = EDGE(u, 0, -cost, net[v]);
        net[v] = size++;
    }
    bool adjust() {
        int v, min = inf;
        for(int i = 0; i <= n; i++) {
            if(!vis[i])
                continue;
            for(int j = net[i]; v = E[j].v, j != -1; j = E[j].next)
                if(E[j].cap)
                    if(!vis[v] && dis[v]-dis[i]+E[j].cost < min)
                        min = dis[v] - dis[i] + E[j].cost;
        }
        if(min == inf)
            return false;
        for(int i = 0; i <= n; i++)
            if(vis[i])
                cur[i] = net[i], vis[i] = false, dis[i] += min;
        return true;
    }
    int augment(int i, int flow) {
        if(i == en) {
            mincost += dis[st] * flow;
            maxflow += flow;
            return flow;
        }
        vis[i] = true;
        for(int j = cur[i], v; v = E[j].v, j != -1; j = E[j].next) {
            if(!E[j].cap)
                continue;
            if(vis[v] || dis[v]+E[j].cost != dis[i])
                continue;
            int delta = augment(v, std::min(flow, E[j].cap));
            if(delta) {
                E[j].cap -= delta;
                E[j^1].cap += delta;
                cur[i] = j;
                return delta;
            }
        }
        return 0;
    }
    void spfa() {
        int u, v;
        for(int i = 0; i <= n; i++)
            vis[i] = false, dis[i] = inf;
        dis[st] = 0;
        Q.push(st);
        vis[st] = true;
        while(!Q.empty()) {
            u = Q.front(), Q.pop();
            vis[u] = false;
            for(int i = net[u]; v = E[i].v, i != -1; i = E[i].next) {
                if(!E[i].cap || dis[v] <= dis[u] + E[i].cost)
                    continue;
                dis[v] = dis[u] + E[i].cost;
                if(!vis[v]) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
        for(int i = 0; i <= n; i++)
            dis[i] = dis[en] - dis[i];
    }
    int zkw(int s, int t) {
        st = s, en = t;
        spfa();
        mincost = maxflow = 0;
        for(int i = 0; i <= n; i++)
            vis[i] = false, cur[i] = net[i];
        do {
            while(augment(st, inf))
                memset(vis, false, sizeof(vis));
        } while(adjust());
        return mincost;
    }
};
MaxFlow townboy;
