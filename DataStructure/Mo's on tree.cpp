// https://www.codechef.com/problems/FCTRE?tab=statement


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
//#define int long long
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;
const int N=1e5+9;
const int block = 350;
const int max_A = 1e6+9;
int in[N],out[N],ft[2*N];
int ara[N];
int level[N];
int ans[N];
int spf[max_A];
int nodeF[N];
vector<int>g[N];
int cnt[max_A],vis[N];
int par[N][20];
int inv[max_A];
int timer;
int res;
struct item
{
    int l, r, lca, id;
    bool operator< (const item &other)
    {
        if(l/block != other.l/block) return l / block < other.l/block;
        return ((l/block)&1)? r > other.r : r < other.r;
    }
}q[N];

void dfs(int u, int p = 0)
{
    level[u] = level[p] + 1;
    in[u] = timer;
    ft[timer] = u;
    timer++;
    par[u][0] = p;
    for(int v : g[u])
    {
        if(v == p) continue;
        dfs(v,u);
    }
    out[u] = timer;
    ft[timer] = u;
    timer++;
}
int BigMod(int a, int n)
{
    if(!n) return 1LL;
    int now = BigMod(a,n/2);
    now = (1LL * now * now) % mod;
    if(n&1) now = (1LL * now * a) % mod;
    return now;
}
void precompute()
{
    vector<int>prime;
    spf[1] = 1;
    for(int i = 2; i < max_A; i++)
    {
        if(!spf[i]) spf[i] = i,prime.pb(i);
        int sz = prime.size();
        for(int j = 0; j < sz and prime[j] <= spf[i] and 1LL * prime[j] * i < max_A; j++)
        {
            spf[prime[j] * i] = prime[j];
        }
    }
    inv[max_A-1] = BigMod(max_A-1,mod-2);
    for(int i = max_A-2; i >= 1; i--)
    {
       // inv[i] = (inv[i+1] * (i+1)) % mod;
        inv[i] = BigMod(i,mod-2);
    }
   
}
void binarylifting(int n)
{
    for(int j = 1; j < 20; j++)
    {
        for(int i = 1; i <= n; i++)
        {
            if(par[i][j-1] != -1) 
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
}
int getLCA(int u, int v)
{
    if(level[u] < level[v]) swap(u,v);
    int d = level[u] - level[v];
    for(int i = 19; i >= 0; i--)
    {
        if(d & (1<<i)) u = par[u][i];
    }
    if(u == v) return u;
    for(int i = 19; i >= 0; i--)
    {
        if(par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
// bool comp(item &x, item &y)
// {
//     if(x.l / block != y.l / block) return x.l/block < y.l/block;
//     return (1&(x.l/block)) ? x.r < y.r : x.r > y.r;
// }

void factorize(int id,int add)
{
    int p = -1;
    int x = ara[id];
    while(x != 1)
    {
        
        if(spf[x] != p)
        {
            res = (1LL * res * inv[cnt[spf[x]]+1]) % mod;
           //res = (res * BigMod(cnt[spf[x]]+1,mod-2)) % mod;
            if(p != -1) res = (1LL * res * (cnt[p]+1)) % mod;
            p = spf[x];
        }
        if(add) cnt[spf[x]]++;
        else cnt[spf[x]]--;
        x /= spf[x];
    }
    if(p != -1) res = (1LL * res *(cnt[p]+1)) % mod;
}
void update(int id)
{
    vis[id] = !vis[id];
    if(vis[id]) factorize(id,1);
    else factorize(id,0);
}
int now_l = 1, now_r = 0;
void Mo(int i)
{
    int l = q[i].l, r = q[i].r;
        int lca = q[i].lca;
        while(now_r  < r) 
        {
            now_r++;
            update(ft[now_r]);
        } 
        while(now_l > l)
        {
            now_l--;
            update(ft[now_l]);
        }
        while(now_r > r)
        {
            update(ft[now_r]);
            now_r--;
        }
        while(now_l < l)
        {
            update(ft[now_l]);
            now_l++;
        }
        if(lca != ft[l] and lca != ft[r]) update(lca);
        ans[q[i].id] = res;
        if(lca != ft[l] and lca != ft[r]) update(lca);
}
void solve()
{
    int n;
    cin >> n;
    // initializing
    for(int i = 0; i <= n; i++)
    {
        g[i].clear();
        nodeF[i] = 0;
    }
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    memset(par,-1,sizeof(par));
    timer = 1;
    dfs(1);
    
    binarylifting(n);
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    for(int i = 1; i <= n; i++) cin >> ara[i];
    
    int m;
    cin >> m;
    
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        int lca = getLCA(u,v);
        if(in[u] > in[v]) swap(u,v);
        q[i].id = i;
        q[i].lca = lca;
        if(lca != u and lca != v) 
        {
            
            q[i].l = out[u],q[i].r = in[v];
        }
        else
        {
            q[i].l = in[u];
            q[i].r = in[v];
        }

    }
    sort(q+1,q+m+1);
   
    now_l = 1, now_r = 0;
    res = 1;
    for(int i = 1; i <= m; i++)
    {
        Mo(i);
    }
     for(int i = 1; i <= m; i++) cout << ans[i] << endl;
}

int32_t main()
{
    IOS;
    int t = 1;
    int ct = 1;
    precompute();
    cin >> t;
    while(t--) 
    {
       // cout << "Case #" << ct++ <<": " ;     
        solve();
    }

    return 0;
}
