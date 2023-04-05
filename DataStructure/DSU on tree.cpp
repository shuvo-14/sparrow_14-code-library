// https://codeforces.com/contest/1805/problem/E

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
int sz[N];
vector<int>g[N];
int val[N];
vector<pair<int,int>>edges;
int node_mx[N];
int in[N];
int ft[N];
int timer = 0;
struct DS
{
    map<int,int>cnt;
    multiset<int>mad;
    void add(int u)
    {
        cnt[val[u]]++;
        if(cnt[val[u]] == 2) mad.insert(val[u]);
    }
    void remove(int u)
    {
        cnt[val[u]]--;
        if(cnt[val[u]]==1)
        {
            mad.erase(val[u]);
        }
    }
    int query()
    {
        if(mad.size() == 0) return 0;
        return *mad.rbegin();
    }
}one,two;
void add(int node)
{
    two.add(node);
    one.remove(node);
}
void remove(int node)
{
    two.remove(node);
    one.add(node);
}
int par[N];
void dfs_sz(int u, int p = 0)
{
    sz[u] = 1;
    for(int v : g[u])
    {
        if(v == p) continue;
        par[v] = u;
        dfs_sz(v,u);
        sz[u] += sz[v];
    }
}
void dfs(int u, int p, bool baad = false)
{
    int BigChild = -1;
    int mx = 0;
    in[u] = timer;
    ft[timer] = u;
    int st = timer;
    timer++;
    for(int v : g[u])
    {
        if(v == p) continue;
        if(mx < sz[v])
        {
            mx = sz[v];
            BigChild = v;
        }
    }
    for(int v : g[u])
    {
        if(v == p or v == BigChild) continue;
        dfs(v,u,1);
    }
    int ed = timer;
    if(BigChild != -1) 
    {
        dfs(BigChild,u,0);
    }
    for(int i = st; i < ed; i++) 
    {
        add(ft[i]);
    }
    node_mx[u] = max(one.query(),two.query());
    if(baad)
    {
        for(int i = st; i < timer; i++) remove(ft[i]);
    }
}
void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
        edges.pb({u,v});
    }
    for(int i = 1; i <= n; i++) cin >> val[i],one.add(i);
    dfs_sz(1);
    
    dfs(1,0);
    vector<int>ans(n,0);
    for(int i = 0; i + 1 < n; i++)
    {
        int u = edges[i].ff, v = edges[i].ss;
        if(par[u] == v) ans[i] = node_mx[u];
        else ans[i] = node_mx[v];
    }
    for(int i = 0; i + 1 < n; i++) cout << ans[i] << endl;
}dd

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
    //cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
