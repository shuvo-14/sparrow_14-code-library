// https://codeforces.com/contest/342/problem/E
#include<bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define pb push_back
#define ff first
#define ss second
#define int long long
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;
const int inf = 1e9;
const int N=1e5+9,LG=18;
vector<int>g[N];

int depth[N],par[N][LG+1];
int dis[N];
bool mark[N];
int centroid_par[N];
void dfs(int u, int p = 0)
{
    depth[u] = depth[p] + 1;
    par[u][0] = p;
    for(int i = 1; i <= LG; i++)
    {
        par[u][i] = par[par[u][i-1]][i-1];
    }
    for(int v : g[u])
    {
        if(v == p) continue;
        dfs(v,u);
    }
}
int sz[N];
int len;
void get_size(int u, int p)
{
    sz[u] = 1;
    len++;
    for(int v : g[u])
    {
        if(v == p or mark[v]) continue;
        get_size(v,u);
        sz[u] += sz[v];
    }
}
int get_centroid(int u, int p)
{
    for(int v : g[u])
    {
        if(v != p and !mark[v] and sz[v] > len/2) 
            return get_centroid(v,u);
    }
    return u;
}

void decompose(int u, int p)
{
    len = 0;
    get_size(u,u);
    int centroid = get_centroid(u,u);
    mark[centroid] = 1;
    centroid_par[centroid] = p;
    for(int v : g[centroid])
    {
        if(v == p or mark[v]) continue;
        decompose(v,centroid);
    }
}
int get_lca(int u, int v)
{
    if(depth[u] < depth[v]) swap(u,v);
    int d = depth[u] - depth[v];
    for(int i = LG; i >= 0; i--) 
    {
        if(d & (1<<i)) u = par[u][i];
    }
    if(u == v) return u;
    for(int i = LG; i >= 0; i--)
    {
        if(par[u][i] != par[v][i]) 
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
int distance(int u, int v)
{
    return depth[u] + depth[v] - 2 * depth[get_lca(u,v)];
}
void modify(int i)
{
    int cur = i;
    dis[cur] = 0;
    while(cur)
    {
        dis[cur] = min(dis[cur],distance(cur,i));
        cur = centroid_par[cur];
    }
}
int query(int i)
{
    int res = inf;
    int cur = i;
    while(cur)
    {
        res = min(res,dis[cur] + distance(cur,i));
        cur = centroid_par[cur];
    }
    return res;
}
void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) dis[i] = inf;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1);
    decompose(1,0);
    modify(1);
    while(q--)
    {
        int t, v;
        cin >> t >> v;
        if(t == 1)
        {
            modify(v);
        }
        else 
        {
            cout << query(v) << endl;
        }
    }
}

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
   // cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
