
//https://codeforces.com/contest/1790/problem/F

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
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define int long long
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;
const int inf = 1e15;
const int N=2e5+9;
vector<int>g[N];
int T[N][20];
int q[N],depth[N],sz[N],par[N];
vector<int>ans;
bool mark[N];
int len;
void init(int n)
{
    for(int i = 0; i <= n; i++)
    {
        g[i].clear();
        depth[i] = 0;
        par[i] = 0;
        ans[i] = inf;
        mark[i] = 0;
        for(int j = 0; j < 20; j++) T[i][j] = 0;
    }
}

void dfs(int u, int p = 0)
{
    depth[u] = depth[p] + 1;
    T[u][0] = p;
    for(int j = 1; j < 20; j++)
    {
         T[u][j] = T[T[u][j-1]][j-1];
    }
    for(int v : g[u])
    {
        if(v == p) continue;
        dfs(v,u);
    }
}
void computesize(int u, int p)
{
    sz[u] = 1;
    len++;
    for(int v : g[u])
    {
        if(v == p or mark[v]) continue;
        computesize(v,u);
        sz[u] += sz[v];
    }
}
int getCentroid(int u, int p)
{
    for(int v : g[u])
    {
        if(mark[v] or v == p) continue;
        if(sz[v] > len/2) return getCentroid(v,u);
    }
    return u;
}
void decompose(int u, int p)
{
    len = 0;
    computesize(u,u);
    int centroid = getCentroid(u,u);
    mark[centroid] = 1;
   // debug(centroid,p,len,sz[centroid]);
    par[centroid] = p;
    for(int v : g[centroid])
    {
        if(mark[v]) continue;
        decompose(v,centroid);
    }
}
int lca(int u, int v)
{
  //  debug(u,v);
    if(depth[u] < depth[v]) swap(u,v);
    int d = depth[u] - depth[v];
    for(int i = 0; i < 20; i++)
    {
        if(d & (1<<i)) u = T[u][i];
    }
  //  debug(u,v);
  //  debug(11111111);
    if(u == v) return u;
    for(int i = 19; i >= 0; i--)
    {
        if(T[u][i] != T[v][i])
        {
            u = T[u][i];
            v = T[v][i];
        }
    }
    return T[u][0];
}
int distance(int u, int v)
{
    //debug(u,v,lca(u,v));
    return depth[u] + depth[v] - 2 * depth[lca(u,v)];
}
void modify(int u)
{
    int now = u;
   // debug(u);
    while(now)
    {
        //debug(now);
        int d = distance(now,u);
       // debug(now,u,d);
        ans[now] = min(ans[now],distance(now,u));
       // debug(now,par[now]);
        now = par[now];
    }
}
int query(int u)
{
    //debug(u);
    int mn = inf;
    int now = u;
    while(now)
    {
       // debug(now);
        mn = min(mn,ans[now]+distance(now,u));
        now = par[now];
    }
    return mn;
}
void solve()
{
    int n, s;
    cin >> n >> s;
    ans.resize(n+1);
    init(n);
    for(int i = 1; i < n ;i++) cin >> q[i];
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(s);
    decompose(s,0);
    vector<int>res(n+1,1);
    res[0] = 0;
    modify(s);
   // debug(ans);
    int mn = inf;
    for(int i = 1; i < n; i++)
    {
        mn = min(mn,query(q[i]));
        modify(q[i]);
      //  debug(ans);
        res[i] = mn;
        if(mn == 1) break;
    }
    for(int i = 1; i < n; i++) cout << res[i] << " "; cout << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
    cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
