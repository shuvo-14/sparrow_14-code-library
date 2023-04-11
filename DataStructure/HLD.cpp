// https://www.hackerrank.com/challenges/subtrees-and-paths/problem
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
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define piii pair<int,pii>
#define min_heap priority_queue<int,vector<int>,greater<int>>

const int mod=1e9+7;

const int N = 1e5 + 9, LG = 18, inf = 1e9 + 9;
int n;
struct segtree{
    
    int size;
    vector<ll>tree,lazy;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size,0LL);
        lazy.assign(2*size,0LL);
    }

    //change accordingly
    int merge(int u, int v)
    {
        return max(u,v);
    }

    void build(int x, int lx, int rx)
    {
        if(lx == rx)
        {
            tree[x] = 0;
            return;
        }
        int mid = (lx+rx)/2;
        build(2*x+1,lx,mid);
        build(2*x+2,mid+1,rx);
        tree[x] = merge(tree[2*x+1],tree[2*x+2]);
    }

    // void build(vector<int>&vec)
    // {
    //     build(0,0,n-1,vec);
    // }

    void propagate(int x, int lx, int rx)
    {
        if(lazy[x])
        {
            tree[x] += lazy[x];
            if(lx != rx)
            {
                lazy[2*x+1] += lazy[x];
                lazy[2*x+2] += lazy[x];
            }
            lazy[x] = 0;
        }
    }

    void update(int x, int lx, int rx, int l, int r, int v)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r)
        {
           lazy[x] += v;
           propagate(x,lx,rx);
           return;
        }
        int mid = (lx+rx)/2;
        update(2*x+1,lx,mid,l,r,v);
        update(2*x+2,mid+1,rx,l,r,v);
        tree[x] = merge(tree[2*x+1], tree[2*x+2]);
    }

    void update(int l, int r, int v){
        update(0,0,n-1,l,r,v);     
    }

    int query(int l, int r, int x, int lx, int rx)
    {
        propagate(x,lx,rx);
        if(lx > r || rx < l) return -inf; //change accordingly
        if(lx >= l && rx <= r) return tree[x];
        int mid = (lx+rx)/2;
        int s1 = query(l,r,2*x+1,lx,mid);
        int s2 = query(l,r,2*x+2,mid+1,rx);
        return merge(s1,s2);
    }

    int query(int l, int r)
    {
        return query(l,r,0,0,n-1);
    }

}t;
vector<int>g[N];
int depth[N],par[N],sz[N];

void dfs(int u, int p = 0)
{
    depth[u] = depth[p] + 1;
    par[u] = p;
    sz[u] = 1;
    
    if(p) g[u].erase(find(g[u].begin(),g[u].end(),p));

    for(auto &v : g[u])
    {
        if(v == p) continue;
        dfs(v,u);
        sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(g[u][0],v);
    }
}

int head[N],in[N],out[N],T;
void dfs_hld(int u) {
  in[u] = ++T;
  for (auto v : g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  out[u] = T;
}

int query(int u, int v) 
{
    int ans= -inf;
    while(head[u] != head[v])
    {
        if(depth[head[u]] < depth[head[v]]) swap(u,v);
        ans = max(ans,t.query(in[head[u]],in[u],0,1,n));
        u = par[head[u]];
    }
    if(depth[u] > depth[v]) swap(u,v);
    ans = max(ans,t.query(in[u],in[v],0,1,n));
    return ans;
}

int32_t main()
{
    IOS;
     cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1);
    head[1] = 1;
    dfs_hld(1);
    t.init(n);
    t.build(0,1,n);
    int q;
    cin >> q;
    while(q--)
    {
        string str;
        cin >> str;
        int u, v;
        cin >> u >> v;
        if(str == "add")
        {
            t.update(0,1,n,in[u],out[u],v);
            //debug(t.query(in[u], out[u],1,1,n));
        }
        else 
        {
            cout << query(u,v) << "\n";
            
        }
    }
    return 0;
}
